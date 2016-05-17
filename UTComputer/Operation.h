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

/**
 * @brief Un objet Operation définit un comportement sur des littérales spécifiques. Elle implémente des méthodes de calculs pour
 * plusieurs types de littérales concrètes.
 */
class Operation {
public:
    /**
     * @brief Opération sur des littérales entières.
     * @arg Ensemble de littérales entières IntegerLiteral. wrappées dans un objet Arguments.
     * @exception invalid_argument si non implémenté dans une sous-classe.
     * @return Ensemble résultat de pointeurs sur Literal.
     */
    virtual Arguments<std::shared_ptr<Literal>> eval(const Arguments<IntegerLiteral>&);
    /**
     * @brief Opération sur des littérales entières.
     * @arg Ensemble de littérales rationnelles RationalLiteral wrappées dans un objet Arguments.
     * @exception invalid_argument si non implémenté dans une sous-classe.
     * @return Ensemble résultat de pointeurs sur Literal.
     */
    virtual Arguments<std::shared_ptr<Literal>> eval(const Arguments<RationalLiteral>&);
    /**
     * @brief Opération sur des littérales entières.
     * @arg Ensemble de littérales complexes ComplexLiteral wrappées dans un objet Arguments.
     * @exception invalid_argument si non implémenté dans une sous-classe.
     * @return Ensemble résultat de pointeurs sur Literal.
     */
    virtual Arguments<std::shared_ptr<Literal>> eval(const Arguments<ComplexLiteral>&);
    /**
     * @brief Opération sur des littérales entières.
     * @arg Ensemble de littérales réelles RealLiteral wrappées dans un objet Arguments.
     * @exception invalid_argument si non implémenté dans une sous-classe.
     * @return Ensemble résultat de pointeurs sur Literal.
     */
    virtual Arguments<std::shared_ptr<Literal>> eval(const Arguments<RealLiteral>&);
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
    Arguments<std::shared_ptr<Literal>> eval(const Arguments<IntegerLiteral>& args) override;
    Arguments<std::shared_ptr<Literal>> eval(const Arguments<RationalLiteral>& args) override;
    Arguments<std::shared_ptr<Literal>> eval(const Arguments<RealLiteral>& args) override;
};

class STOOperarion : public Operation {
    Arguments<std::shared_ptr<Literal>> eval(const Arguments<IntegerLiteral>& args) override;
    Arguments<std::shared_ptr<Literal>> eval(const Arguments<RationalLiteral>& args) override;
    Arguments<std::shared_ptr<Literal>> eval(const Arguments<RealLiteral>& args) override;
};

#endif
