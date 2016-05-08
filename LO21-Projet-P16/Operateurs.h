#pragma once
#include <map>
#include <iostream>
#include <vector>
#include <algorithm>
#include <type_traits>
#include <memory>

class Literal;
class Operation;

template <typename T>
class Arguments : public std::vector<T> {
	using std::vector<T>::vector;
};

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

class Operator {
	friend class OperatorManager;
	const unsigned int arity;
	std::string symbol;
	const std::shared_ptr<Operation> operation;
	Operator(std::string symbol, unsigned int arity, std::shared_ptr<Operation> operation) : symbol(symbol), arity(arity), operation(operation) { }
};