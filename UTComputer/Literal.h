#pragma once
#include <string>
#include <memory>
#include <vector>

//Note : la littérale atome n'existe pas car elle est une représentation de passage, destinée
//à être remplacée dès évaluation par une littérale, un programme ou une expression.

class IntegerLiteral;
class RationalLiteral;
class RealLiteral;
class ExpressionLiteral;
class ComplexLiteral;

class Operand { 
public:
	virtual std::string toString() const = 0;
}; //A discuter

class Literal : public Operand {
public:
	virtual operator IntegerLiteral();
	virtual operator RationalLiteral();
	virtual operator RealLiteral();
	virtual operator ComplexLiteral();
	virtual operator ExpressionLiteral();
};
class NumericLiteral : public Literal {
public:
	operator ExpressionLiteral() override;
	virtual std::string toString() const = 0;
};
class IntegerLiteral : public NumericLiteral {
	int value;
public:
	explicit IntegerLiteral(int value) : value(value) {}
	int getValue() const { return value; }
	operator RationalLiteral() override;
	operator RealLiteral() override;
	operator IntegerLiteral() override { return *this; }
	std::string toString() const override { return std::to_string(value); }
	bool operator==(int n) const { return value == n; }
};
class RationalLiteral : public NumericLiteral {
	IntegerLiteral num, den;
public:
	RationalLiteral(IntegerLiteral& num, IntegerLiteral& den) : num(num), den(den) {}
	const IntegerLiteral& getNum() const { return num; }
	const IntegerLiteral& getDen() const { return den; }
	operator RealLiteral() override;
	operator RationalLiteral() override { return *this; }
	std::string toString() const override { return num.toString() + '/' + den.toString(); }
};
class RealLiteral : public NumericLiteral {
	double value;
public:
	explicit RealLiteral(double value) : value(value) {}
	operator RealLiteral() override { return *this; }
	double getValue() const { return value; }
	std::string toString() const override { return std::to_string(value); }
};
class ComplexLiteral : public NumericLiteral {
	std::shared_ptr<NumericLiteral> re, im; //Existent avant l'application de l'opérateur spécifique, ce n'est pas une composition et on doit pouvoir faire usage du polymorphisme
public:
	ComplexLiteral(std::shared_ptr<NumericLiteral> re, std::shared_ptr<NumericLiteral> im) : re(re), im(im) { }
	const NumericLiteral& getRe() const { return *re; }
	const NumericLiteral& getIm() const { return *im; }
	operator ComplexLiteral() override { return *this; }
	std::string toString() const override { return re->toString() + "$" + im->toString(); }
};
class ExpressionLiteral : public Literal {
	std::string expr;
public:
	ExpressionLiteral(std::string expr) : expr(expr) {}
	operator ExpressionLiteral() override { return *this; }
	std::string toString() const override { return expr; }
	std::string getExpression() const { return expr; }
};

//Pattern Composite
class ProgramLiteral : public Literal {
	std::vector<std::shared_ptr<Operand>> operands;
public:
	std::string toString() const override;
	ProgramLiteral* add(std::shared_ptr<Operand> op) { operands.push_back(op); return this; }
};