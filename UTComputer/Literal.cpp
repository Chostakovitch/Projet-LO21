#include <iostream>
#include <memory>
#include <sstream> 
#include "Literal.h"
#include "Utility.h"

Literal::operator IntegerLiteral() const { throw std::bad_cast(); }
Literal::operator RationalLiteral() const { throw std::bad_cast(); }
Literal::operator RealLiteral() const { throw std::bad_cast(); }
Literal::operator ComplexLiteral() const { throw std::bad_cast(); }
Literal::operator ExpressionLiteral() const { throw std::bad_cast(); }

NumericLiteral::operator ExpressionLiteral() const { return ExpressionLiteral(toString()); }

IntegerLiteral::operator RationalLiteral() const { return RationalLiteral(value, 1); }
IntegerLiteral::operator RealLiteral() const { return RealLiteral(value); }

RationalLiteral::operator RealLiteral() const { return RealLiteral(num.getValue() / (double)den.getValue()); }
