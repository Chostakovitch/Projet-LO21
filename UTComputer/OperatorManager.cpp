#include "OperatorManager.h"
#include "Literal.h"
#include "Operateurs.h"
#include "LiteralFactory.h"
#include "Operation.h"
#include <memory>

const std::map<std::string, std::pair<int, std::shared_ptr<Operation>>> OperatorManager::op_infos = {
	{"+", { 2, std::shared_ptr<Operation>(new PlusOperation)} },
	{"NEG", { 1, nullptr }},
	{"DUP", { 1, nullptr }},
	{"IFT", { 3, nullptr }},
	{"<", { 2, nullptr }}
};

OperatorManager::OperatorManager() {
	for (auto op : op_infos) operators.insert({ op.first, std::shared_ptr<Operator>(new Operator(op.first, op.second.first, op.second.second)) });
}

OperatorManager& OperatorManager::getInstance() {
	static OperatorManager instance;
	return instance;
}

const std::shared_ptr<Operator> OperatorManager::getOperator(std::string opcode) {
	if (operators.count(opcode) == 0) throw std::invalid_argument("Operator doesn't exist.");
	return operators[opcode];
}

std::vector<std::shared_ptr<Literal>> OperatorManager::dispatchOperation(std::shared_ptr<Operator> op, Arguments<std::shared_ptr<Literal>> args) {
	if (op->arity != args.size()) throw std::invalid_argument("Wrong number of operands.");
	try {
        return op->operation->eval((Arguments<IntegerLiteral>)args);
	}
	catch (std::bad_cast&) {
		try {
            return op->operation->eval((Arguments<RationalLiteral>)args);
		} 
		catch(std::bad_cast&) {
			try {
                return op->operation->eval((Arguments<RealLiteral>)args);
			}
			catch (std::bad_cast&) {
				try {
					//(Arguments<ExpressionLiteral>)args); Ici appeler le traitement de l'expression
				}
				catch (std::bad_cast&) {
					throw std::invalid_argument("Failed to standardize arguments.");
				}
			}
		}
	}
}
