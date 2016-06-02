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
 * @brief Un objet Operation définit un comportement sur des littérales spécifiques.
 * @details Elle implémente soit un comportement pour un ensemble de pointeurs
 * de littérale abstraites, soit un comportement pour un ensemble de littérales concrètes. Elle peut implémenter un comportement pour
 * plusieurs types de littérales concrètes.
 *
 * On hérite de std::enable_shared_from_this afin de pouvoir renvoyer un shared_ptr sur this en tout sécurité, i.e. sans
 * compromettre la gestion des propriétaires des pointeurs.
 */
class Operation : public std::enable_shared_from_this<Operation> {
protected:
    typedef Arguments<std::shared_ptr<Literal>> Generic;
    typedef Arguments<std::shared_ptr<IntegerLiteral>> Integers;
    typedef Arguments<std::shared_ptr<RationalLiteral>> Rationals;
    typedef Arguments<std::shared_ptr<ComplexLiteral>> Complexs;
    typedef Arguments<std::shared_ptr<RealLiteral>> Reals;
    typedef Arguments<std::shared_ptr<ExpressionLiteral>> Expressions;
    typedef std::complex<double> StdComplex;
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
    virtual Generic eval(Generic) const;
    /**
     * @brief Opération sur des littérales entières.
     * @arg Ensemble de littérales entières IntegerLiteral wrappées dans un objet Arguments.
     * @exception invalid_argument si non implémenté dans une sous-classe.
     * @return Ensemble résultat de pointeurs sur Operand.
     */
    virtual Generic eval(Integers) const;
    /**
     * @brief Opération sur des littérales rationnelles.
     * @arg Ensemble de littérales rationnelles RationalLiteral wrappées dans un objet Arguments.
     * @exception invalid_argument si non implémenté dans une sous-classe.
     * @return Ensemble résultat de pointeurs sur Literal.
     */
    virtual Generic eval(Rationals) const;
    /**
     * @brief Opération sur des littérales complexes.
     * @arg Ensemble de littérales complexes ComplexLiteral wrappées dans un objet Arguments.
     * @exception invalid_argument si non implémenté dans une sous-classe.
     * @return Ensemble résultat de pointeurs sur Operand.
     */
    virtual Generic eval(Complexs) const;
    /**
     * @brief Opération sur des littérales réelles.
     * @arg Ensemble de littérales réelles RealLiteral wrappées dans un objet Arguments.
     * @exception invalid_argument si non implémenté dans une sous-classe.
     * @return Ensemble résultat de pointeurs sur Operand.
     */
    virtual Generic eval(Reals) const;
    /**
     * @brief Opération sur des littérales expressions.
     * @arg Ensemble de littérales réelles ExpressionLiteral wrappées dans un objet Arguments.
     * @exception invalid_argument si non implémenté dans une sous-classe.
     * @return Ensemble résultat de pointeurs sur Operand.
     */
    virtual Generic eval(const Expressions) const;
    /**
     * @brief Destructeur virtuel.
     */
public:
    /**
     * @brief Dispatch des opérandes vers la bonne opération via des casts.
     * @return Résultat de l'opération.
     */
    static Generic apply(const std::shared_ptr<const Operation> &op, Generic args);
    virtual ~Operation() {}
};

/**
 * @brief Un objet PlusOperation implémente l'opération d'addition.
 * @details Les littérales supportées sont RationalLiteral et ComplexLiteral.
 */
class PlusOperation : public Operation {
public:
    Generic eval(Rationals args) const override;
    Generic eval(Complexs args) const override;
};

/**
 * @brief Un objet MulOperation implémente l'opération de multiplication.
 * @details Les littérales supportées sont RationalLiteral et ComplexLiteral.
 */
class MulOperation : public Operation {
    Generic eval(Rationals args) const override;
    Generic eval(Complexs args) const override;
};

/**
 * @brief Un objet NegOperation implémente l'opération de négation. (en terme de multiplication par -1)
 * @details Toutes les littérales sont supportées.
 */
class NegOperation : public Operation {
    Generic eval(Generic args) const override;
};

/**
 * @brief Un objet MoinsOperation implémente l'opération de soustraction (en terme de négation et d'addition).
 * @details Toutes les littérales sont supportées.
 */
class MoinsOperation : public Operation {
    Generic eval(Generic args) const override;
};

/**
 * @brief Un objet ComplexOperation permet de produire un nombre complexe.
 * @details Les littérales numériques sont supportées.
 */
class ComplexOperation : public Operation {
    Generic eval(Generic args) const override;
};

/**
 * @brief Un objet DivOperation implémente l'opération de division (rationnelle)
 * @details Les littérales supportées sont RationalLiteral et ComplexLiteral.
 */
class DivOperation : public Operation {
    Generic eval(Rationals args) const override;
    Generic eval(Complexs args) const override;
};

/**
 * @brief Un objet IntDivOperation implémente l'opération de division entière.
 * @details Seuls les IntegerLiteral sont supportés.
 */
class IntDivOperation : public Operation {
    Generic eval(Integers args) const override;
};

/**
 * @brief Un objet ModOperation implémente l'opération de modulo.
 * @details Seules les IntegerLiteral sont supportés.
 */
class ModOperation : public Operation {
    Generic eval(Integers args) const override;
};

/**
 * @brief Un objet PowOperation implémente l'opération de puissance.
 * @details Les littérales supportées sont le couple (RationalLiteral, IntegerLiteral), et ComplexLiteral.
 */
class PowOperation : public Operation {
    Generic eval(Generic args) const override;
    Generic eval(Complexs args) const override;
};

/**
 * @brief Un objet SinOperation implémente le sinus (radians).
 * @details Seuls les ComplexLiteral sont supportés.
 */
class SinOperation : public Operation {
    Generic eval(Complexs args) const override;
};

/**
 * @brief Un objet CosOperation implémente le cosinus (radians).
 * @details Seuls les ComplexLiteral sont supportés.
 */
class CosOperation : public Operation {
    Generic eval(Complexs args) const override;
};

/**
 * @brief Un objet TanOperation implémente la tangeante (radians).
 * @details Seuls les ComplexLiteral sont supportés.
 */
class TanOperation : public Operation {
    Generic eval(Complexs args) const override;
};

/**
 * @brief Un objet ArcSinOperation implémente l'inverse du sinus (radians).
 * @details Seuls les ComplexLiteral sont supportés.
 */
class ArcSinOperation : public Operation {
    Generic eval(Complexs args) const override;
};

/**
 * @brief Un objet ArcCosOperation implémente l'inverse du cosinus (radians).
 * @details Seuls les ComplexLiteral sont supportés.
 */
class ArcCosOperation : public Operation {
    Generic eval(Complexs args) const override;
};

/**
 * @brief Un objet ArcTanOperation implémente l'inverse de la tangeante (radians).
 * @details Seuls les ComplexLiteral sont supportés.
 */
class ArcTanOperation : public Operation {
    Generic eval(Complexs args) const override;
};

/**
 * @brief Un objet SqrtOperation implémente la racine carrée.
 * @details Les littérales supportées sont RationalLiteral et ComplexLiteral.
 */
class SqrtOperation : public Operation {
    Generic eval(Rationals args) const override;
    Generic eval(Complexs args) const override;
};

/**
 * @brief Un objet ExpOperation implémente l'exponentielle.
 * @details Seuls les ComplexLiteral sont supportés.
 */
class ExpOperation : public Operation {
    Generic eval(Complexs args) const override;
};

/**
 * @brief Un objet ExpOperation implémente le logarithme néperien.
 * @details Seuls les ComplexLiteral sont supportés.
 */
class LnOperation : public Operation {
    Generic eval(Complexs args) const override;
};

/**
 * @brief Un objet NumOperation renvoie le numérateur d'un rationnel (a fortiori la valeur d'un entier après cast).
 * @details Seuls les RationalLiteral sont supportés.
 */
class NumOperation : public Operation {
    Generic eval(Rationals args) const override;
};

/**
 * @brief Un objet DenOperation renvoie le dénominateur d'un rationnel (a fortiori 1 pour un entier après cast).
 * @details Seuls les RationalLiteral sont supportés.
 */
class DenOperation : public Operation {
    Generic eval(Rationals args) const override;
};

/**
 * @brief Un objet ReOperation renvoie la partie réelle d'un complexe (a fortiori toutes les autres littérales numériques après cast).
 * @details Seuls les ComplexLiteral sont supportés.
 */
class ReOperation : public Operation {
    Generic eval(Complexs args) const override;
};

/**
 * @brief Un objet ImOperation renvoie la partie imaginaire d'un complexe (a fortiori 0 pour toutes les autres littérales numériques après cast).
 * @details Seuls les ComplexLiteral sont supportés.
 */
class ImOperation : public Operation {
    Generic eval(Complexs args) const override;
};

/**
 * @brief Un objet ArgOperation renvoie l'argument d'un complexe.
 * @details Seuls les ComplexLiteral sont supportés.
 */
class ArgOperation : public Operation {
    Generic eval(Complexs args) const override;
};

/**
 * @brief Un objet ModuleOperation renvoie module d'un complexe.
 * @details Seuls les ComplexLiteral sont supportés.
 */
class ModuleOperation : public Operation {
    Generic eval(Complexs args) const override;
};

/**
 * @brief Un objet StoOperation enregistre un identificateur référençant une litteral.
 * @details Une litteral atome doit étre fournie pour la création de l'identificateur.
 */
class StoOperation : public Operation {
    Generic eval(Generic args) const override;
};

/**
 * @brief Un objet ForgetOperation supprime un identificateur référençant une litteral.
 */
class ForgetOperation : public Operation {
    Generic eval(Generic args) const override;
};

#endif
