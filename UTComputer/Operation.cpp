#include <complex>

#include "Operation.h"
#include "OperatorManager.h"
#include "Manager.h"
#include "UTException.h"
#include "ExpressionParser.h"

Operation::Result Operation::apply(const std::shared_ptr<const Operation> &op, Operation::Generic args) {
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
                            e5.add(e4);
                            try {
                                return op->eval((Operation::Programs)args);
                            } catch(UTException& e6) {
                                throw e6.add(e5);
                            }
                        }
                    }
                }
            }
        }
    }
}

Operation::Result Operation::eval(Operation::Generic) const {
    throw UTException("Generic operation not implemented.");
}

Operation::Result Operation::eval(Operation::Integers) const {
    throw UTException("Operation not implemented for IntegerLiteral.");
}
Operation::Result Operation::eval(Operation::Rationals) const {
    throw UTException("Operation not implemented for RationalLiteral.");
}
Operation::Result Operation::eval(Operation::Complexs) const {
    throw UTException("Operation not implemented for ComplexLiteral.");
}

Operation::Result Operation::eval(Operation::Reals) const {
    throw UTException("Operation not implemented for RealLiteral.");
}
Operation::Result Operation::eval(Operation::Expressions) const {
    throw UTException("Operation not implemented for ExpressionLiteral.");
}

Operation::Result Operation::eval(Operation::Programs args) const {
     throw UTException("Operation not implemented for ProgramLiteral.");
}

Operation::Result PlusOperation::eval(Operation::Rationals args) const {
    int a = args.front()->getNum(), b = args.front()->getDen(), c = args.back()->getNum(), d = args.back()->getDen();

    //Calcul du résultat via le dénominateur commun : la simplification est déléguée à la fabrique.
    int num = a * d + b * c;
    int den = b * d;
    return {LiteralFactory::getInstance().makeLiteral(num, den)};
}

Operation::Result PlusOperation::eval(Operation::Complexs args) const {
    return {LiteralFactory::getInstance().makeLiteral((Operation::StdComplex)*args.front() + (Operation::StdComplex)*args.back())};
}

Operation::Result MulOperation::eval(Operation::Rationals args) const {
    int a = args.front()->getNum(), b = args.front()->getDen(), c = args.back()->getNum(), d = args.back()->getDen();
    return {LiteralFactory::getInstance().makeLiteral(a * c, b * d)};
}

Operation::Result MulOperation::eval(Operation::Complexs args) const {
    return {LiteralFactory::getInstance().makeLiteral((Operation::StdComplex)*args.front() * (Operation::StdComplex)*args.back())};
}

Operation::Result ComplexOperation::eval(Operation::Generic args) const {
    auto re = std::dynamic_pointer_cast<NumericLiteral>(args.front());
    auto im = std::dynamic_pointer_cast<NumericLiteral>(args.back());
    if(re && im) return Operation::Generic{LiteralFactory::getInstance().makeLiteral(re, im)};
    throw UTException("Unable to apply ComplexLiteral from other operands than NumericLiteral's");
}

Operation::Result NegOperation::eval(Operation::Generic args) const {
    args.push_back(LiteralFactory::getInstance().makeLiteral(-1));
    return apply(std::make_shared<MulOperation>(), args);
}

Operation::Result MoinsOperation::eval(Operation::Generic args) const {
    args.back() = std::dynamic_pointer_cast<Literal>(apply(std::make_shared<NegOperation>(), {args.back()}).front());
    return apply(std::make_shared<PlusOperation>(), args);
}

Operation::Result DivOperation::eval(Operation::Rationals args) const {
    if(args.back()->getNum() == 0) throw UTException("Division by 0");
    auto den = LiteralFactory::getInstance().makeLiteral(args.back()->getDen(), args.back()->getNum());
    return apply(std::make_shared<MulOperation>(), {args.front(), den});
}

Operation::Result DivOperation::eval(Operation::Complexs args) const {
    if((RealLiteral)*(args.back()->getRe()) == 0 && (RealLiteral)*(args.back()->getIm()) == 0) throw UTException("Complex infinity");
    return {LiteralFactory::getInstance().makeLiteral((Operation::StdComplex)*args.front() / (Operation::StdComplex)*args.back())};
}

Operation::Result IntDivOperation::eval(Operation::Integers args) const {
    if(*args.back() == 0) throw UTException("Division by 0");
    return {LiteralFactory::getInstance().makeLiteral(*args.front() / *args.back())};
}

Operation::Result ModOperation::eval(Operation::Integers args) const {
    return {LiteralFactory::getInstance().makeLiteral(*args.front() % *args.back())};
}

Operation::Result PowOperation::eval(Generic args) const {
    //Rationnel
    auto n = (RationalLiteral)*args.front();
    //Puissance entière
    int p = (IntegerLiteral)*args.back();
    return {LiteralFactory::getInstance().makeLiteral(std::pow((int)n.getNum(), p), std::pow((int)n.getDen(), p))};

}

Operation::Result PowOperation::eval(Operation::Complexs args) const {
    return {LiteralFactory::getInstance().makeLiteral(std::pow((Operation::StdComplex)*args.front(), (Operation::StdComplex)*args.back()))};
}

Operation::Result SinOperation::eval(Operation::Complexs args) const {
    return {LiteralFactory::getInstance().makeLiteral(std::sin((Operation::StdComplex)*args.front()))};
}

Operation::Result CosOperation::eval(Operation::Complexs args) const {
    return {LiteralFactory::getInstance().makeLiteral(std::cos((Operation::StdComplex)*args.front()))};
}

Operation::Result TanOperation::eval(Operation::Complexs args) const {
    return {LiteralFactory::getInstance().makeLiteral(std::tan((Operation::StdComplex)*args.front()))};
}

Operation::Result ArcSinOperation::eval(Operation::Complexs args) const {
    return {LiteralFactory::getInstance().makeLiteral(std::asin((Operation::StdComplex)*args.front()))};
}

Operation::Result ArcCosOperation::eval(Operation::Complexs args) const {
    return {LiteralFactory::getInstance().makeLiteral(std::acos((Operation::StdComplex)*args.front()))};
}

Operation::Result ArcTanOperation::eval(Operation::Complexs args) const {
    return {LiteralFactory::getInstance().makeLiteral(std::atan((Operation::StdComplex)*args.front()))};
}

Operation::Result SqrtOperation::eval(Operation::Rationals args) const {
    double intpart;
    double num = std::sqrt((int)args.front()->getNum());
    double den = std::sqrt((int)args.front()->getDen());
    //Si les résultats sont entiers on peut fabriquer une littérale rationnelle et conserver l'écriture fractionnaire
    if(std::modf(num, &intpart) == 0.0 && std::modf(den, &intpart) == 0.0) return {LiteralFactory::getInstance().makeLiteral((int)num, (int)den)};
    return {LiteralFactory::getInstance().makeLiteral(num/den)};
}

Operation::Result SqrtOperation::eval(Operation::Complexs args) const {
    return {LiteralFactory::getInstance().makeLiteral(std::sqrt((Operation::StdComplex)*args.front()))};
}

Operation::Result ExpOperation::eval(Operation::Complexs args) const {
    return {LiteralFactory::getInstance().makeLiteral(std::exp((Operation::StdComplex)*args.front()))};
}

Operation::Result LnOperation::eval(Operation::Complexs args) const {
    return {LiteralFactory::getInstance().makeLiteral(std::log((Operation::StdComplex)*args.front()))};
}

Operation::Result NumOperation::eval(Operation::Rationals args) const {
    return {LiteralFactory::getInstance().makeLiteral(args.front()->getNum())};
}

Operation::Result DenOperation::eval(Operation::Rationals args) const {
    return {LiteralFactory::getInstance().makeLiteral(args.front()->getDen())};
}

Operation::Result ReOperation::eval(Operation::Complexs args) const {
    return {args.front()->getRe()};
}

Operation::Result ImOperation::eval(Operation::Complexs args) const{
    return {args.front()->getIm()};
}

Operation::Result ArgOperation::eval(Operation::Complexs args) const {
    return{LiteralFactory::getInstance().makeLiteral(std::arg((Operation::StdComplex)*args.front()))};
}

Operation::Result ModuleOperation::eval(Operation::Complexs args) const {
    return{LiteralFactory::getInstance().makeLiteral(std::norm((Operation::StdComplex)*args.front()))};
}

Operation::Result StoOperation::eval(Operation::Generic args) const {
    if(!std::dynamic_pointer_cast<ExpressionLiteral>(args.back())) throw TypeError("An identifier must be an expression.", args);
    Manager::getInstance().addIdentifier((std::dynamic_pointer_cast<ExpressionLiteral>(args.back()))->getExpression(), args.front());
    return {};
}

Operation::Result ForgetOperation::eval(Operation::Generic args) const {
    if(!std::dynamic_pointer_cast<ExpressionLiteral>(args.front())) throw TypeError("An identifier must be an expression.", args);
    try {
        Manager::getInstance().getIdentifier(args.front()->toString());
    } catch (UTException e) {
        throw UTException("This identifier doesn't exist.");
    }
    Manager::getInstance().deleteIdentifier(args.front()->toString());
    return {};
}

Operation::Result DupOperation::eval(Operation::Generic args) const {
    return {LiteralFactory::getInstance().makeLiteralFromString(args.front()->toString()), args.front()};
}

Operation::Result DropOperation::eval(Operation::Generic) const {
    return {};
}

Operation::Result SwapOperation::eval(Operation::Generic args) const {
    return {args.back(), args.front()};
}

Operation::Result UndoOperation::eval(Operation::Generic) const {
    Manager::getInstance().undo();
    return {};
}

Operation::Result RedoOperation::eval(Operation::Generic) const {
    Manager::getInstance().redo();
    return {};
}

Operation::Result ClearOperation::eval(Operation::Generic) const {
    Manager::getInstance().clearPile();
    return {};
}

Operation::Result LastopOperation::eval(Operation::Generic) const {
    return {Manager::getInstance().getLastop()};
}

Operation::Result LastargsOperation::eval(Operation::Generic) const {
    return Manager::getInstance().getLastargs();
}

Operation::Result EqualOperation::eval(Operation::Complexs args) const {
    return {LiteralFactory::getInstance().makeLiteral((Operation::StdComplex)*args.front() == (Operation::StdComplex)*args.back())};
}

Operation::Result NotEqualOperation::eval(Operation::Complexs args) const {
    return {LiteralFactory::getInstance().makeLiteral((Operation::StdComplex)*args.front() != (Operation::StdComplex)*args.back())};
}

Operation::Result BelowOrEqual::eval(Operation::Reals args) const {
    return {LiteralFactory::getInstance().makeLiteral(*args.front() <= *args.back())};
}

Operation::Result AboveOrEqual::eval(Operation::Reals args) const {
    return {LiteralFactory::getInstance().makeLiteral(*args.front() >= *args.back())};
}

Operation::Result Below::eval(Operation::Reals args) const {
    return {LiteralFactory::getInstance().makeLiteral(*args.front() < *args.back())};
}

Operation::Result Above::eval(Operation::Reals args) const {
    return {LiteralFactory::getInstance().makeLiteral(*args.front() > *args.back())};
}

Operation::Result LogicAnd::eval(Operation::Integers args) const {
    return {LiteralFactory::getInstance().makeLiteral(*args.front() && *args.back())};
}

Operation::Result LogicOr::eval(Operation::Integers args) const {
    return {LiteralFactory::getInstance().makeLiteral(*args.front() || *args.back())};
}

Operation::Result LogicNot::eval(Operation::Integers args) const {
    return {LiteralFactory::getInstance().makeLiteral(!*args.front())};
}

Operation::Result Eval::eval(Operation::Complexs args) const {
    return {LiteralFactory::getInstance().makeLiteral(args.front()->getRe(), args.front()->getIm())};
}

Operation::Result Eval::eval(Operation::Expressions args) const {
    auto res = ExpressionParser(args.front()->getExpression()).parse();
    return Operation::Result(res.begin(), res.end()); //Parsing de l'expression
}

Operation::Result Eval::eval(Operation::Programs args) const {
    Manager::getInstance().eval(args.front()->getOperands()); //Evaluation des opérandes de la littérale programme
    return {};
}

Operation::Result IFT::eval(Operation::Generic args) const {
    if(auto value = std::dynamic_pointer_cast<IntegerLiteral>(args.front())) {
        if(*value) return {OperatorManager::getInstance().getEvalOperator(), args.back()}; //Premier argument = true, on provoque l'évaluation du deuxième
        return {};
    }
    throw UTException("First argument can't be interpreted as a integer boolean");
}

Operation::Result IFTE::eval(Operation::Generic args) const {
    if(auto value = std::dynamic_pointer_cast<IntegerLiteral>(args.front())) {
        if(*value) return {OperatorManager::getInstance().getEvalOperator(), args.at(1)}; //Premier argument = true, on provoque l'évaluation du deuxième
        return {OperatorManager::getInstance().getEvalOperator(), args.back()}; //Sinon on provoque l'évaluation du troisième
    }
    throw UTException("First argument can't be interpreted as a integer boolean");
}

Operation::Result WHILE::eval(Operation::Generic args) const {
    std::shared_ptr<Operand> res;
    std::shared_ptr<IntegerLiteral> value;
    //Tant que le premier argument s'évalue en un entier représentant true, on évalue le dernier argument
    auto v = apply(OperatorManager::getInstance().getEvalOperator()->getOperation(), {args.front()});
    while(res = apply(OperatorManager::getInstance().getEvalOperator()->getOperation(), {args.front()}).front(), (value = std::dynamic_pointer_cast<IntegerLiteral>(res)) && *value) {
        Manager::getInstance().eval({OperatorManager::getInstance().getEvalOperator(), args.back()});
    }
    return {};
}
