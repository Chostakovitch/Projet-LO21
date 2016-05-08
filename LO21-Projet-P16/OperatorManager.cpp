#include "OperatorManager.h"
#include "Literal.h"
#include "Operateurs2.h"
#include "LiteralFactory.h"
#include "Operation.h"
#include <memory>

const std::map<std::string, std::pair<int, std::shared_ptr<Operation>>> OperatorManager::op_infos = { {"+", { 2, std::shared_ptr<Operation>(new PlusOperation)} } };

OperatorManager::OperatorManager() {
	for (auto op : op_infos) operators.insert({ op.first, std::shared_ptr<Operator>(new Operator(op.first, op.second.first, op.second.second)) });
}

OperatorManager& OperatorManager::getInstance() {
	static OperatorManager instance;
	return instance;
}

const std::shared_ptr<Operator> OperatorManager::getOperator(std::string opcode) {
	if (operators.count(opcode) < 0) throw std::invalid_argument("Operator doesn't exist.");
	return operators[opcode];
}

std::vector<std::shared_ptr<Literal>> OperatorManager::dispatchOperation(std::shared_ptr<Operator> op, Arguments<std::shared_ptr<Literal>> args) {
	if (op->arity != args.size()) throw std::invalid_argument("Wrong number of operands.");
	try {
		return op->operation->eval(LiteralFactory::getInstance(), (Arguments<IntegerLiteral>)args);
	}
	catch (std::bad_cast&) {
		try {
			return op->operation->eval(LiteralFactory::getInstance(), (Arguments<RationalLiteral>)args);
		} 
		catch(std::bad_cast&) {
			try {
				return op->operation->eval(LiteralFactory::getInstance(), (Arguments<RealLiteral>)args);
			}
			catch (std::bad_cast&) {
				try {
					return op->operation->eval(LiteralFactory::getInstance(), (Arguments<ExpressionLiteral>)args);
				}
				catch (std::bad_cast&) {
					throw std::invalid_argument("Failed to standardize arguments.");
				}
			}
		}
	}
}

int main() {
	//Singletons
	LiteralFactory& factory = LiteralFactory::getInstance();
	OperatorManager& manager = OperatorManager::getInstance();

	//Parsing des littéraux
	auto l1 = factory.makeLiteralFromString("\"1\"");
	auto l2 = factory.makeLiteralFromString("5.4");

	//Instance de l'opérateur
	auto op = manager.getOperator("+");

	//Liste d'arguments générique
	Arguments<std::shared_ptr<Literal>> args = { l1, l2 };

	//Promotion des arguments et appel de la bonne fonction de calcul
	auto result = manager.dispatchOperation(op, args);

	for (auto arg : args) std::cout << typeid(*arg).name() << " : " << arg->toString() << std::endl;
	//Affichage du vecteur de retour
	for (auto res : result) std::cout << typeid(*res).name() << " : " << res->toString() << std::endl;
	getchar();
	return 0;
}