#include "Utility.h"
#include <cctype>
#include <algorithm>
<<<<<<< HEAD:LO21-Projet-P16/Utility.cpp
#include <cstdlib>
=======
#include <cstdlib> //avec <cmath>, problème d'ambiguité sur certains compilateurs
>>>>>>> 49ee4c93e6a68e70cb1b5f15fc2be9ca4e144321:UTComputer/Utility.cpp

bool Utility::isUnsignedInt(std::string s) {
	return (!s.empty() && std::find_if(s.begin(), s.end(), [](char c) { return !std::isdigit(c); }) == s.end());
}

unsigned int Utility::computeGcd(int num, int den) {
	unsigned int r;
	num = std::abs(num);
	den = std::abs(den);
	while (den != 0) {
		r = num % den;
		num = den;
		den = r;
	}
	return num;
}
