#include "LiteralFactory.h"
#include "OperatorManager.h"
#include "Utility.h"
#include <algorithm>
#include <sstream>
#include <vector>
#include <iterator>

LiteralFactory::LiteralFactory() { //Push dans l'ordre de priorité
	allocatorsPriority.push_back(std::bind(&LiteralFactory::makeInteger, this, std::placeholders::_1));
	allocatorsPriority.push_back(std::bind(&LiteralFactory::makeRational, this, std::placeholders::_1));
	allocatorsPriority.push_back(std::bind(&LiteralFactory::makeReal, this, std::placeholders::_1));
	allocatorsPriority.push_back(std::bind(&LiteralFactory::makeExpression, this, std::placeholders::_1));
	allocatorsPriority.push_back(std::bind(&LiteralFactory::makeCompositeProgram, this, std::placeholders::_1));
}

LiteralFactory& LiteralFactory::getInstance() {
	 static LiteralFactory instance;
	 return instance;
}

std::shared_ptr<Literal> LiteralFactory::makeInteger(const std::string& s) const {
	if(!Utility::isUnsignedInt(s)) throw std::invalid_argument("Only positive integer are accepted.");
	return makeLiteral(std::stoi(s));
}

std::shared_ptr<Literal> LiteralFactory::makeRational(const std::string& s) const {
	std::istringstream iss(s);
	std::string num, den;
	std::getline(iss, num, '/');
	std::getline(iss, den);
	return makeLiteral(std::stoi(num), std::stoi(den));
}

std::shared_ptr<Literal> LiteralFactory::makeReal(const std::string& s) const {
	return makeLiteral(std::stof(s));
}

std::shared_ptr<Literal> LiteralFactory::makeExpression(const std::string& s) const {
	std::string copy(s);
	copy.erase(std::remove(copy.begin(), copy.end(), ' '), copy.end());
	if (s.front() == '"' && s.back() == '"') {
		copy.erase(0, 1);
		copy.erase(copy.size() - 1);
		return makeLiteral(copy);
	}
	throw std::invalid_argument("Expressions must be surrounded by double quotes.");
}

void LiteralFactory::makeLeafProgram(const std::string &s, std::shared_ptr<ProgramLiteral> prog) const {
	std::istringstream iss(s);
	std::vector<std::string> ops { std::istream_iterator<std::string>(iss), std::istream_iterator<std::string>() };
	for (auto str : ops) { //On itère sur toutes les opérandes séparées par des espaces
		std::shared_ptr<Operand> op;
		try {
			prog->add(makeLiteralFromString(str)); //Ajout du litéral au vecteur courant
		}
		catch (std::invalid_argument&) {
			prog->add(OperatorManager::getInstance().getOperator(str)); //Ajout de l'opérateur au vecteur courant
		}
	}
}

std::shared_ptr<Literal> LiteralFactory::makeCompositeProgram(const std::string& s) const {
	std::shared_ptr<ProgramLiteral> prog(new ProgramLiteral);
	std::string copy(s);
	size_t first, last;
	if (s.front() == '[' && s.back() == ']') {
		copy.erase(0, 1);
		copy.erase(copy.size() - 1); //On efface les délimiteurs de programme
		first = copy.find_first_of('['); //On trouve le plus large sous-programme (s'il existe)
		last = copy.find_last_of(']');
		if (first == std::string::npos && last == std::string::npos) makeLeafProgram(copy, prog); //Cas où n'y a pas de sous-programme (terminaison)
		else if(first != std::string::npos && last != std::string::npos) { //Cas où il y a un sous-programme (deux feuilles éventuelles + une récursion)
			makeLeafProgram(copy.substr(0, first), prog);
			prog->add(makeCompositeProgram(copy.substr(first, last - first + 1)));
			makeLeafProgram(copy.substr(last + 1, copy.size() - last + 1), prog);
		}
		else {
			throw std::invalid_argument("Square bracket unclosed.");
		}
		return prog;
	}
	throw std::invalid_argument("Programs and subprograms must be surrounded by square brackets.");
}

std::shared_ptr<Literal> LiteralFactory::makeLiteralFromString(std::string str) const {
	for (auto alloc : allocatorsPriority) {
		try {
			return alloc(str);
		}
		catch(std::exception&) {}
	}
	throw std::invalid_argument("No literal could match string.");
}

std::shared_ptr<Literal> LiteralFactory::makeLiteral(int n) const {
	return std::shared_ptr<Literal>(new IntegerLiteral(n));
}

std::shared_ptr<Literal> LiteralFactory::makeLiteral(int num, int den) const {
	unsigned int gcd = Utility::computeGcd(num, den);
	if (den < 0) { //Simplification des signes
		num = -num;
		den = -den;
	}
	num /= gcd;
	den /= gcd;
	if (den == 1) return makeLiteral(num);
	return std::shared_ptr<RationalLiteral>(new RationalLiteral(IntegerLiteral(num), IntegerLiteral(den)));
}

std::shared_ptr<Literal> LiteralFactory::makeLiteral(double f) const {
	double intpart;
	if (std::modf(f, &intpart) == 0) return makeLiteral((int)intpart);
	return std::shared_ptr<Literal>(new RealLiteral(f));
}

std::shared_ptr<Literal> LiteralFactory::makeLiteral(const std::string &s) const {
	return std::shared_ptr<ExpressionLiteral>(new ExpressionLiteral(s));
}

