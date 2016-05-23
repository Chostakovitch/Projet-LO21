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
    template <typename U>
    /**
     * @brief Applique l'opération demandée après avoir casté les arguments en type T.
     * @param op Pointeur sur Operation.
     * @param args Pointeurs sur Literal.
     * @exception bad_cast si aucune conversion entre Literal et T n'existe.
     * @exception invalid_argument si aucune opération n'est définie pour le type T.
     * @return Résultat de l'opération.
     */
    static Arguments<std::shared_ptr<Operand>> applyOperation(std::shared_ptr<Operation> op, Arguments<std::shared_ptr<Literal>> args) {
        return op->eval((Arguments<U>)args);
    }
    /**
     * @brief Vecteur de fonctions d'application d'opération sur des littérales numériques.
     * @details Ce vecteur définit un ensemble d'instances du template applyOperation, en priorisant l'ordre des casts en __littérales numériques__.
     * Usuellement, les littérales les plus spécialisées sont essayées en premier, et les plus générales en dernier.
     */
    std::vector<std::function<Arguments<std::shared_ptr<Operand>>(std::shared_ptr<Operation>, Arguments<std::shared_ptr<Literal>>)>> numericPriority;

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
    const std::shared_ptr<Operator>& getOperator(const std::string& opcode) const;
    bool isOperator(const std::string& opcode) const;
    /**
     * @brief Effectue l'opération associée à un opérateur sur des littérales.
     * @details Cette fonction appelle la classe Operation associée à l'opérateur passé en arguments, et détermine la surcharge d'évaluation
     * à appeler en fonction du type réelle des littérales. Pour ce faire, on essaye de promouvoir les littérales passées en argument des plus
     * spécialisées aux plus générales. Dès que l'on a trouvé un type englobant toutes les littérales, on appelle la fonction d'évaluation
     * avec un objet Arguments sur littérales concrètes.
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
     std::shared_ptr<ExpressionLiteral> opExpression(std::shared_ptr<Operator> op, const Arguments<ExpressionLiteral>& args) const;
};
#endif
