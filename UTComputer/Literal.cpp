#include <iostream>
#include <sstream> 
#include "Literal.h"
#include "Utility.h"
#include "UTException.h"

Literal::operator IntegerLiteral() const { throw TypeError("Can't cast to IntegerLiteral."); }
Literal::operator RationalLiteral() const { throw TypeError("Can't cast to RationalLiteral."); }
Literal::operator RealLiteral() const { throw TypeError("Can't cast to RealLiteral."); }
Literal::operator ComplexLiteral() const { throw TypeError("Can't cast to ComplexLiteral."); }
Literal::operator ExpressionLiteral() const { throw TypeError("Can't cast to ExpressionLiteral."); }

NumericLiteral::operator ExpressionLiteral() const { return ExpressionLiteral(toString()); }

IntegerLiteral::operator RationalLiteral() const { return RationalLiteral(value, 1); }
IntegerLiteral::operator RealLiteral() const { return RealLiteral(value); }
IntegerLiteral::operator ComplexLiteral() const { return ComplexLiteral(std::make_shared<IntegerLiteral>(*this), std::make_shared<IntegerLiteral>(0)); }

RationalLiteral::operator RealLiteral() const { return RealLiteral(num.getValue() / (double)den.getValue()); }
RationalLiteral::operator ComplexLiteral() const { return ComplexLiteral(std::make_shared<RationalLiteral>(*this), std::make_shared<IntegerLiteral>(0)); }

RealLiteral::operator ComplexLiteral() const { return ComplexLiteral(std::make_shared<IntegerLiteral>(*this), std::make_shared<IntegerLiteral>(0)); }
