#include <complex>

#include "Operation.h"
#include "OperatorManager.h"
#include "Manager.h"
#include "UTException.h"

Operation::Generic Operation::apply(const std::shared_ptr<const Operation> &op, Operation::Generic args) {
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
    int a = args.front()->getNum(), b = args.front()->getDen(), c = args.back()->getNum(), d = args.back()->getDen();

    //Calcul du résultat via le dénominateur commun : la simplification est déléguée à la fabrique.
    int num = a * d + b * c;
    int den = b * d;
    return {LiteralFactory::getInstance().makeLiteral(num, den)};
}

Operation::Generic PlusOperation::eval(Operation::Complexs args) const {
    return {LiteralFactory::getInstance().makeLiteral((Operation::StdComplex)*args.front() + (Operation::StdComplex)*args.back())};
}

Operation::Generic MulOperation::eval(Operation::Rationals args) const {
    int a = args.front()->getNum(), b = args.front()->getDen(), c = args.back()->getNum(), d = args.back()->getDen();
    return {LiteralFactory::getInstance().makeLiteral(a * c, b * d)};
}

Operation::Generic MulOperation::eval(Operation::Complexs args) const {
    return {LiteralFactory::getInstance().makeLiteral((Operation::StdComplex)*args.front() * (Operation::StdComplex)*args.back())};
}

Operation::Generic ComplexOperation::eval(Operation::Generic args) const {
    auto re = std::dynamic_pointer_cast<NumericLiteral>(args.front());
    auto im = std::dynamic_pointer_cast<NumericLiteral>(args.back());
    if(re && im) return Operation::Generic{LiteralFactory::getInstance().makeLiteral(re, im)};
    throw UTException("Unable to apply ComplexLiteral from other operands than NumericLiteral's");
}

Operation::Generic NegOperation::eval(Operation::Generic args) const {
    args.push_back(LiteralFactory::getInstance().makeLiteral(-1));
    return apply(std::make_shared<MulOperation>(), args);
}

Operation::Generic MoinsOperation::eval(Operation::Generic args) const {
    args.back() = apply(std::make_shared<NegOperation>(), {args.back()}).front();
    return apply(std::make_shared<PlusOperation>(), args);
}

Operation::Generic DivOperation::eval(Operation::Rationals args) const {
    auto den = LiteralFactory::getInstance().makeLiteral(args.back()->getDen(), args.back()->getNum());
    return apply(std::make_shared<MulOperation>(), {args.front(), den});
}

Operation::Generic DivOperation::eval(Operation::Complexs args) const {
    return {LiteralFactory::getInstance().makeLiteral((Operation::StdComplex)*args.front() / (Operation::StdComplex)*args.back())};
}

Operation::Generic IntDivOperation::eval(Operation::Integers args) const {
    return {LiteralFactory::getInstance().makeLiteral(*args.front() / *args.back())};
}

Operation::Generic ModOperation::eval(Operation::Integers args) const {
    return {LiteralFactory::getInstance().makeLiteral(*args.front() % *args.back())};
}

Operation::Generic PowOperation::eval(Generic args) const {
    //Rationnel
    auto n = (RationalLiteral)*args.front();
    //Puissance entière
    int p = (IntegerLiteral)*args.back();
    return {LiteralFactory::getInstance().makeLiteral(std::pow((int)n.getNum(), p), std::pow((int)n.getDen(), p))};

}

Operation::Generic PowOperation::eval(Operation::Complexs args) const {
    return {LiteralFactory::getInstance().makeLiteral(std::pow((Operation::StdComplex)*args.front(), (Operation::StdComplex)*args.back()))};
}

Operation::Generic SinOperation::eval(Operation::Complexs args) const {
    return {LiteralFactory::getInstance().makeLiteral(std::sin((Operation::StdComplex)*args.front()))};
}

Operation::Generic CosOperation::eval(Operation::Complexs args) const {
    return {LiteralFactory::getInstance().makeLiteral(std::cos((Operation::StdComplex)*args.front()))};
}

Operation::Generic TanOperation::eval(Operation::Complexs args) const {
    return {LiteralFactory::getInstance().makeLiteral(std::tan((Operation::StdComplex)*args.front()))};
}

Operation::Generic ArcSinOperation::eval(Operation::Complexs args) const {
    return {LiteralFactory::getInstance().makeLiteral(std::asin((Operation::StdComplex)*args.front()))};
}

Operation::Generic ArcCosOperation::eval(Operation::Complexs args) const {
    return {LiteralFactory::getInstance().makeLiteral(std::acos((Operation::StdComplex)*args.front()))};
}

Operation::Generic ArcTanOperation::eval(Operation::Complexs args) const {
    return {LiteralFactory::getInstance().makeLiteral(std::atan((Operation::StdComplex)*args.front()))};
}

Operation::Generic SqrtOperation::eval(Operation::Rationals args) const {
    double intpart;
    double num = std::sqrt((int)args.front()->getNum());
    double den = std::sqrt((int)args.front()->getDen());
    //Si les résultats sont entiers on peut fabriquer une littérale rationnelle et conserver l'écriture fractionnaire
    if(std::modf(num, &intpart) == 0.0 && std::modf(den, &intpart) == 0.0) return {LiteralFactory::getInstance().makeLiteral((int)num, (int)den)};
    return {LiteralFactory::getInstance().makeLiteral(num/den)};
}

Operation::Generic SqrtOperation::eval(Operation::Complexs args) const {
    return {LiteralFactory::getInstance().makeLiteral(std::sqrt((Operation::StdComplex)*args.front()))};
}

Operation::Generic ExpOperation::eval(Operation::Complexs args) const {
    return {LiteralFactory::getInstance().makeLiteral(std::exp((Operation::StdComplex)*args.front()))};
}

Operation::Generic LnOperation::eval(Operation::Complexs args) const {
    return {LiteralFactory::getInstance().makeLiteral(std::log((Operation::StdComplex)*args.front()))};
}

Operation::Generic NumOperation::eval(Operation::Rationals args) const {
    return {LiteralFactory::getInstance().makeLiteral(args.front()->getNum())};
}

Operation::Generic DenOperation::eval(Operation::Rationals args) const {
    return {LiteralFactory::getInstance().makeLiteral(args.front()->getDen())};
}

Operation::Generic ReOperation::eval(Operation::Complexs args) const {
    return {args.front()->getRe()};
}

Operation::Generic ImOperation::eval(Operation::Complexs args) const{
    return {args.front()->getIm()};
}

Operation::Generic ArgOperation::eval(Operation::Complexs args) const {
    return{LiteralFactory::getInstance().makeLiteral(std::arg((Operation::StdComplex)*args.front()))};
}

Operation::Generic ModuleOperation::eval(Operation::Complexs args) const {
    return{LiteralFactory::getInstance().makeLiteral(std::norm((Operation::StdComplex)*args.front()))};
}

Operation::Generic StoOperation::eval(Generic args) const {
    if(!std::dynamic_pointer_cast<ExpressionLiteral>(args.front())) throw TypeError("An identifier must be an expression.", args);
    Manager::getInstance().addIdentifier(args.back()->toString(), args.front());
    return {};
}

Operation::Generic ForgetOperation::eval(Generic args) const {
    // TEST
    return {};
}
