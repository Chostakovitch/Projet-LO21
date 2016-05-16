#include "Utility.h"
#include <cctype>
#include <algorithm>
#include <cstdlib> //avec <cmath>, problème d'ambiguité sur certains compilateurs

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
