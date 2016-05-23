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
class Memento;

class Memento {
private:
    std::map<const std::string, std::shared_ptr<Literal>> identifiers;
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

    friend class Manager;
};

class Manager
{
    std::map<const std::string, std::shared_ptr<Literal>> identifiers;
    // TO DO : a-t-on vraiment besoin d'un wrapper ?
    //std::stack<std::shared_ptr<Literal>> pile;
    std::shared_ptr<Pile> pile;
    std::shared_ptr<Settings> settings;

    //Memento :
    std::vector<std::shared_ptr<Memento>> backup;
    unsigned int currentState;
    std::shared_ptr<Memento> saveState();
    void restoreState(std::shared_ptr<Memento> memento);

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
};

#endif // MANAGER_H
