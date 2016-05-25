/**
  * @file Operation.h
  * @brief Fichier de référence pour les opérations sur des littérales.
  */

#ifndef OPERATION_H
#define OPERATION_H
#include "Literal.h"
#include "Arguments.h"
#include "Operateurs.h"
#include "LiteralFactory.h"
#include <memory>
#include <vector>
#include <functional>

/**
 * @brief Un objet Operation définit un comportement sur des littérales spécifiques. Elle implémente soit un comportement pour un ensemble de pointeurs
 * de littérale abstraites, soit un comportement pour un ensemble de littérales concrètes. Elle peut implémenter un comportement pour
 * plusieurs types de littérales concrètes. Une opération agit sur des littérales mais peut produire des littérales et des opérateurs.
 * Une classe Operation est implémentée comme "standalone". Dans un souci de modularité, elle ne doit pas faire référence à
 * d'autres objets Operation ou Operator.
 */
class Operation {
public:
    typedef Arguments<std::shared_ptr<Operand>> Result;
    typedef Arguments<std::shared_ptr<Literal>> Generic;
    typedef Arguments<IntegerLiteral> Integers;
    typedef Arguments<RationalLiteral> Rationals;
    typedef Arguments<ComplexLiteral> Complexs;
    typedef Arguments<RealLiteral> Reals;
    typedef Arguments<ExpressionLiteral> Expressions;
    /**
     * @brief Opération générique sur des littérales typées dynamiquement.
     * @details Les sous-classes devraient redéfinir cette méthode dans trois cas :
     *      - L'opération ne tient pas compte du type des opérateurs.
     *      - L'opération DOIT s'effectuer sur des types hétérogènes.
     *      - L'opération souhaite effectuer elle-même les casts nécessaires au traitement.
     * Autrement, il est conseillé de redéfinir les autres méthodes prenant des types homogènes numériques concrets.
     * @arg Ensemble de pointeurs sur Literal wrappées dans un objet Arguments.
     * @exception invalid_argument si non implémenté dans une sous-classe.
     * @return Ensemble résultat de pointeurs sur Operand.
     */
    virtual Result eval(const Generic&);
    /**
     * @brief Opération sur des littérales entières.
     * @arg Ensemble de littérales entières IntegerLiteral wrappées dans un objet Arguments.
     * @exception invalid_argument si non implémenté dans une sous-classe.
     * @return Ensemble résultat de pointeurs sur Operand.
     */
    virtual Result eval(const Integers&);
    /**
     * @brief Opération sur des littérales rationnelles.
     * @arg Ensemble de littérales rationnelles RationalLiteral wrappées dans un objet Arguments.
     * @exception invalid_argument si non implémenté dans une sous-classe.
     * @return Ensemble résultat de pointeurs sur Literal.
     */
    virtual Result eval(const Rationals&);
    /**
     * @brief Opération sur des littérales complexes.
     * @arg Ensemble de littérales complexes ComplexLiteral wrappées dans un objet Arguments.
     * @exception invalid_argument si non implémenté dans une sous-classe.
     * @return Ensemble résultat de pointeurs sur Operand.
     */
    virtual Result eval(const Complexs&);
    /**
     * @brief Opération sur des littérales réelles.
     * @arg Ensemble de littérales réelles RealLiteral wrappées dans un objet Arguments.
     * @exception invalid_argument si non implémenté dans une sous-classe.
     * @return Ensemble résultat de pointeurs sur Operand.
     */
    virtual Result eval(const Reals&);
    /**
     * @brief Opération sur des littérales expressions.
     * @arg Ensemble de littérales réelles ExpressionLiteral wrappées dans un objet Arguments.
     * @exception invalid_argument si non implémenté dans une sous-classe.
     * @return Ensemble résultat de pointeurs sur Operand.
     */
    virtual Result eval(const Expressions&);
    /**
     * @brief Destructeur virtuel.
     */
    virtual ~Operation() {}
};

/**
 * @brief Un objet PlusOperation implémente l'opération d'addition.
 * @details Les littérales supportées sont IntegerLiteral, RationalLiteral, RealLiteral et ComplexLiteral.
 */
class PlusOperation : public Operation {
public:
    Result eval(const Integers& args) override;
    Result eval(const Rationals& args) override;
    Result eval(const Reals& args) override;
    Result eval(const Complexs& args) override;
};

class MoinsOperation : public Operation {

};

class ComplexOperation : public Operation {
    Result eval(const Generic& args);
};

class STOOperarion : public Operation {
public:
    Result eval(const Generic& args) override;
};

#endif
