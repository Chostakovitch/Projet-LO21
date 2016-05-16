/**
  * @file CompositeLiteral Fichier de référence pour toutes les littérales dépendant d'autres objets externes.
  */

#ifndef COMPOSITELITERAL_H
#define COMPOSITELITERAL_H

#include "Literal.h"
#include "Operateurs.h" //Obligatoire pour que le compilateur connaisse la relation d'héritage entre Operand et Operator

/**
 * @brief Un objet ProgramLiteral représente une suite d'opérandes ordonnées.
 * @details Cette suite d'opérandes constitue un algorithme qui ne s'évalue pas en un résultat particulier. Un programme étant aussi
 * une opérande, on peut référencer des sous-programmes.
 * Cette classe utilise le design pattern __Composite__.
 */
class ProgramLiteral : public Literal {
    /**
     * @brief Vecteur de pointeurs sur objets Operand représentant les membres du programme.
     */
    std::vector<std::shared_ptr<Operand>> operands;
public:
    /**
     * @brief Ajout d'une opérande à la fin du vecteur
     * @param op Pointeur sur objet Operand
     */
    void add(std::shared_ptr<Operand> op) { operands.push_back(op); }
    std::string toString() const override;
};

#endif
