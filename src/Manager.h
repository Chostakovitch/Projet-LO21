#ifndef MANAGER_H
#define MANAGER_H

#include <map>
#include <vector>
#include <memory>
#include <stack>
#include <iostream>
#include "Settings.h"
#include "Pile.h"
#include "OperatorManager.h"

class Literal;
class Settings;
class Operand;
class Operator;

/**
 * @brief La classe Memento permet de gardé en mémoire un état de la classe Manager.
 */
class Memento {
private:
    /**
     * @brief Sauvegarde de la liste associative des identifiers d'un état du Manager.
     */
    std::map<const std::string, std::shared_ptr<Literal>> identifiers;
    /**
     * @brief Sauvegarde de la pile d'un état du Manager.
     */
    Pile pile;
    /**
     * @brief Sauvegarde des options d'un état du Manager.
     */
    Settings settings;
    /**
     * @brief Sauvegarde du dernier opérateur utilisé d'un état du Manager.
     */
    std::shared_ptr<Operator> lastop;
    /**
     * @brief Sauvegarde du vecteur des derniers arguments utilisés d'un état du Manager.
     */
    Arguments<std::shared_ptr<Literal>> lastargs;
public:
    /**
     * @brief Constructeur public de la classe Memento.
     * @param i Liste associative de chaine de caractères et de litterale à enregistrer.
     * @param p Pile de litterals à enregistrer.
     * @param s Options à enregistrer.
     * @param lastop Dernière opération à enregistrer.
     * @param lastargs Vecteur des derniers arguments à enregistrer.
     */
    Memento (const std::map<const std::string, std::shared_ptr<Literal>>& i,
             const Pile& p, const Settings& s,
             std::shared_ptr<Operator> lastop,
             Arguments<std::shared_ptr<Literal>> lastargs):
        identifiers(i), pile(p), settings(s), lastop(lastop), lastargs(lastargs) {}
    /**
     * @brief Accesseur au tableau d'identifieurs enregistré dans le Memento.
     * @return La liste associative d'identifieurs.
     */
    std::map<const std::string, std::shared_ptr<Literal>> getIdentifiers() const { return identifiers; }
    /**
     * @brief Accesseur a la pile enregistré dans le Memento.
     * @return Pile de litterals.
     */
    const Pile& getPile() const { return pile; }
    /**
     * @brief Accesseur aux options enregistré dans le Memento.
     * @return Options
     */
    const Settings& getSettings() const { return settings; }
    /**
     * @brief Accesseur au dernier opérateur utilisé.
     * @return  Dernier opérateur utilisé.
     */
    const std::shared_ptr<Operator>& getLastop() const { return lastop; }
    /**
     * @brief Accesseur a la liste des dernières litterales utilisées.
     * @return La liste des dernières litterales utilisées.
     */
    const Arguments<std::shared_ptr<Literal>> getLastargs() const { return lastargs; }

    friend class Manager;
};

/**
 * @brief Singleton manageant le stockage de la pile, des identifieurs et le calcul.
 */
class Manager
{
    /**
     * @brief Map de chaine de caratères et de litteral représenrant les identifieurs.
     */
    std::map<const std::string, std::shared_ptr<Literal>> identifiers;
    /**
     * @brief Pile de litteral.
     */
    Pile pile;
    /**
     * @brief Options de l'application : nombre de ligne de la pile affiché, bip pour le message et affichage du clavier clickable.
     */
    Settings settings;
    /**
     * @brief Dernier opérateur évalué par la classe.
     */
    std::shared_ptr<Operator> lastop;
    /**
     * @brief Liste des dernières arguments évalués par la classe
     */
    Arguments<std::shared_ptr<Literal>> lastargs;

    //Memento :
    /**
     * @brief Vecteur de Memento pour la sauvegarde des états de la classe.
     */
    std::vector<std::shared_ptr<Memento>> backup;
    /**
     * @brief Entier représentant la position de l'état actuel de la classe dans la liste de Memento.
     */
    unsigned int currentState;
    /**
     * @brief Fonction restorant l'état du Manager selon le Memento.
     * @param Memento contenant l'état du Manager à restorer.
     */
    void restoreState(std::shared_ptr<Memento> memento);

    /**
     * @brief Constructeur vide de Manager en privé qui crée l'unique instance du singleton.
     */
    Manager();
public:
    /**
     * @brief Suppression du constructeur de recopie.
     */
    Manager(const Manager&) = delete;
    /**
     * @brief Suppression de l'opérateur d'affectation.
     */
    void operator= (const Manager&) = delete;
    /**
     * @brief Récupération de l'instance du singleton.
     * @return Référence constante sur Manager.
     */
    static Manager& getInstance();
    /**
     * @brief Récupération d'un identifier à partir de sa clé, s'il existe.
     * @exception ParsingError si l'identifieur n'existe pas.
     * @param k Chaine de caractères représentant la clé.
     * @return Référence constante sur un shared_ptr sur Literal.
     */
    const std::shared_ptr<Literal>& getIdentifier(const std::string& k) const;
    /**
     * @brief Accesseur aux options du Manager;
     * @exception ParsingError si l'identifieur n'existe pas.
     * @return Référence constante sur Settings.
     */
    Settings& getSettings() { return settings; }
    /**
     * @brief Récupération de la liste associative d'identifieurs du Manager.
     * @exception ParsingError si l'identifieur n'existe pas.
     * @return La liste associative de chaine de caractère et de Litteral.
     */
    std::map<const std::string, std::shared_ptr<Literal>>& getIdentifiers() { return identifiers; }
    /**
     * @brief Accesseur au dernier opérateur utilisé.
     * @return Un shared_ptr sur Operator.
     */
    std::shared_ptr<Operator> getLastop() const { return lastop; }
    /**
     * @brief Accesseur au derniers arguments utilisés.
     * @return Arguments de shared_ptr sur Literal.
     */
    Arguments<std::shared_ptr<Literal>> getLastargs() const {return lastargs; }
    /**
     * @brief Ajout d'un identifieur selon une chaine de caractères représentant la clé, et une chaine de caractères représentant la litteral.
     * @param k Chaine de caractère représentant la clé.
     * @param l shared_ptr de Literal.
     */
    void addIdentifier(const std::string& k, const std::shared_ptr<Literal> l) ;
    /**
     * @brief Ajout d'un identifieur selon une chaine de caractères représentant la clé, et une chaine de caractères représentant la litterale.
     * @param k Chaine de caractère représentant la clé.
     * @param l Chaine de caractère représentant la Literal.
     */
    void addIdentifier(const std::string& k,const std::string& l) ;
    /**
     * @brief Mise un jour d'un identifieur selon une chaine de caractères représentant la clé, et une litterale.
     * @param key Chaine de caractère représentant l'ancienne clé.
     * @param newKey Chaine de caractère représentant la nouvelle clé.
     * @param newValue shared_ptr de Literal.
     */
    void changeIdentifier(const std::string& key, const std::string& newKey, const std::shared_ptr<Literal> newValue);
    /**
     * @brief Mise un jour d'un identifieur selon une chaine de caractères représentant la clé, et une chaine de caractères représentant la litterale.
     * @param key Chaine de caractère représentant l'ancienne clé.
     * @param newKey Chaine de caractère représentant la nouvelle clé.
     * @param newValue Chaine de caractère représentant la Literal.
     */
    void changeIdentifier(const std::string& key, const std::string& newKey, const std::string newValue);
    /**
     * @brief Mise un jour d'un identifieur selon une chaine de caractères représentant la clé, et une chaine de caractères représentant la litterale.
     * @param key Chaine de caractère représentant la clé.
     * @param newValue Chaine de caractère représentant la Literal.
     */
    void changeIdentifier(const std::string& key, const std::string newValue) ;
    /**
     * @brief Suppression d'un identifieur selon une chaine de caractères représentant la clé.
     * @param key Chaine de caractère représentant la clé.
     */
    void deleteIdentifier(const std::string& key);
    /**
     * @brief Accesseur aux identifieurs de Literal programmes.
     * @return Liste associative de string et de shared_ptr sur Literal.
     */
    const std::map<const std::string,std::shared_ptr<Literal>> getProgramsIdentifiers() const;
    /**
     * @brief Accesseur aux identifieurs de Literal non-programme.
     * @return Liste associative de string et de shared_ptr sur Literal.
     */
    const std::map<const std::string,std::shared_ptr<Literal>> getVariablesIdentifiers() const;
    /**
     * @brief Traite une ligne d'opérandes sous forme textuelle.
     * @details Une ligne de commande est une suite cohérente de représentations d'opérandes (opérateurs ou littérales)
     * séparées par des espaces. Elles sont transformées en instances d'Operand puis évaluées.
     * @param command Ligne de commande à évaluer.
     */
    void handleOperandLine(std::string command);
    /**
     * @brief Procède à l'évalution d'un ensemble d'opérandes.
     * @details Le résultat de l'opération, s'il a lieu, est empilé sur la pile.
     * @param operands Vecteur d'opérandes à évaluer
     */
    void eval(std::vector<std::shared_ptr<Operand>> operands);
    /**
     * @brief Accesseur au vecteur d'opérateurs symbolique en chaine de caractères.
     * @return Un vecteur de chaine de caractère représentant les opérateurs symboliques.
     */
    std::vector<std::string> getSymbolicOperatorToString() const;
    /**
     * @brief Accesseur au vecteur d'opérateurs de fonction en chaine de caractères.
     * @return Un vecteur de chaine de caractère représentant les opérateurs de fonction.
     */
    std::vector<std::string> getFunctionOperatorToString() const;
    /**
     * @brief Accesseur à la pile en chaine de caractères.
     * @return Un vecteur de chaine de caractère représentant la pile.
     */
    std::vector<std::string> getPileToString() const;
    /**
     * @brief Procédure vidant la pile.
     */
    void clearPile();
    /**
     * @brief Fonction indiquant si l'état du mémento est l'état courant du manager
     * @param m Memento représentant l'état à comparer à l'état actuel du Manager.
     * @return bool true si l'état actuel du manager est celui du Memento, false sinon.
     */
    bool isCurrentState(std::shared_ptr<Memento> m);

    /**
     * @brief Sauvegarde l'état actuel du manager dans le vecteur de Memento.
     */
    void saveState();
    /**
     * @brief Retour à l'état précédent du Manager.
     * @exception UTException s'il n'y a rien à annulé.
     */
    void undo();
    /**
     * @brief Annulation de undo.
     * @exception UTException s'il n'y a rien remettre.
     */
    void redo();

    /**
     * @brief Accesseur à la pile
     * @return Pile
     */
    Pile& getPile() {
        return pile;
    }
};

#endif // MANAGER_H
