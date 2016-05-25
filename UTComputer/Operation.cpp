#include "Operation.h"
#include "OperatorManager.h"
#include "Manager.h"
#include "UTException.h"

Operation::Result Operation::eval(const Operation::Generic&) {
    throw UTException("Generic operation not implemented.");
}

Operation::Result Operation::eval(const Operation::Integers&) {
    throw UTException("Operation not implemented for IntegerLiteral.");
}
Operation::Result Operation::eval(const Operation::Rationals&) {
    throw UTException("Operation not implemented for RationalLiteral.");
}
Operation::Result Operation::eval(const Operation::Complexs&) {
    throw UTException("Operation not implemented for ComplexLiteral.");
}

Operation::Result Operation::eval(const Operation::Reals&) {
    throw UTException("Operation not implemented for RealLiteral.");
}

Operation::Result Operation::eval(const Operation::Expressions&) {
    throw UTException("Operation not implemented for ExpressionLiteral.");
}

Operation::Result PlusOperation::eval(const Operation::Integers& args) {
    return Operation::Result{LiteralFactory::getInstance().makeLiteral(args.at(0).getValue() + args.at(1).getValue())};
}

Operation::Result PlusOperation::eval(const Operation::Rationals& args) {
	IntegerLiteral a = args.at(0).getNum(), b = args.at(0).getDen(), c = args.at(1).getNum(), d = args.at(1).getDen();

    //Calcul du résultat via le dénominateur commun : la simplification est déléguée à la fabrique.
	int e = a.getValue() * d.getValue() + b.getValue() * c.getValue(), f = b.getValue() * d.getValue();
    return Operation::Result{LiteralFactory::getInstance().makeLiteral(e, f)};
}

Operation::Result PlusOperation::eval(const Operation::Reals& args) {
    return Operation::Result{LiteralFactory::getInstance().makeLiteral(args.at(0).getValue() + args.at(1).getValue())};
}

Operation::Result PlusOperation::eval(const Operation::Complexs& args) {
    Operation::Generic re{args.at(0).getRe(), args.at(1).getRe()};
    Operation::Generic im{args.at(0).getIm(), args.at(1).getIm()};
    std::shared_ptr<Operand> new_re, new_im;
    std::shared_ptr<NumericLiteral> res_re, res_im;
    try {
        new_re = eval((Operation::Integers)re).at(0);
    } catch(UTException& e1) {
        try {
            new_re = eval((Operation::Rationals)re).at(0);
        } catch(UTException& e2) {
            try {
                new_re = eval((Operation::Reals)re).at(0);
            } catch(UTException& e3) { throw UTException("Can't perform PlusOperation on the real part of complexs").add(e3).add(e2).add(e1); }
        }
    }
    try {
        new_im = eval((Operation::Integers)im).at(0);
    } catch(UTException& e1) {
        try {
            new_im = eval((Operation::Rationals)im).at(0);
        } catch(UTException& e2) {
            try {
                new_im = eval((Operation::Reals)im).at(0);
            } catch(UTException& e3) { throw UTException("Can't perform PlusOperation on the imaginary part of complexs").add(e3).add(e2).add(e1); }
        }
    }
    res_re = std::dynamic_pointer_cast<NumericLiteral>(new_re);
    res_im = std::dynamic_pointer_cast<NumericLiteral>(new_im);
    if(!(res_re && res_im)) throw UTException("Result of operation on real or imaginary part incompatible with complexs.");
    return Operation::Result{LiteralFactory::getInstance().makeLiteral(res_re, res_im)};
}

Operation::Result STOOperarion::eval(const Operation::Generic& args) {
    // Verifier qu'on a bien une expression
    ExpressionLiteral exp = ExpressionLiteral(*args.at(1).get());
    Manager::getInstance().addIdentifier(exp.toString(),args.at(0));
    return Operation::Result{};
}

Operation::Result ComplexOperation::eval(const Operation::Generic& args) {
    auto re = std::dynamic_pointer_cast<NumericLiteral>(args.at(0));
    auto im = std::dynamic_pointer_cast<NumericLiteral>(args.at(1));
    if(re && im) return Operation::Result{LiteralFactory::getInstance().makeLiteral(re, im)};
    throw UTException("Unable to make ComplexLiteral from other operands than NumericLiteral's");
}
