#include "OperatorManager.h"
#include "Literal.h"
#include "Operateurs.h"
#include "LiteralFactory.h"
#include "Operation.h"
#include "Utility.h"
#include <memory>
#include <algorithm>
#include <sstream>

/**
 * @details Ce constructeur privé crée une seule fois les instances d'Operator correspondant
 * aux opérateurs manipulables par l'application et leur associe une instance d'Operation pour définir leur comportenment.
 */
OperatorManager::OperatorManager() {
    //Création des opérateurs symboliques
    operators.push_back(std::make_shared<Operator>("+", 2, std::make_shared<PlusOperation>(), 0)); //Addition
    operators.push_back(std::make_shared<Operator>("*", 2, std::make_shared<PlusOperation>(), 1)); //Exemple

    //Création des opérateurs parenthésés
    operators.push_back(std::make_shared<Operator>("DUP", 2, std::make_shared<Operation>())); //Exemple
}

const OperatorManager& OperatorManager::getInstance() {
	static OperatorManager instance;
	return instance;
}

const std::shared_ptr<Operator>& OperatorManager::getOperator(const std::string& opcode) const {
    //Recherche d'un opérateur défini dont le symbole est le même que la chaîne passée en argument.
    auto op = std::find_if(operators.begin(), operators.end(), FindOperator(opcode));
    if(op != operators.end()) return *op;
    throw std::invalid_argument("Operator not found");
}

Arguments<std::shared_ptr<Literal>> OperatorManager::dispatchOperation(std::shared_ptr<Operator> op, Arguments<std::shared_ptr<Literal>> args) const {
    if (op->getArity() != args.size()) throw std::invalid_argument("Wrong number of operands.");
    //Cas le plus spécialisé : tous les objets sont représentables sous forme d'entiers
	try {
        return op->getOperation()->eval((Arguments<IntegerLiteral>)args);
	}
    catch (std::exception& e) {
        //Cas où tous les objets sont représentables sous forme de rationnels
        try {
            return op->getOperation()->eval((Arguments<RationalLiteral>)args);
		} 
        catch(std::exception&) {
            //Cas où tous les objets sont représentables sous forme de réels
			try {
                return op->getOperation()->eval((Arguments<RealLiteral>)args);
            }
            catch (std::exception&) {                
                //Cas où tous les objets sont représentables sous forme de complexes
				try {
                    return op->getOperation()->eval((Arguments<ComplexLiteral>)args);
				}
                catch (std::exception&) {
                    /* Cas le plus général : on essaye de convertir en expression et d'appliquer l'opération générique de concaténation.
                    Cette opération ne dépend pas de l'opérateur (uniquement de son symbole), aucune classe d'Operation n'est donc appelée */
                    try {
                        return Arguments<std::shared_ptr<Literal>>{ opExpression(op, (Arguments<ExpressionLiteral>)args) };
                    }
                    catch(std::exception&) {
                        throw std::invalid_argument("No suitable operator for these operands.");
                    }
				}
			}
		}
    }
}

bool OperatorManager::FindOperator::operator()(const std::shared_ptr<Operator>& op) {
    return op->toString() == symbol;
}

bool OperatorManager::PriorityComparator::operator()(const std::shared_ptr<Operator> &op) {
    return op->isSymbolic() && (priority > op->getPriority());
}

std::shared_ptr<ExpressionLiteral> OperatorManager::opExpression(std::shared_ptr<Operator> op, const Arguments<ExpressionLiteral>& args) const {
    std::ostringstream oss;
    //Cas d'un opérateur parenthésé, on l'applique simplement
    if(!op->isSymbolic()) {
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
        //On récupère un vecteur de tous les opérateurs définis ayant une priorité inférieure à la priorité de l'opérateur courant
        std::vector<std::vector<std::shared_ptr<Operator>>::const_iterator> res;
        Utility::select_iterator(operators.begin(), operators.end(), std::back_inserter(res), PriorityComparator(op->getPriority()));
        //Par définition du caractère symbolique, on connaît déjà l'arité : 2. On récupère les éléments non-parenthésés des expressions
        std::string left = Utility::getOutside(args.at(0).getExpression(), '(', ')');
        std::string right = Utility::getOutside(args.at(1).getExpression(), '(', ')');

        //Indique s'il faut parenthéser les expressions opérandes
        bool parenthizeLeft = false;
        bool parenthizeRight = false;

        //On itère sur tous les opérateurs existants de priorité inférieure
        for(auto it : res) {
            std::string symbol = (*it)->toString();
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
