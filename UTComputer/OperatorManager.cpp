#include "OperatorManager.h"
#include "Literal.h"
#include "Operateurs.h"
#include "LiteralFactory.h"
#include "Operation.h"
#include <memory>
#include <algorithm>

OperatorManager::OperatorManager() {
    operators.push_back(std::make_shared<Operator>("+", 2, std::make_shared<PlusOperation>()));
}

const OperatorManager& OperatorManager::getInstance() {
	static OperatorManager instance;
	return instance;
}

const std::shared_ptr<Operator>& OperatorManager::getOperator(const std::string& opcode) const {
    auto op = std::find_if(operators.begin(), operators.end(), FindOperator(opcode));
    if(op != operators.end()) return *op;
    throw std::invalid_argument("Operator not found");
}

std::vector<std::shared_ptr<Literal>> OperatorManager::dispatchOperation(std::shared_ptr<Operator> op, Arguments<std::shared_ptr<Literal>> args) const {
    if (op->getArity() != args.size()) throw std::invalid_argument("Wrong number of operands.");
	try {
        return op->getOperation()->eval((Arguments<IntegerLiteral>)args);
	}
    catch (std::exception& e) {
        try {
            return op->getOperation()->eval((Arguments<RationalLiteral>)args);
		} 
        catch(std::exception&) {
			try {
                return op->getOperation()->eval((Arguments<RealLiteral>)args);
			}
            catch (std::exception&) {
				try {
					//(Arguments<ExpressionLiteral>)args); Ici appeler le traitement de l'expression
				}
                catch (std::exception&) {
                    throw std::invalid_argument("No suitable operator for these operands.");
				}
			}
		}
	}
}

bool OperatorManager::FindOperator::operator()(const std::shared_ptr<Operator>& op) {
    return op->toString() == symbol;
}
