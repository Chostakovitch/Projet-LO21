#include "OperatorManager.h"
#include "Literal.h"
#include "Operateurs.h"
#include "LiteralFactory.h"
#include "Operation.h"
#include "Utility.h"
#include <memory>
#include <algorithm>
#include <iterator>
#include <sstream>

/**
 * @details Ce constructeur privé crée une seule fois les instances d'Operator correspondant
 * aux opérateurs manipulables par l'application et leur associe une instance d'Operation pour définir leur comportenment.
 */
OperatorManager::OperatorManager() : minus_symbol("-") {
    //Création des opérateurs symboliques
    operators.push_back(std::make_shared<SymbolicOperator>("+", 2, std::make_shared<PlusOperation>(), true, 0)); //Addition
    operators.push_back(std::make_shared<SymbolicOperator>("*", 2, std::make_shared<PlusOperation>(), true, 1)); //Exemple
    operators.push_back(std::make_shared<SymbolicOperator>("$", 2, std::make_shared<PlusOperation>(), true, 2)); //Exemple
    operators.push_back(std::make_shared<SymbolicOperator>(minus_symbol, 2, std::make_shared<PlusOperation>(), true, 2)); //Exemple

    //Création des opérateurs parenthésés
    operators.push_back(std::make_shared<FunctionOperator>("POW", 2, std::make_shared<Operation>(), true)); //Exemple
    operators.push_back(std::make_shared<FunctionOperator>("SIN", 2, std::make_shared<Operation>(), true)); //Exemple
    operators.push_back(std::make_shared<FunctionOperator>("STO", 2, std::make_shared<Operation>(), false)); //Exemple
    auto eval = std::make_shared<FunctionOperator>("EVAL", 1, std::make_shared<PlusOperation>(), false); //Exemple
    operators.push_back(eval);

    //Définition de la priorité des casts numériques
    numericPriority.push_back(&applyOperation<IntegerLiteral>);
    numericPriority.push_back(&applyOperation<RationalLiteral>);
    numericPriority.push_back(&applyOperation<RealLiteral>);
    numericPriority.push_back(&applyOperation<ComplexLiteral>);
}

const OperatorManager& OperatorManager::getInstance() {
	static OperatorManager instance;
	return instance;
}

const std::shared_ptr<Operator>& OperatorManager::getOperator(const std::string& opcode) const {
    //Recherche d'un opérateur défini dont le symbole est le même que la chaîne passée en argument.
    auto op = std::find_if(operators.begin(), operators.end(), [&opcode](const std::shared_ptr<Operator>& op) { return op->toString() == opcode; });
    if(op != operators.end()) return *op;
    throw std::invalid_argument("Operator not found");
}

bool OperatorManager::isOperator(const std::string& opcode) const {
    try {
        getOperator(opcode);
        return true;
    } catch(std::exception e) {
        return false;
    }
}

Arguments<std::shared_ptr<Operand>> OperatorManager::dispatchOperation(std::shared_ptr<Operator> op, Arguments<std::shared_ptr<Literal>> args) const {
    if (op->getArity() != args.size()) throw std::invalid_argument("Wrong number of operands.");
    //Si l'opération définit une méthode d'évaluation générique, on l'appelle ici
    try {
        return op->getOperation()->eval(args);
    }
    //Sinon, on tente d'appliquer l'opération sur des types homogènes numériques concrèts
    catch(std::invalid_argument& e) {
        for(auto caller : numericPriority) {
            try {
                return caller(op->getOperation(), args);
            }
            catch(std::bad_cast&) {}
            //Cas où les littéraux sont homogènes et l'opération existe, mais échoue.
            catch(std::invalid_argument& e) {
                throw std::invalid_argument(std::string("No operation suitable for operator " + op->toString() + " with these operands : ") + e.what());
            }
        }
    }
    //Aucune conversion vers des littérales numériques n'a été trouvée : on tente de caster en littérales expressions.
    try {
        //Si l'opérateur est numérique, il faut utiliser la méthode d'évaluation membre.
        if(op->isNumeric()) return Arguments<std::shared_ptr<Operand>>{opExpression(op, (Arguments<ExpressionLiteral>)args)};
        //Sinon, on tente de trouver une méthode d'évaluation sur LiteralExpression (ex : opérateur EVAL -> non numérique et s'applique sur LiteralExpression).
        return applyOperation<ExpressionLiteral>(op->getOperation(), args);
    }
    //Aucun comportement valable pour cet opérateur et ces opérandes.
    catch(std::exception& e) {
        throw std::invalid_argument(std::string("Failed to apply operation for these operands. Operator : ") + op->toString() + std::string(" : ") + e.what());
    }
}

std::shared_ptr<ExpressionLiteral> OperatorManager::opExpression(std::shared_ptr<Operator> op, const Arguments<ExpressionLiteral>& args) const {
    std::ostringstream oss;
    auto op_symbol = std::dynamic_pointer_cast<SymbolicOperator>(op);
    //Cas d'un opérateur fonction, on l'applique simplement
    if(!op_symbol) {
        oss << op->toString() << "(";
        //Ajout des opérandes
        for(auto it = args.begin(); it != args.end(); ++it) {
            oss << it->getExpression();
            //Excepté pour la dernière itération
            if(std::next(it) != args.end()) {
                oss << ',';
            }
        }
        oss << ")";
    }
    //Cas d'un opérateur symbolique, il faut vérifier la priorité des opérateurs présents dans les expressions
    else {
        //On récupère un vecteur de tous les opérateurs symboliques définis ayant une priorité inférieure à la priorité de l'opérateur courant
        std::vector<std::shared_ptr<Operator>> res;
        std::copy_if(operators.begin(), operators.end(), std::back_inserter(res), [&op_symbol](const std::shared_ptr<Operator> op) {
            auto s_op = std::dynamic_pointer_cast<SymbolicOperator>(op);
            return s_op && s_op->getPriority() <= op_symbol->getPriority();
        });

        //Par définition du caractère symbolique, on connaît déjà l'arité : 2. On récupère les éléments non-parenthésés des expressions
        std::string left = Utility::getOutside(args.at(0).getExpression(), '(', ')');
        std::string right = Utility::getOutside(args.at(1).getExpression(), '(', ')');

        //Indique s'il faut parenthéser les expressions opérandes
        bool parenthizeLeft = false;
        bool parenthizeRight = false;

        //On itère sur tous les opérateurs existants de priorité inférieure
        for(auto it : res) {
            std::string symbol = it->toString();
            //A gauche ou à droite, s'il existe un opérateur non parenthésé de priorité inférieure, il faut mettre des parenthèses
            if(left.find(symbol) != std::string::npos) parenthizeLeft = true;
            if(right.find(symbol) != std::string::npos) parenthizeRight = true;
        }

        //Construction de l'expression
        if(parenthizeLeft) oss << '(';
        oss << args.at(0).getExpression();
        if(parenthizeLeft) oss << ')';
        oss << op->toString();
        if(parenthizeRight) oss << '(';
        oss << args.at(1).getExpression();
        if(parenthizeRight) oss << ')';
    }
    return std::make_shared<ExpressionLiteral>(oss.str());
}
