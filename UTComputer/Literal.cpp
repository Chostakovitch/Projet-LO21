#include <iostream>
#include <memory>
#include <sstream> 
#include "Literal.h"
#include "Utility.h"

Literal::operator IntegerLiteral() { throw std::bad_cast(); }
Literal::operator RationalLiteral() { throw std::bad_cast(); }
Literal::operator RealLiteral() { throw std::bad_cast(); }
Literal::operator ComplexLiteral() { throw std::bad_cast(); }
Literal::operator ExpressionLiteral() { throw std::bad_cast(); }

NumericLiteral::operator ExpressionLiteral() { return ExpressionLiteral(toString()); }

IntegerLiteral::operator RationalLiteral() { return RationalLiteral(*this, IntegerLiteral(1)); }
IntegerLiteral::operator RealLiteral() { return RealLiteral(value); }

RationalLiteral::operator RealLiteral() { return RealLiteral(num.getValue() / (double)den.getValue()); }

std::string ProgramLiteral::toString() const {
	static int count;
	++count;
	std::stringstream ss;
	ss << "Program(debug)" << std::endl;
	for (int i = 0; i < count - 1; ++i) ss << "\t";
	ss << "[" << std::endl;
	for (auto op : operands) {
		for (int i = 0; i < count; ++i) ss << "\t";
		ss << op->toString();
		ss << "\t" << typeid(*op).name() <<"(debug)";
		ss << std::endl;
	}
	for (int i = 0; i < count - 1; ++i) ss << "\t";
	ss << "]" << std::endl;
	--count;
	return ss.str();
}
