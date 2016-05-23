#ifndef MANAGER_H
#define MANAGER_H

#include <map>
#include <vector>
#include <memory>
#include <stack>
#include <iostream>
#include "Settings.h"
#include "Pile.h"

class Literal;
class Settings;
class Operand;

class Memento {
private:
    std::map<const std::string, std::shared_ptr<Literal>> identifiers;
<<<<<<< HEAD
    //std::stack<std::shared_ptr<Literal>> pile;
    std::shared_ptr<Pile> pile;
    std::shared_ptr<Settings> settings;
public:
    Memento (const std::map<const std::string, std::shared_ptr<Literal>> i, std::shared_ptr<Pile> p, std::shared_ptr<Settings> s):
        identifiers (i), pile(p), settings(s) {}
    std::map<const std::string, std::shared_ptr<Literal>> getIdentifiers() const { return identifiers; }
    //std::stack<std::shared_ptr<Literal>> getPile() { return pile; }
    std::shared_ptr<Pile> getPile() { return pile; }
    std::shared_ptr<Settings> getSettings() { return settings; }
=======
    std::vector<std::shared_ptr<Literal>> pile;
    Settings settings;
public:
    Memento (const std::map<const std::string, std::shared_ptr<Literal>> i, std::vector<std::shared_ptr<Literal>> p, Settings* s):
        identifiers (i), pile(p), settings(*s) {}
    std::map<const std::string, std::shared_ptr<Literal>> getIdentifiers() const { return identifiers; }
    std::vector<std::shared_ptr<Literal>> getPile() { return pile; }
    Settings getSettings() { return settings; }
>>>>>>> c578b282fb458615af977b08ff937aa7bea396da

    friend class Manager;
};

class Manager
{
    std::map<const std::string, std::shared_ptr<Literal>> identifiers;
    // TO DO : a-t-on vraiment besoin d'un wrapper ?
<<<<<<< HEAD
    //std::stack<std::shared_ptr<Literal>> pile;
    std::shared_ptr<Pile> pile;
    std::shared_ptr<Settings> settings;
=======
    std::vector<std::shared_ptr<Literal>> pile;
    Settings* settings;
>>>>>>> c578b282fb458615af977b08ff937aa7bea396da

    //Memento :
    std::vector<std::shared_ptr<Memento>> backup;
    unsigned int currentState;
    std::shared_ptr<Memento> saveState();
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

    const std::shared_ptr<Literal> getIdentifier(const std::string&) const;
    const std::shared_ptr<Settings> getSettings() { return settings; }
    void addIdentifier(const std::string&, const std::shared_ptr<Literal>) ;
    void changeIdentifier(const std::string&, const std::string&, const std::shared_ptr<Literal>);
    const std::map<const std::string,std::shared_ptr<Literal>> getProgramsIdentifiers() const;
    const std::map<const std::string,std::shared_ptr<Literal>> getVariablesIdentifiers() const;
    /**
     * @brief Traite une ligne d'opérandes sous forme textuelle.
     * @details Une ligne de commande est une suite cohérente de représentations d'opérandes (opérateurs ou littérales)
     * séparées par des espaces. Elles sont transformées en instances d'Operand puis évaluées.
     * @param command Ligne de commande à évaluer.
     */
    void handleOperandLine(std::string command);

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

    std::vector<std::shared_ptr<Literal>> getStackContent() {
        return pile;
    }
};

#endif // MANAGER_H
