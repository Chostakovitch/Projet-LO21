#pragma once
#include "Literal.h"
#include <memory>
#include <functional>
#include <vector>

//TODO : traitement d'un atome (cherche dans un enregistrement des variables mais renvoie la littérale associée dans tous les cas)

class LiteralFactory
{
	LiteralFactory();
	std::shared_ptr<Literal> makeInteger(const std::string& s) const;
	std::shared_ptr<Literal> makeRational(const std::string& s) const;
	std::shared_ptr<Literal> makeReal(const std::string& s) const;
	std::shared_ptr<Literal> makeExpression(const std::string& s) const;
	std::shared_ptr<Literal> makeCompositeProgram(const std::string& s) const;
	void makeLeafProgram(const std::string &s, std::shared_ptr<ProgramLiteral> prog) const;
	std::vector<std::function<std::shared_ptr<Literal>(const std::string&)>> allocatorsPriority;
public:
	static LiteralFactory& getInstance();
	LiteralFactory(const LiteralFactory&) = delete;
	void operator=(const LiteralFactory&) = delete;
	std::shared_ptr<Literal> makeLiteralFromString(std::string str) const;
	std::shared_ptr<Literal> makeLiteral(int n) const;
	std::shared_ptr<Literal> makeLiteral(int num, int den) const;
	std::shared_ptr<Literal> makeLiteral(double f) const;
	std::shared_ptr<Literal> makeLiteral(const std::string& s) const;
};

