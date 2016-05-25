/**
  * @file Operation.h
  * @brief Fichier de référence pour les opérations sur des littérales.
  */

#ifndef OPERATION_H
#define OPERATION_H
#include "Literal.h"
#include "Operateurs.h"
#include "LiteralFactory.h"
#include <memory>
#include <vector>
#include <functional>

/**
 * @brief Un objet Operation définit un comportement sur des littérales spécifiques. Elle implémente soit un comportement pour un ensemble de pointeurs
 * de littérale abstraites, soit un comportement pour un ensemble de littérales concrètes. Elle peut implémenter un comportement pour
 * plusieurs types de littérales concrètes. Une opération agit sur des littérales mais peut produire des littérales et des opérateurs.
 */
class Operation {
public:
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
    virtual Arguments<std::shared_ptr<Operand>> eval(const Arguments<std::shared_ptr<Literal>>&);
    /**
     * @brief Opération sur des littérales entières.
     * @arg Ensemble de littérales entières IntegerLiteral wrappées dans un objet Arguments.
     * @exception invalid_argument si non implémenté dans une sous-classe.
     * @return Ensemble résultat de pointeurs sur Operand.
     */
    virtual Arguments<std::shared_ptr<Operand>> eval(const Arguments<IntegerLiteral>&);
    /**
     * @brief Opération sur des littérales rationnelles.
     * @arg Ensemble de littérales rationnelles RationalLiteral wrappées dans un objet Arguments.
     * @exception invalid_argument si non implémenté dans une sous-classe.
     * @return Ensemble résultat de pointeurs sur Literal.
     */
    virtual Arguments<std::shared_ptr<Operand>> eval(const Arguments<RationalLiteral>&);
    /**
     * @brief Opération sur des littérales complexes.
     * @arg Ensemble de littérales complexes ComplexLiteral wrappées dans un objet Arguments.
     * @exception invalid_argument si non implémenté dans une sous-classe.
     * @return Ensemble résultat de pointeurs sur Operand.
     */
    virtual Arguments<std::shared_ptr<Operand>> eval(const Arguments<ComplexLiteral>&);
    /**
     * @brief Opération sur des littérales réelles.
     * @arg Ensemble de littérales réelles RealLiteral wrappées dans un objet Arguments.
     * @exception invalid_argument si non implémenté dans une sous-classe.
     * @return Ensemble résultat de pointeurs sur Operand.
     */
    virtual Arguments<std::shared_ptr<Operand>> eval(const Arguments<RealLiteral>&);
    /**
     * @brief Opération sur des littérales expressions.
     * @arg Ensemble de littérales réelles ExpressionLiteral wrappées dans un objet Arguments.
     * @exception invalid_argument si non implémenté dans une sous-classe.
     * @return Ensemble résultat de pointeurs sur Operand.
     */
    virtual Arguments<std::shared_ptr<Operand>> eval(const Arguments<ExpressionLiteral>&);
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
    Arguments<std::shared_ptr<Operand>> eval(const Arguments<IntegerLiteral>& args) override;
    Arguments<std::shared_ptr<Operand>> eval(const Arguments<RationalLiteral>& args) override;
    Arguments<std::shared_ptr<Operand>> eval(const Arguments<RealLiteral>& args) override;
};

class STOOperarion : public Operation {
public:
    Arguments<std::shared_ptr<Operand>> eval(const Arguments<std::shared_ptr<Literal>>& args) override;
};

#endif
