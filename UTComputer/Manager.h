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

class Memento {
private:
    std::map<const std::string, std::shared_ptr<Literal>> identifiers;
    Pile pile;
    Settings settings;
    std::shared_ptr<Operator> lastop;
    Arguments<std::shared_ptr<Literal>> lastargs;
public:
    Memento (const std::map<const std::string,
             std::shared_ptr<Literal>>& i,
             const Pile& p, const Settings& s,
             std::shared_ptr<Operator> lastop,
             Arguments<std::shared_ptr<Literal>> lastargs):
        identifiers(i), pile(p), settings(s), lastop(lastop), lastargs(lastargs) {}
    std::map<const std::string, std::shared_ptr<Literal>> getIdentifiers() const { return identifiers; }
    const Pile& getPile() const { return pile; }
    const Settings& getSettings() const { return settings; }
    const std::shared_ptr<Operator>& getLastop() const { return lastop; }
    const Arguments<std::shared_ptr<Literal>> getLastargs() const { return lastargs; }

    friend class Manager;
};

class Manager
{
    std::map<const std::string, std::shared_ptr<Literal>> identifiers;
    Pile pile;
    Settings settings;
    std::shared_ptr<Operator> lastop;
    Arguments<std::shared_ptr<Literal>> lastargs;

    //Memento :
    std::vector<std::shared_ptr<Memento>> backup;
    unsigned int currentState;
    void restoreState(std::shared_ptr<Memento> memento);

    /**
     * @brief Procède à l'évalution d'un ensemble d'opérandes.
     * @details Le résultat de l'opération, s'il a lieu, est empilé sur la pile.
     * @param operands
     */
    void eval(std::vector<std::shared_ptr<Operand>> operands);

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
    std::vector<std::string> getSymbolicOperatorToString() const;
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

    // Pour les tests
    const Pile& getPile() {
        return pile;
    }
};

#endif // MANAGER_H
