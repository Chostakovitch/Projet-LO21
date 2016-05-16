#include "OperatorManager.h"
#include "Literal.h"
#include "Operateurs.h"
#include "LiteralFactory.h"
#include "Operation.h"
#include <memory>
#include <algorithm>

/**
 * @details Ce constructeur privé crée une seule fois les instances d'Operator correspondant
 * aux opérateurs manipulables par l'application et leur associe une instance d'Operation pour définir leur comportenment.
 */
OperatorManager::OperatorManager() {
    operators.push_back(std::make_shared<Operator>("+", 2, std::make_shared<PlusOperation>(), true)); //Addition
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

std::vector<std::shared_ptr<Literal>> OperatorManager::dispatchOperation(std::shared_ptr<Operator> op, Arguments<std::shared_ptr<Literal>> args) const {
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
                        //(Arguments<ExpressionLiteral>)args); Ici appeler le traitement de l'expression
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
