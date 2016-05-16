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

std::string Utility::getOutside(std::string s, char left, char right) {
    int leftPos = s.find_first_of(left);
    int rightPos = s.find_first_of(right);
    //Il existe une sous-chaîne délimitée
    if(leftPos != std::string::npos && rightPos != std::string::npos) {
        return s.substr(0, leftPos) + ' ' + s.substr(rightPos, s.size() - rightPos);
    }
    return s;
}
