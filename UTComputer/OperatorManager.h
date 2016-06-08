/**
  * @file OperatorManager.h
  * @brief Fichier de référence pour la gestion des opérateurs et des opérations.
  */

#ifndef OPERATORMANAGER_H
#define OPERATORMANAGER_H
#include <vector>
#include <memory>
#include <string>
#include <functional>
#include <iostream>

#include "Operation.h"

class Operand;
class Operator;
class Literal;
class ExpressionLiteral;
template <typename T>
class Arguments;

/**
 * @brief Singleton manageant la création et l'accès aux opérateurs, ainsi que le dispatch des opérations.
 * @details L'instance d'OperatorManager contient des instances d'objets Operator.
 * Elle permet aussi de sélectionner la bonne opération à effectuer selon les opérandes d'entrée.
 */
class OperatorManager
{
    /**
     * @brief Constructeur privé qui crée les instances des opérateurs applicables.
     */
	OperatorManager();
    /**
     * @brief Ensemble des opérateurs applicables.
     */
    std::vector<std::shared_ptr<Operator>> operators;
    /**
     * @brief Symbole utilisé pour l'opérateur de soustraction (utilisé pour le parsing qui ne différencie pas de la négation).
     */
    const std::string minus_symbol;
    /**
     * @brief Pointeur sur l'opérateur utilisé pour l'évalution des programmes (que l'on doit rajouter manuellement pour un atome sur un programme).
     */
    std::shared_ptr<FunctionOperator> evalOperator;
public:
    /**
     * @brief Suppression du constructeur de recopie.
     */
	OperatorManager(const OperatorManager&) = delete;
    /**
     * @brief Suppression de l'opérateur d'affectation.
     */
	void operator=(const OperatorManager&) = delete;
    /**
     * @brief Récupération de l'instance du singleton.
     * @return Référence constante sur OperatorManager.
     */
    static const OperatorManager& getInstance();
    /**
     * @brief Récupération de l'instance d'un opérateur à partir de son symbole, s'il existe.
     * @param opcode Symbole de l'objet Operator à récupérer.
     * @exception invalid_argument si aucun opérateur ne possède le symbole demandé.
     * @return Référence constante sur un shared_ptr sur Operator.
     */
    const std::shared_ptr<Operator>& getOperator(std::string opcode) const;
    /**
     * @brief Accesseur pour minus_symbol.
     * @return std::string représentant l'opérateur de soustraction.
     */
    std::string getMinusSymbol() const { return minus_symbol; }
    /**
     * @brief Accesseur pour evalOperator.
     * @return Pointeur sur Operator représentant l'opérateur d'évaluation de programme.
     */
    const std::shared_ptr<Operator> getEvalOperator() const { return evalOperator; }
    /**
     * @brief Indique si une chaîne représente un opérateur.
     * @param opcode Identifieur à vérifier.
     * @return Booléen.
     */
    bool isOperator(const std::string& opcode) const;
    /**
     * @brief Indique si une chaîne représente un opérateur arithmétique.
     * @param opcode Identifieur à vérifier.
     * @return Booléen.
     */
    bool isArithmeticOperator(const std::string& opcode) const;
    /**
     * @brief Effectue l'opération associée à un opérateur sur des littérales.
     * @details Cette fonction appelle la méthode d'évaluation générique de la classe Operation. S'il y a un problème, on teste des cas particuliers,
     * comme l'opération entre littérales expressions pour des opérateurs symboliques ou les méthodes liées à Memento.
     * @param op Objet Operator à utiliser pour l'opération.
     * @param args Objet Arguments de pointeurs sur Literal représentants les opérandes sur lesquelles agit l'opérateur.
     * @exception invalid_argument Si aucun type englobant n'a été trouvé ou si aucune opération n'est définie pour le type des littérales.
     * @return Objet Arguments de pointeurs sur Operand représentant le(s) résultat(s) de l'opération.
     */
    Arguments<std::shared_ptr<Operand>> dispatchOperation(std::shared_ptr<Operator> op, Arguments<std::shared_ptr<Literal>> args) const;
    /**
     * @brief Effectue une opération entre un ensemble d'objet ExpressionLiteral. L'algorithme ne dépend pas de l'opérateur mais uniquement de
     * son symbole et des autres opérateurs définis, c'est pourquoi elle est définie à part des autres opérations.
     * @param op Pointeur sur Operator.
     * @param args Arguments d'objets ExpressionLiteral.
     * @return Arguments de pointeurs sur Literal.
     */
    std::shared_ptr<ExpressionLiteral> opExpression(std::shared_ptr<Operator> op, const Arguments<std::shared_ptr<ExpressionLiteral>>& args) const;
    std::vector<std::shared_ptr<Operator>> getSymbolicOperators() const;
    std::vector<std::shared_ptr<Operator>> getFunctionOperators() const;
};
#endif
