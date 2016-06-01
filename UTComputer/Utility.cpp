#include "Utility.h"
#include <cctype>
#include <algorithm>
#include <cstdlib> //avec <cmath>, problème d'ambiguité sur certains compilateurs
#include <cctype>

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
    size_t leftPos = s.find_first_of(left);
    size_t rightPos = s.find_last_of(right);
    //Il existe une sous-chaîne délimitée
    if(leftPos != std::string::npos && rightPos != std::string::npos) {
        return s.substr(0, leftPos) + ' ' + s.substr(rightPos, s.size() - rightPos);
    }
    return s;
}

bool Utility::isSymbol(char c) {
    return !std::isalnum(c) && std::isgraph(c);
}

bool Utility::isAtom(std::string atom) {
    return !atom.empty() && std::isupper(atom.at(0)) && std::find_if(atom.begin(), atom.end(), [](char c) { return !(std::isdigit(c) || std::isupper(c)); }) == atom.end();
}
