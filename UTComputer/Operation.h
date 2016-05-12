#ifndef OPERATION_H
#define OPERATION_H
#include "Literal.h"
#include "Operateurs.h"
#include "LiteralFactory.h"
#include <memory>

class Operation {
public:
    virtual Arguments<std::shared_ptr<Literal>> eval(LiteralFactory& factory, const Arguments<IntegerLiteral>& args);
    virtual Arguments<std::shared_ptr<Literal>> eval(LiteralFactory& factory, const Arguments<RationalLiteral>& args);
    virtual Arguments<std::shared_ptr<Literal>> eval(LiteralFactory& factory, const Arguments<RealLiteral>& args);
	virtual ~Operation() {}
};

class PlusOperation : public Operation {
public:
    Arguments<std::shared_ptr<Literal>> eval(LiteralFactory& factory, const Arguments<IntegerLiteral>& args) override;
    Arguments<std::shared_ptr<Literal>> eval(LiteralFactory& factory, const Arguments<RationalLiteral>& args) override;
    Arguments<std::shared_ptr<Literal>> eval(LiteralFactory& factory, const Arguments<RealLiteral>& args) override;
};
#endif
