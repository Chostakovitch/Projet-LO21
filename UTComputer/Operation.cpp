#include "Operation.h"
#include "OperatorManager.h"
#include "Manager.h"
#include "UTException.h"

Operation::Generic Operation::applyOperation(const std::shared_ptr<const Operation> &op, Operation::Generic args) {
    //Tentative d'application de l'opération générique
    try {
        return op->eval(args);
    } catch(UTException& e) {
        //Sinon, on tente de caster successivement les littérales par ordre de généralité
        try {
            return op->eval((Operation::Integers)args);
        } catch(UTException& e1) {
            e1.add(e);
            try {
                return op->eval((Operation::Rationals)args);
            } catch(UTException& e2) {
                e2.add(e1);
                try {
                    return op->eval((Operation::Reals)args);
                } catch(UTException& e3) {
                    e3.add(e2);
                    try {
                        return op->eval((Operation::Complexs)args);
                    } catch(UTException& e4) {
                        e4.add(e3);
                        try {
                            return op->eval((Operation::Expressions)args);
                        } catch(UTException& e5) {
                            throw e5.add(e4);
                        }
                    }
                }
            }
        }
    }
}

Operation::Generic Operation::eval(Operation::Generic) const {
    throw UTException("Generic operation not implemented.");
}

Operation::Generic Operation::eval(Operation::Integers) const {
    throw UTException("Operation not implemented for IntegerLiteral.");
}
Operation::Generic Operation::eval(Operation::Rationals) const {
    throw UTException("Operation not implemented for RationalLiteral.");
}
Operation::Generic Operation::eval(Operation::Complexs) const {
    throw UTException("Operation not implemented for ComplexLiteral.");
}

Operation::Generic Operation::eval(Operation::Reals) const {
    throw UTException("Operation not implemented for RealLiteral.");
}

Operation::Generic Operation::eval(Operation::Expressions) const {
    throw UTException("Operation not implemented for ExpressionLiteral.");
}
Operation::Generic PlusOperation::eval(Operation::Rationals args) const {
    IntegerLiteral a = args.front()->getNum(), b = args.front()->getDen(), c = args.back()->getNum(), d = args.back()->getDen();

    //Calcul du résultat via le dénominateur commun : la simplification est déléguée à la fabrique.
    int num = a.getValue() * d.getValue() + b.getValue() * c.getValue();
    int den = b.getValue() * d.getValue();
    return {LiteralFactory::getInstance().makeLiteral(num, den)};
}

Operation::Generic PlusOperation::eval(Operation::Reals args) const {
    return {LiteralFactory::getInstance().makeLiteral(args.front()->getValue() + args.back()->getValue())};
}

Operation::Generic PlusOperation::eval(Operation::Complexs args) const {
    std::shared_ptr<Literal> new_re, new_im;
    std::shared_ptr<NumericLiteral> res_re, res_im;
    //Appel du plus sur les autres opérations
    new_re = applyOperation(shared_from_this(), {args.front()->getRe(), args.back()->getRe()}).front();
    new_im = applyOperation(shared_from_this(), {args.front()->getIm(), args.back()->getIm()}).front();
    res_re = std::dynamic_pointer_cast<NumericLiteral>(new_re);
    res_im = std::dynamic_pointer_cast<NumericLiteral>(new_im);
    if(!(res_re && res_im)) throw UTException("Result of operation on real or imaginary part incompatible with complexs.");
    return {LiteralFactory::getInstance().makeLiteral(res_re, res_im)};
}

Operation::Generic MulOperation::eval(Operation::Rationals args) const {
    IntegerLiteral a = args.front()->getNum(), b = args.front()->getDen(), c = args.back()->getNum(), d = args.back()->getDen();
    int num = a.getValue() * c.getValue();
    int den = b.getValue() * d.getValue();
    return Operation::Generic{LiteralFactory::getInstance().makeLiteral(num, den)};
}

Operation::Generic MulOperation::eval(Operation::Reals args) const {
    return {LiteralFactory::getInstance().makeLiteral(args.front()->getValue() * args.back()->getValue())};
}

Operation::Generic MulOperation::eval(Operation::Complexs args) const {
    std::shared_ptr<Literal> new_re, new_im;
    std::shared_ptr<NumericLiteral> res_re, res_im;
    new_re = applyOperation(std::make_shared<MoinsOperation>(), \
        {applyOperation(shared_from_this(), {args.front()->getRe(), args.back()->getRe()}).front(), \
         applyOperation(shared_from_this(), {args.front()->getIm(), args.back()->getIm()}).front()}).front();
    new_im = applyOperation(std::make_shared<PlusOperation>(), \
        {applyOperation(shared_from_this(), {args.front()->getRe(), args.back()->getIm()}).front(), \
         applyOperation(shared_from_this(), {args.front()->getIm(), args.back()->getRe()}).front()}).front();
    res_re = std::dynamic_pointer_cast<NumericLiteral>(new_re);
    res_im = std::dynamic_pointer_cast<NumericLiteral>(new_im);
    if(!(res_re && res_im)) throw UTException("Result of operation on real or imaginary part incompatible with complexs.");
    return {LiteralFactory::getInstance().makeLiteral(res_re, res_im)};
}

Operation::Generic ComplexOperation::eval(Operation::Generic args) const {
    auto re = std::dynamic_pointer_cast<NumericLiteral>(args.front());
    auto im = std::dynamic_pointer_cast<NumericLiteral>(args.back());
    if(re && im) return Operation::Generic{LiteralFactory::getInstance().makeLiteral(re, im)};
    throw UTException("Unable to make ComplexLiteral from other operands than NumericLiteral's");
}

Operation::Generic NegOperation::eval(Operation::Generic args) const {
    args.push_back(LiteralFactory::getInstance().makeLiteral(-1));
    return applyOperation(std::make_shared<MulOperation>(), args);
}

Operation::Generic MoinsOperation::eval(Operation::Generic args) const {
    args.back() = applyOperation(std::make_shared<NegOperation>(), {args.back()}).front();
    return applyOperation(std::make_shared<PlusOperation>(), args);
}

Operation::Generic DivOperation::eval(Operation::Rationals args) const {
    args.back() = LiteralFactory::getInstance().makeLiteral(args.back()->getDen().getValue(), args.back()->getNum().getValue());
    return applyOperation(std::make_shared<MulOperation>(), args);
}

Operation::Generic DivOperation::eval(Operation::Reals args) const {

}

Operation::Generic DivOperation::eval(Operation::Complexs args) const {

}
