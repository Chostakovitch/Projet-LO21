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
     * @brief Remplit l'itérateur out si le prédicat renvoie true, pour chaque élément de first jusqu'à last.
     * @param first Itérateur sur le début d'une collection.
     * @param last Itérateur sur la fin d'une collection.
     * @param out Itérateur sur la collection de sortie.
     * @param pred Prédicat unaire.
     */
    template <typename FIterator, typename OIterator, typename Predicate>
    void select_iterator(FIterator first, FIterator last, OIterator out, Predicate pred) {
        while(first != last) {
            if(pred(*first)) *out++ = first;
            ++first;
        }
    }

    /**
     * @brief Produit la concaténation des éléments externes à l'ensemble délimité par deux caractères.
     * @param s Chaîne à traiter.
     * @param left Caractère de délimitation à gauche
     * @param right Caractère de délimitation à droite.
     * @return La concaténation des chaînes externes ou bien la chaîne elle-même si les délimiteurs n'ont pas été trouvés
     */
    std::string getOutside(std::string s, char left, char right);
}
#endif
