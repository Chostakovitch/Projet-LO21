﻿#include "Operation.h"
#include "OperatorManager.h"
#include "Manager.h"

Arguments<std::shared_ptr<Operand> > Operation::eval(const Arguments<std::shared_ptr<Literal>> &) {
    throw std::invalid_argument("Not implemented.");
}

Arguments<std::shared_ptr<Operand>> Operation::eval(const Arguments<IntegerLiteral>&) {
	throw std::invalid_argument("Not implemented."); 
}
Arguments<std::shared_ptr<Operand>> Operation::eval(const Arguments<RationalLiteral>&) {
	throw std::invalid_argument("Not implemented."); 
}
Arguments<std::shared_ptr<Operand>> Operation::eval(const Arguments<ComplexLiteral>&) {
    throw std::invalid_argument("Not implemented.");
}

Arguments<std::shared_ptr<Operand>> Operation::eval(const Arguments<RealLiteral>&) {
    throw std::invalid_argument("Not implemented.");
}

Arguments<std::shared_ptr<Operand>> Operation::eval(const Arguments<ExpressionLiteral>&) {
    throw std::invalid_argument("Not implemented.");
}

Arguments<std::shared_ptr<Operand>> PlusOperation::eval(const Arguments<IntegerLiteral>& args) {
    return Arguments<std::shared_ptr<Operand>>{LiteralFactory::getInstance().makeLiteral(args.at(0).getValue() + args.at(1).getValue())};
}

Arguments<std::shared_ptr<Operand>> PlusOperation::eval(const Arguments<RationalLiteral>& args) {
	IntegerLiteral a = args.at(0).getNum(), b = args.at(0).getDen(), c = args.at(1).getNum(), d = args.at(1).getDen();

    //Calcul du résultat via le dénominateur commun : la simplification est déléguée à la fabrique.
	int e = a.getValue() * d.getValue() + b.getValue() * c.getValue(), f = b.getValue() * d.getValue();
    return Arguments<std::shared_ptr<Operand>>{LiteralFactory::getInstance().makeLiteral(e, f)};
}

Arguments<std::shared_ptr<Operand>> PlusOperation::eval(const Arguments<RealLiteral>& args) {
    return Arguments<std::shared_ptr<Operand>>{LiteralFactory::getInstance().makeLiteral(args.at(0).getValue() + args.at(1).getValue())};
}

Arguments<std::shared_ptr<Operand>> STOOperarion::eval(const Arguments<std::shared_ptr<Literal>>& args) {
    // Verifier qu'on a bien une expression
    //Manager::addIdentifier()
    return Arguments<std::shared_ptr<Operand>>{};
}




