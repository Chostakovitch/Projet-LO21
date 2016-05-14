#include "Operation.h"
#include "OperatorManager.h"

Arguments<std::shared_ptr<Literal>> Operation::eval(Arguments<IntegerLiteral>&) {
	throw std::invalid_argument("Not implemented."); 
}
Arguments<std::shared_ptr<Literal>> Operation::eval( Arguments<RationalLiteral>&) {
	throw std::invalid_argument("Not implemented."); 
}
Arguments<std::shared_ptr<Literal>> Operation::eval(Arguments<RealLiteral>&) {
	throw std::invalid_argument("Not implemented."); 
}

Arguments<std::shared_ptr<Literal>> PlusOperation::eval(Arguments<IntegerLiteral>& args) {
    return Arguments<std::shared_ptr<Literal>>{LiteralFactory::getInstance().makeLiteral(args.at(0).getValue() + args.at(1).getValue())};
}

Arguments<std::shared_ptr<Literal>> PlusOperation::eval(Arguments<RationalLiteral>& args) {
	IntegerLiteral a = args.at(0).getNum(), b = args.at(0).getDen(), c = args.at(1).getNum(), d = args.at(1).getDen();
	int e = a.getValue() * d.getValue() + b.getValue() * c.getValue(), f = b.getValue() * d.getValue();
    return Arguments<std::shared_ptr<Literal>>{LiteralFactory::getInstance().makeLiteral(e, f)};
}

Arguments<std::shared_ptr<Literal>> PlusOperation::eval(Arguments<RealLiteral>& args) {
    return Arguments<std::shared_ptr<Literal>>{LiteralFactory::getInstance().makeLiteral(args.at(0).getValue() + args.at(1).getValue())};
}
