#pragma once
#include "Literal.h"
#include <memory>
#include <functional>
#include <vector>

class LiteralFactory
{
	LiteralFactory();
	std::shared_ptr<Literal> makeInteger(const std::string& s);
	std::shared_ptr<Literal> makeRational(const std::string& s);
	std::shared_ptr<Literal> makeReal(const std::string& s);
	std::shared_ptr<Literal> makeExpression(const std::string& s);
	std::vector<std::function<std::shared_ptr<Literal>(const std::string&)>> allocatorsPriority;
public:
	static LiteralFactory& getInstance();
	LiteralFactory(const LiteralFactory&) = delete;
	void operator=(const LiteralFactory&) = delete;
	std::shared_ptr<Literal> makeLiteralFromString(std::string str);
	std::shared_ptr<Literal> makeLiteral(int n);
	std::shared_ptr<Literal> makeLiteral(int num, int den);
	std::shared_ptr<Literal> makeLiteral(double f);
	std::shared_ptr<Literal> makeLiteral(const std::string& s);
};

