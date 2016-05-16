/**
  * @file OperatorManager.h
  * @brief Fichier de référence pour la gestion des opérateurs et des opérations.
  */

#ifndef OPERATORMANAGER_H
#define OPERATORMANAGER_H
#include <vector>
#include <memory>
#include <string>

class Operator;
class Literal;
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
     * @brief Foncteur utilisé comme prédicat pour identifier un opérateur dans une collection d'opérateurs par son symbole.
     */
    struct FindOperator {
        std::string symbol;
        FindOperator(const std::string& symbol) : symbol(symbol) { }
        bool operator()(const std::shared_ptr<Operator>& op);
    };

public:
	OperatorManager(const OperatorManager&) = delete;
	void operator=(const OperatorManager&) = delete;
    static const OperatorManager& getInstance();
    const std::shared_ptr<Operator>& getOperator(const std::string& opcode) const;
    std::vector<std::shared_ptr<Literal>> dispatchOperation(std::shared_ptr<Operator> op, Arguments<std::shared_ptr<Literal>> args) const;
};
#endif
