#include "Manager.h"
#include "Literal.h"
#include "CompositeLiteral.h"
#include "OperatorManager.h"
#include <memory>
#include <iostream>
#include <cctype>

Manager::Manager() : settings (new Settings()) { saveState(); currentState = 0;}

Manager& Manager::getInstance() {
    static Manager instance;
    return instance;
}

const std::shared_ptr<Literal>& Manager::getIdentifier(const std::string& id) const {
    return identifiers.at(id);
}

void Manager::addIdentifier(const std::string& id, std::shared_ptr<Literal> lit) {
    if (id.empty() || std::islower(id[0])) throw std::invalid_argument("An identifier must begin with a uppercase character.");
    if (!std::all_of(id.begin(), id.end(), [](char c) { return (isupper(c) || isdigit(c));})) throw std::invalid_argument("An identifier must constain only uppercase character and digit.");
    if (OperatorManager::getInstance().isOperator(id)) throw std::invalid_argument("This name is already assigned to a program.");
    identifiers[id] = lit;
    saveState();
}

void Manager::changeIdentifier(const std::string& key, const std::string& newKey, const std::shared_ptr<Literal> newValue) {
    identifiers.erase(key);
    addIdentifier(newKey, newValue);
}

const std::map<const std::string,std::shared_ptr<Literal>> Manager::getProgramsIdentifiers() {
    std::map<const std::string,std::shared_ptr<Literal>> result;
    for (auto it : identifiers) {
        if (std::dynamic_pointer_cast<ProgramLiteral>(it.second)) result[it.first] = it.second;
    }
    return result;
}

const std::map<const std::string,std::shared_ptr<Literal>> Manager::getVariablesIdentifiers() {
    std::map<const std::string,std::shared_ptr<Literal>> result;
    for (auto it : identifiers) {
        if (!std::dynamic_pointer_cast<ProgramLiteral>(it.second)) result[it.first] = it.second;
    }
    return result;
}

std::shared_ptr<Memento> Manager::saveState() {
    for (unsigned int i= currentState+1; i< backup.size(); i++) backup.pop_back();
    std::shared_ptr<Memento> memento(new Memento(identifiers, pile, settings));
    backup.push_back(memento);
    currentState++;
    return memento;
}

void Manager::restoreState(std::shared_ptr<Memento> memento){
    pile = memento->getPile();
    identifiers = memento->getIdentifiers();
    *settings = memento->getSettings();
}

void Manager::undo() {
    if (currentState == 0) throw std::out_of_range("There are nothing to undo.");
    currentState--;
    restoreState(backup[currentState]);
}

void Manager::redo() {
    if (currentState == backup.size()-1) throw std::out_of_range("There are nothing to redo.");
    currentState++;
    restoreState(backup[currentState]);
}
