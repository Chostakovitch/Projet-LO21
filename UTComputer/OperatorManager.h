#pragma once
#include "Operateurs.h"

class OperatorManager
{
	OperatorManager();
	std::map<std::string, std::shared_ptr<Operator>> operators;
	static const std::map<std::string, std::pair<int, std::shared_ptr<Operation>>> op_infos;
public:
	OperatorManager(const OperatorManager&) = delete;
	void operator=(const OperatorManager&) = delete;
	static OperatorManager& getInstance();
	const std::shared_ptr<Operator> getOperator(std::string opcode);
	std::vector<std::shared_ptr<Literal>> dispatchOperation(std::shared_ptr<Operator> op, Arguments<std::shared_ptr<Literal>> args);
};