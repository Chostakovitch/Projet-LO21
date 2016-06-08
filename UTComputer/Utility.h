#ifndef UTILITY_H
#define UTILITY_H

#include <string>
#include "UTException.h"

/**
 * @brief Namespace contenant des fonctions utilitaires.
 */
namespace Utility {
    /**
     * @brief Calcule le PGCD de deux nombres entiers.
     * @param num Premier nombre.
     * @param den Deuxième nombre.
     * @return PGCD(num, den).
     */
    unsigned int computeGcd(int num, int den);

    /**
     * @brief Produit la concaténation des éléments externes à l'ensemble délimité par deux caractères.
     * @param s Chaîne à traiter.
     * @param left Caractère de délimitation à gauche
     * @param right Caractère de délimitation à droite.
     * @return La concaténation des chaînes externes ou bien la chaîne elle-même si les délimiteurs n'ont pas été trouvés
     */
    std::string getOutside(std::string s, char left, char right);

    /**
     * @brief Indique si un caractère est un symbole affichable, hors lettres et chiffres.
     * @param c Caractère à valider.
     * @return Booléen.
     */
    bool isSymbol(char c);
    /**
     * @brief Indique si une chaîne est une atome, i.e. un mot commençant par une majuscule et contenant des chiffres et des majuscules
     * @param atom Chaîne à valider.
     * @return Booléen.
     */
    bool isAtom(std::string atom);
    /**
     * @brief Parsing d'une chaîne en autre type T
     * @param s Instance du type T
     * @return T
     */
    template <typename T>
    T stringToOther(const std::string& s) {
        std::istringstream iss(s);
        T d;
        char c;
        if(!(iss >> d) || iss >> c ) throw UTException("Impossible to cast (bad format or trailing char)");
        return d;
    }
}
#endif
