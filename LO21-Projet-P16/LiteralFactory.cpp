#include "LiteralFactory.h"
#include "Utility.h"
#include <algorithm>
#include <sstream>
#include <cmath>

LiteralFactory::LiteralFactory() { //Push dans l'ordre de priorité
	allocatorsPriority.push_back(std::bind(&LiteralFactory::makeInteger, this, std::placeholders::_1));
	allocatorsPriority.push_back(std::bind(&LiteralFactory::makeRational, this, std::placeholders::_1));
	allocatorsPriority.push_back(std::bind(&LiteralFactory::makeReal, this, std::placeholders::_1));
	allocatorsPriority.push_back(std::bind(&LiteralFactory::makeExpression, this, std::placeholders::_1));
}

LiteralFactory& LiteralFactory::getInstance() {
	 static LiteralFactory instance;
	 return instance;
}

std::shared_ptr<Literal> LiteralFactory::makeInteger(const std::string& s) {
	if(!Utility::isUnsignedInt(s)) throw std::invalid_argument("Only positive integer are accepted.");
	return makeLiteral(std::stoi(s));
}

std::shared_ptr<Literal> LiteralFactory::makeRational(const std::string& s) {
	std::istringstream iss(s);
	std::string num, den;
	std::getline(iss, num, '/');
	std::getline(iss, den);
	return makeLiteral(std::stoi(num), std::stoi(den));
}

std::shared_ptr<Literal> LiteralFactory::makeReal(const std::string& s) {
	return makeLiteral(std::stof(s));
}

std::shared_ptr<Literal> LiteralFactory::makeExpression(const std::string& s) {
	std::string copy(s);
	copy.erase(std::remove(copy.begin(), copy.end(), ' '), copy.end());
	if (s.front() != '"' || s.back() == '"') {
		copy.erase(0, 1);
		copy.erase(copy.size() - 1);
		return makeLiteral(copy);
	}
	throw std::invalid_argument("Expressions must be surrounded by double quotes."); //Ici gérer la litérale atome (variable etc)
}

std::shared_ptr<Literal> LiteralFactory::makeLiteralFromString(std::string str) {
	for (auto alloc : allocatorsPriority) {
		try {
			return alloc(str);
		}
		catch(std::exception&) {}
	}
	throw std::invalid_argument("No literal could match string.");
}

std::shared_ptr<Literal> LiteralFactory::makeLiteral(int n) {
	return std::shared_ptr<Literal>(new IntegerLiteral(n));
}

std::shared_ptr<Literal> LiteralFactory::makeLiteral(int num, int den) {
	unsigned int gcd = Utility::computeGcd(num, den);
	if (den < 0) { //Simplification des signes
		num = -num;
		den = -den;
	}
	num /= gcd;
	den /= gcd;
	if (den == 1) return makeLiteral(num);
	return std::shared_ptr<RationalLiteral>(new RationalLiteral(num, den));
}

std::shared_ptr<Literal> LiteralFactory::makeLiteral(double f) {
	double intpart;
	if (std::modf(f, &intpart) == 0) return makeLiteral((int)intpart);
	return std::shared_ptr<Literal>(new RealLiteral(f));
}

std::shared_ptr<Literal> LiteralFactory::makeLiteral(const std::string &s) {
	return std::shared_ptr<ExpressionLiteral>(new ExpressionLiteral(s));
}

