#pragma once
#include <string>

class IntegerLiteral;
class RationalLiteral;
class RealLiteral;
class ExpressionLiteral;

class Literal {
public:
	virtual std::string toString() const = 0;
	virtual operator IntegerLiteral();
	virtual operator RationalLiteral();
	virtual operator RealLiteral();
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
	IntegerLiteral(int value) : value(value) {}
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
	RationalLiteral(int num, int den) : num(num), den(den) {}
	const IntegerLiteral& getNum() const { return num; }
	const IntegerLiteral& getDen() const { return den; }
	operator RealLiteral() override;
	operator RationalLiteral() override { return *this; }
	std::string toString() const override { return num.toString() + '/' + den.toString(); }
};
class RealLiteral : public NumericLiteral {
	double value;
public:
	RealLiteral(double value) : value(value) {}
	operator RealLiteral() override { return *this; }
	double getValue() const { return value; }
	std::string toString() const override { return std::to_string(value); }
};
class ExpressionLiteral : public Literal {
	std::string expr;
public:
	ExpressionLiteral(std::string expr) : expr(expr) {}
	operator ExpressionLiteral() override { return *this; }
	std::string toString() const override { return expr; }
	std::string getExpression() const { return expr; }
};