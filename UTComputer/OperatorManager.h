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
        /**
         * @brief Symbole de l'objet Operator à identifier.
         */
        std::string symbol;
        /**
         * @brief Constructeur d'objet FindOperator.
         * @param symbol Symbole de l'opérateur à identifier.
         */
        FindOperator(const std::string& symbol) : symbol(symbol) { }
        /**
         * @brief Opérateur fonction qui compare le symbole de l'objet Operator en paramètre et le symbole courant.
         * @param op Pointeur sur objet Operator à comparer.
         * @return true si le symbole est identique, false sinon.
         */
        bool operator()(const std::shared_ptr<Operator>& op);
    };

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
    /**
     * @brief Effectue l'opération associée à un opérateur sur des littérales.
     * @details Cette fonction appelle la classe Operation associée à l'opérateur passé en arguments, et détermine la surcharge d'évaluation
     * à appeler en fonction du type réelle des littérales. Pour ce faire, on essaye de promouvoir les littérales passées en argument des plus
     * spécialisées aux plus générales. Dès que l'on a trouvé un type englobant toutes les littérales, on appelle la fonction d'évaluation
     * avec un objet Arguments sur littérales concrètes.
     * @param op Objet Operator à utiliser pour l'opération.
     * @param args Objet Arguments de pointeurs sur Literal représentants les opérandes sur lesquelles agit l'opérateur.
     * @exception invalid_argument Si aucun type englobant n'a été trouvé ou si aucune opération n'est définie pour le type des littérales.
     * @return Objet Arguments de pointeurs sur Literal représentant le(s) résultat(s) de l'opération.
     */
    std::vector<std::shared_ptr<Literal>> dispatchOperation(std::shared_ptr<Operator> op, Arguments<std::shared_ptr<Literal>> args) const;
};
#endif
