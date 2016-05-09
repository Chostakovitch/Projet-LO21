#pragma once
#include <map>
#include <iostream>
#include <vector>
#include <algorithm>
#include <type_traits>
#include <memory>
#include "Literal.h"

class Operation;

template <typename T>
class Arguments : public std::vector<T> {
	using std::vector<T>::vector;
};

/* A bien noter sur cette classe pour expliquer dans le rapport : on pourrait se demander pourquoi on ne fait pas simplement
un dynamic_cast (ou équivalent pour shared_ptr) : tout simplement parce qu'on souhaite opérer sur des littérales qui sont soeurs
(donc pas de downcast direct) et parce qu'on applique le mécanisme de promotion pour éviter la redondance dans des méthodes de calcul
dont le nombre deviendrait exponentiel (i.e. toutes les combinaisons de types possibles). Il existe certains opérateurs spéciaux (par exemple le "$") 
pour lesquels cela aurait été pertinent, mais le "$" semble plus appartenir à la Factory de littérales qu'autre chose. A voir donc.
*/
template <typename T>
class Arguments<std::shared_ptr<T>> : public std::vector<std::shared_ptr<T>> {
public:
	using std::vector<std::shared_ptr<T>>::vector;
	template <typename U>
	operator Arguments<U>() { //Cast d'un vecteur de pointeurs sur un T vers un vecteur de U (si la conversion existe)
		Arguments<U> dest;
		for (auto arg : *this) dest.push_back(*arg);
		return dest;
	}
};

class Operator : public Operand {
	friend class OperatorManager;
	const unsigned int arity;
	std::string symbol;
	const std::shared_ptr<Operation> operation;
	Operator(std::string symbol, unsigned int arity, std::shared_ptr<Operation> operation) : symbol(symbol), arity(arity), operation(operation) { }
public:
	std::string toString() const override { return symbol; }
};