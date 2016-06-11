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
     * @brief Sauvegarde de la liste des identifiers d'un état du Manager.
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
     * @brief Sauvegarde de la liste utilisé d'un état du Manager.
     */
    Arguments<std::shared_ptr<Literal>> lastargs;
public:
    /**
     * @brief Constructeur public de la classe Memento.
     * @param i Map de chaine de caractères et de litterale à enregistrer.
     * @param p Pile de litterals à enregistrer.
     * @param s Options à enregistrer.
     * @param lastop Dernière opération à enregistrer.
     * @param lastargs Liste des derniers arguments à enregistrer.
     */
    Memento (const std::map<const std::string, std::shared_ptr<Literal>>& i,
             const Pile& p, const Settings& s,
             std::shared_ptr<Operator> lastop,
             Arguments<std::shared_ptr<Literal>> lastargs):
        identifiers(i), pile(p), settings(s), lastop(lastop), lastargs(lastargs) {}
    /**
     * @brief Accesseur au tableau d'identifieurs enregistré dans le Memento.
     * @return Le tableau d'identifieurs.
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
     * @brief Liste de Memento pour la sauvegarde des états de la classe.
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
     * @brief Constructeur vide de Manager en privé.
     */
    Manager();
public:
    Manager(const Manager&) = delete;
    Manager& operator= (const Manager&) = delete;
    static Manager& getInstance();

    const std::shared_ptr<Literal>& getIdentifier(const std::string&) const;
    Settings& getSettings() { return settings; }
    std::map<const std::string, std::shared_ptr<Literal>>& getIdentifiers() { return identifiers; }
    std::shared_ptr<Operator> getLastop() const { return lastop; }
    Arguments<std::shared_ptr<Literal>> getLastargs() const {return lastargs; }
    void addIdentifier(const std::string&, const std::shared_ptr<Literal>) ;
    void addIdentifier(const std::string&,const std::string&) ;
    void changeIdentifier(const std::string&, const std::string&, const std::shared_ptr<Literal>);
    void changeIdentifier(const std::string& key, const std::string& newKey, const std::string newValue);
    void changeIdentifier(const std::string& key, const std::string newValue) ;
    void deleteIdentifier(const std::string&);
    const std::map<const std::string,std::shared_ptr<Literal>> getProgramsIdentifiers() const;
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
    std::vector<std::string> getSymbolicOperatorToString() const;
    std::vector<std::string> getFunctionOperatorToString() const;
    std::vector<std::string> getPileToString() const;
    void clearPile();
    bool isCurrentState(std::shared_ptr<Memento>);

    void saveState();
    void undo();
    void redo();

    // Juste pour les tests
    void afficherBackUp(){
        std::cout << "CurrentState : " << currentState << std::endl;
        for (auto e : identifiers) std::cout << "\tId "<< e.first << std::endl;
        for(auto v : backup){
            std::cout << "Backup " << std::endl;
            auto id = v->getIdentifiers();
            for(auto a: id) std::cout <<"\tId " << a.first << std::endl;
        }
    }

    Pile& getPile() {
        return pile;
    }
};

#endif // MANAGER_H
