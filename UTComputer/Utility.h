#ifndef UTILITY_H
#define UTILITY_H

#include <string>

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
}
#endif
