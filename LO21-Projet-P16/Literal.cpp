#include <iostream>
#include <memory>
#include "Literal.h"
#include "Utility.h"

Literal::operator IntegerLiteral() { throw std::bad_cast(); }
Literal::operator RationalLiteral() { throw std::bad_cast(); }
Literal::operator RealLiteral() { throw std::bad_cast(); }
Literal::operator ExpressionLiteral() { throw std::bad_cast(); }

NumericLiteral::operator ExpressionLiteral() { return ExpressionLiteral(toString()); }

IntegerLiteral::operator RationalLiteral() { return RationalLiteral(value, 1); }
IntegerLiteral::operator RealLiteral() { return RealLiteral(value); }

RationalLiteral::operator RealLiteral() { return RealLiteral(num.getValue() / (double)den.getValue()); }