/**
  * @file Operateurs.h
  * @brief Fichier de référence pour les opérateurs.
  */

#ifndef OPERATEURS_H
#define OPERATEURS_H
#include <memory>

#include "Literal.h" //Obligatoire pour pouvoir hériter d'Operand

class Operation;

/**
 * @brief Un objet Operator est une opérande qui abstrait la notion d'opérateur.
 * @details Une instance d'un objet Operator peut représenter indifféremment un opérateur arithmétique, logique, de pile, de programme, etc.
 * L'abstraction ici consiste à dire qu'un opérateur agit sur un vecteur de littérales et produit un autre vecteur de littérales.
 * On empêche ainsi le couplage entre l'opérateur et la pile par exemple, rendant cette classe utilisable sans dépendance aux autres composants d'UTComputer.
 */
class Operator : public Operand {
    /**
     * @brief Chaîne de caractères représentant l'opérateur.
     */
    std::string symbol;
    /**
     * @brief Arité de l'opérateur, i.e. le nombre d'opérandes sur lequel il s'applique.
     */
    const unsigned int arity;
    /**
     * @brief Pointeur sur objet Operation, qui représente le comportement de l'opérateur.
     */
    std::shared_ptr<Operation> operation;
    /**
     * @brief Vaut true si l'opérateur est __numérique__, false sinon.
     * @details La numéricité d'un opérateur est sémantique et est définie informellement par l'utilisateur de la classe. Un opérateur est
     * numérique s'il effectue un calcul entre opérandes.
     */
    bool numeric;
public:
    /**
     * @brief Constructeur d'objet Operator.
     * @param symbol Chaîne de caractère représentant l'opérateur.
     * @param arity Entier positif représentant le nombre d'opérandes sur lequel l'opérateur s'applique.
     * @param operation Pointeur sur Operation, définissant le comportement de l'opérateur.
     */
    Operator(std::string symbol, unsigned int arity, std::shared_ptr<Operation> operation, bool numeric = false) : \
        symbol(symbol), arity(arity), operation(operation), numeric(numeric) { }
    /**
     * @brief Accesseur pour arity.
     * @return Entier non-signé.
     */
    unsigned int getArity() { return arity; }
    /**
     * @brief Accesseur pour operation.
     * @return Référence constante sur un pointeur sur Operation.
     */
    const std::shared_ptr<Operation>& getOperation() { return operation; }
    /**
     * @brief Accesseur pour numeric.
     * @return Booléen.
     */
    bool isNumeric() { return numeric; }
    /**
     * @brief Retourn le symbole de l'opérateur.
     * @return Objet string.
     */
	std::string toString() const override { return symbol; }
    /**
      * @brief Destructeur virtuel pur avec implémentation pour rendre la classe abstraite.
      */
    ~Operator() = 0;
};

/**
 * @brief Un objet FunctionOperator est un opérateur s'écrivant sous forme préfixe parenthésée.
 */
class FunctionOperator : public Operator {
public:
    using Operator::Operator;
};

/**
 * @brief Un objet SymbolicOperator est un opérateur s'écrivant sous forme infixe.
 * @details L'écriture infixe implique l'existence de la notion de priorité, ce qui le différencie de l'opérateur fonction (préfixe parenthésé).
 */
class SymbolicOperator : public Operator {
    /**
     * @brief Entier positif représentant la priorité relative de l'instance de l'opérateur.
     */
    unsigned int priority;
    /**
     * @brief Vaut true si l'opérateur est associatif à gauche, false sinon.
     */
    bool leftAssociative;
public:
    /**
     * @brief Constructeur d'un opérateur symbolique.
     * @param symbol Symbole.
     * @param arity Arité.
     * @param operation Pointeur sur classe Operation.
     * @param numeric Indique si l'opérateur est numérique (i.e. réalise un calcul).
     * @param priority Priorité relative de l'opérateur.
     */
    SymbolicOperator(std::string symbol, unsigned int arity, std::shared_ptr<Operation> operation, bool numeric, unsigned int priority, bool leftAssociative = true) \
        : Operator(symbol, arity, operation, numeric), priority(priority), leftAssociative(leftAssociative) { }
    /**
     * @brief Accesseur pour priority.
     * @return Entier non-signé.
     */
    unsigned int getPriority() { return priority; }
    /**
     * @brief Accesseur pour leftAssociative.
     * @return Booléen.
     */
    bool isLeftAssociative() { return leftAssociative; }
};

#endif
