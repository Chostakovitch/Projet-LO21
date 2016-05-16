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
     * @brief Vaut true si l'opérateur est __symbolique__, false s'il est __parenthésé__.
     * @details Etant donné un opérateur de symbole S, il est symbolique s'il est binaire, d'un seul caractère et si son opération s'écrit L1 S L2 (infixe).
     * Il est parenthésé si son opération s'écrit S(L1, ...) (préfixe parenthésé).
     */
    bool symbolic;
    /**
     * @brief Entier représentant la priorité relative de l'opérateur.
     * @details Cette priorité devrait valoir -1 si l'opérateur est parenthésé, un nombre positif s'il est symbolique.
     */
    int priority;
public:
    /**
     * @brief Constructeur d'objet Operator.
     * @param symbol Chaîne de caractère représentant l'opérateur.
     * @param arity Entier positif représentant le nombre d'opérandes sur lequel l'opérateur s'applique.
     * @param operation Pointeur sur Operation, définissant le comportement de l'opérateur.
     */
    Operator(std::string symbol, unsigned int arity, std::shared_ptr<Operation> operation, int priority = -1) : \
        symbol(symbol), arity(arity), operation(operation), priority(priority) { symbolic = priority >= 0 && arity == 2 && symbol.length() == 1; }
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
     * @brief Accesseur pour priority.
     * @return Nombre entier.
     */
    int getPriority() { return priority; }
    /**
     * @brief Accesseur pour isSymbolic.
     * @return Booléen.
     */
    bool isSymbolic() { return symbolic; }
    /**
     * @brief Retourn le symbole de l'opérateur.
     * @return Objet string.
     */
	std::string toString() const override { return symbol; }
};
#endif
