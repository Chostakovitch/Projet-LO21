#ifndef OPERATION_H
#define OPERATION_H
#include "Literal.h"
#include "Operateurs.h"
#include "LiteralFactory.h"
#include <memory>

class Operation {
public:
    virtual Arguments<std::shared_ptr<Literal>> eval(Arguments<IntegerLiteral>& args);
    virtual Arguments<std::shared_ptr<Literal>> eval(Arguments<RationalLiteral>& args);
    virtual Arguments<std::shared_ptr<Literal>> eval(Arguments<RealLiteral>& args);
	virtual ~Operation() {}
};

class PlusOperation : public Operation {
public:
    Arguments<std::shared_ptr<Literal>> eval(Arguments<IntegerLiteral>& args) override;
    Arguments<std::shared_ptr<Literal>> eval(Arguments<RationalLiteral>& args) override;
    Arguments<std::shared_ptr<Literal>> eval(Arguments<RealLiteral>& args) override;
};
#endif
