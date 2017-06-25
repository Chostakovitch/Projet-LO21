#ifndef PILE_H
#define PILE_H

#include <stack>
#include <vector>
#include "Literal.h"

/**
 * @brief La classe Pile sert à stocker des Literal dans une LIFO.
 */
class Pile
{
    /**
     * @brief Vecteur de Literal
     */
    std::vector<std::shared_ptr<Literal>> p;
public:
    /**
     * @brief Fonction retournant la taille de la pile.
     * @return Entier non signé
     */
    unsigned int size () const { return p.size(); }
    /**
     * @brief Test si la pile est vide.
     * @return bool true si la pile est vide, false sinon.
     */
    bool empty() { return p.empty(); }
    /**
     * @brief Dépile le sommet de la pile
     * @return Un shared_ptr de Literal.
     */
    std::shared_ptr<Literal> pop() {
        std::shared_ptr<Literal> temp = p.back();
        p.pop_back();
        return temp;
    }
    /**
     * @brief Empile une litteral sur le sommet de la pile.
     * @param l Un shared_ptr de Literal.
     */
    void push(std::shared_ptr<Literal> l) { p.push_back(l); }

    bool operator==(const Pile& pile) const { return pile.p == p; }
    bool operator!=(const Pile& pile) const { return pile.p != p; }
    /**
     * @brief Accesseur à l'itérateur du début de la pile.
     * @return Itérateur pointant sur le debut de la pile.
     */
    std::vector<std::shared_ptr<Literal>>::const_iterator begin() const { return p.begin(); }
    /**
     * @brief Accesseur à l'itérateur de fin de la pile.
     * @return Itérateur pointant sur la fin de la pile.
     */
    std::vector<std::shared_ptr<Literal>>::const_iterator end() const { return p.end(); }
};

#endif // PILE_H
