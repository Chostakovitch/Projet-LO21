#include "OperatorManager.h"
#include "Literal.h"
#include "Operateurs.h"
#include "LiteralFactory.h"
#include "Operation.h"
#include "Utility.h"
#include <memory>
#include "UTException.h"
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
    operators.push_back(std::make_shared<SymbolicOperator>("-", 2, std::make_shared<MoinsOperation>(), true, 0)); //Soustraction
    operators.push_back(std::make_shared<SymbolicOperator>("*", 2, std::make_shared<MulOperation>(), true, 1)); //Multiplication
    operators.push_back(std::make_shared<SymbolicOperator>("$", 2, std::make_shared<ComplexOperation>(), true, 2)); //Complexe
    operators.push_back(std::make_shared<SymbolicOperator>("/", 2, std::make_shared<DivOperation>(), true, 1)); //Division

    //Création des opérateurs parenthésés
    operators.push_back(std::make_shared<FunctionOperator>("NEG", 1, std::make_shared<NegOperation>(), true)); //Négation
    operators.push_back(std::make_shared<FunctionOperator>("DIV", 2, std::make_shared<IntDivOperation>(), true)); //Division entière
    operators.push_back(std::make_shared<FunctionOperator>("MOD", 2, std::make_shared<ModOperation>(), true)); //Modulo
    operators.push_back(std::make_shared<FunctionOperator>("POW", 2, std::make_shared<PowOperation>(), true)); //Puissance
    operators.push_back(std::make_shared<FunctionOperator>("SIN", 1, std::make_shared<SinOperation>(), true)); //Puissance
    operators.push_back(std::make_shared<FunctionOperator>("COS", 1, std::make_shared<CosOperation>(), true)); //Puissance
    operators.push_back(std::make_shared<FunctionOperator>("TAN", 1, std::make_shared<TanOperation>(), true)); //Puissance
    operators.push_back(std::make_shared<FunctionOperator>("ARCSIN", 1, std::make_shared<ArcSinOperation>(), true)); //Puissance
    operators.push_back(std::make_shared<FunctionOperator>("ARCCOS", 1, std::make_shared<ArcCosOperation>(), true)); //Puissance
    operators.push_back(std::make_shared<FunctionOperator>("ARCTAN", 1, std::make_shared<ArcTanOperation>(), true)); //Puissance
    operators.push_back(std::make_shared<FunctionOperator>("SQRT", 1, std::make_shared<SqrtOperation>(), true)); //Puissance

}

const OperatorManager& OperatorManager::getInstance() {
	static OperatorManager instance;
	return instance;
}

const std::shared_ptr<Operator>& OperatorManager::getOperator(std::string opcode) const {
    //Recherche d'un opérateur défini dont le symbole est le même que la chaîne passée en argument.
    auto op = std::find_if(operators.begin(), operators.end(), [&opcode](const std::shared_ptr<Operator>& op) { return op->toString() == opcode; });
    if(op != operators.end()) return *op;
    throw ParsingError(opcode, "Operator not found");
}

bool OperatorManager::isOperator(const std::string& opcode) const {
    try {
        getOperator(opcode);
        return true;
    } catch(ParsingError e) {
        return false;
    }
}

std::vector<std::shared_ptr<Operator>> OperatorManager::getSymbolicOperators() const {
    std::vector<std::shared_ptr<Operator>> res;
    std::copy_if(operators.begin(), operators.end(), std::back_inserter(res), [](const std::shared_ptr<Operator> op) {
        return std::dynamic_pointer_cast<SymbolicOperator>(op);
    });
    return res;
}

Arguments<std::shared_ptr<Literal>> OperatorManager::dispatchOperation(std::shared_ptr<Operator> op, Arguments<std::shared_ptr<Literal>> args) const {
    //0. Vérifications
    if (op->getArity() != args.size()) throw OperationError(op, args, "Wrong number of operands.");

    //1. Cas particuliers
    //1.1. Un objet LiteralExpression est présent dans les opérandes et l'opérateur est numérique : méthode membre.
    if(op->isNumeric()) {
        for(auto& arg : args) {
            if(std::dynamic_pointer_cast<ExpressionLiteral>(arg)) return Arguments<std::shared_ptr<Literal>>{opExpression(op, (Arguments<std::shared_ptr<ExpressionLiteral>>)args)};
        }
    }
    //1.2. [...] (eval, memento) TODO

    //2. Appel de la méthode d'évaluation générique de l'opérateur.
    try {
        return Operation::apply(op->getOperation(), args);
    }
    //3. Uniformisation impossible ou opération non-implémentée / ayant provoqué une erreur.
    catch(UTException& e) {
        throw e;
    }
}

std::shared_ptr<ExpressionLiteral> OperatorManager::opExpression(std::shared_ptr<Operator> op, const Arguments<std::shared_ptr<ExpressionLiteral>>& args) const {
    std::ostringstream oss;
    auto op_symbol = std::dynamic_pointer_cast<SymbolicOperator>(op);
    //Cas d'un opérateur fonction, on l'applique simplement
    if(!op_symbol) {
        oss << op->toString() << "(";
        //Ajout des opérandes
        for(auto it = args.begin(); it != args.end(); ++it) {
            oss << (*it)->getExpression();
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
        std::string left = Utility::getOutside(args.at(0)->getExpression(), '(', ')');
        std::string right = Utility::getOutside(args.at(1)->getExpression(), '(', ')');

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
        oss << args.at(0)->getExpression();
        if(parenthizeLeft) oss << ')';
        oss << op->toString();
        if(parenthizeRight) oss << '(';
        oss << args.at(1)->getExpression();
        if(parenthizeRight) oss << ')';
    }
    return std::make_shared<ExpressionLiteral>(oss.str());
}
