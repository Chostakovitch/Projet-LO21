#include <iostream>
#include <memory>
#include <sstream> 
#include "Literal.h"
#include "Utility.h"
#include "UTException.h"

Literal::operator IntegerLiteral() const {
    //Si la littérale pointe déjà vers le type de destination, on a pas besoin de caster l'objet concret.
    if(auto lit = dynamic_cast<const IntegerLiteral*>(this)) return *lit;
    throw TypeError(std::string("Can't cast to IntegerLiteral : ") + toString());
}
Literal::operator RationalLiteral() const {
    if(auto lit = dynamic_cast<const RationalLiteral*>(this)) return *lit;
    throw TypeError(std::string("Can't cast to RationalLiteral : ") + toString());
}
Literal::operator RealLiteral() const {
    if(auto lit = dynamic_cast<const RealLiteral*>(this)) return *lit;
    throw TypeError(std::string("Can't cast to RealLiteral : ") + toString());
}
Literal::operator ComplexLiteral() const {
    if(auto lit = dynamic_cast<const ComplexLiteral*>(this)) return *lit;
    throw TypeError(std::string("Can't cast to ComplexLiteral : ") + toString());
}
Literal::operator ExpressionLiteral() const {
    if(auto lit = dynamic_cast<const ExpressionLiteral*>(this)) return *lit;
    throw TypeError(std::string("Can't cast to ExpressionLiteral : ") + toString());
}

NumericLiteral::operator ExpressionLiteral() const { return ExpressionLiteral(toString()); }

IntegerLiteral::operator RationalLiteral() const { return RationalLiteral(value, 1); }
IntegerLiteral::operator RealLiteral() const { return RealLiteral(value); }
IntegerLiteral::operator ComplexLiteral() const { return ComplexLiteral(std::make_shared<IntegerLiteral>(*this), std::make_shared<IntegerLiteral>(0)); }

RationalLiteral::operator RealLiteral() const { return RealLiteral(num.getValue() / (double)den.getValue()); }
RationalLiteral::operator ComplexLiteral() const { return ComplexLiteral(std::make_shared<RationalLiteral>(*this), std::make_shared<IntegerLiteral>(0)); }

RealLiteral::operator ComplexLiteral() const { return ComplexLiteral(std::make_shared<RealLiteral>(value), std::make_shared<IntegerLiteral>(0)); }
