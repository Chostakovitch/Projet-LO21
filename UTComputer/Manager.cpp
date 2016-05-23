#include "Manager.h"
#include "Literal.h"
#include "CompositeLiteral.h"
#include "OperatorManager.h"
#include <memory>
#include <iostream>
#include <cctype>
#include <algorithm>
#include <iterator>
#include <sstream>

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

const std::map<const std::string,std::shared_ptr<Literal>> Manager::getProgramsIdentifiers() const {
    std::map<const std::string,std::shared_ptr<Literal>> result;
    for (auto& prog : identifiers) {
        if (std::dynamic_pointer_cast<ProgramLiteral>(prog.second)) result[prog.first] = prog.second;
    }
    return result;
}

const std::map<const std::string,std::shared_ptr<Literal>> Manager::getVariablesIdentifiers() const {
    std::map<const std::string,std::shared_ptr<Literal>> result;
    for (auto& var : identifiers) {
        if (!std::dynamic_pointer_cast<ProgramLiteral>(var.second)) result[var.first] = var.second;
    }
    return result;
}

void Manager::handleOperandLine(std::string command) {
    //Suppression des espaces entre les guillemets
    unsigned int leftPos = command.find_first_of('"');
    unsigned int rightPos = command.find_last_of('"');
    if(leftPos != std::string::npos && rightPos != std::string::npos) {
        command.erase(std::remove(command.begin() + leftPos, command.begin() + rightPos + 1, ' '), command.begin() + rightPos + 1);
    }
    //Split sur les espaces
    std::istringstream iss(command);
    std::vector<std::string> tokens{std::istream_iterator<std::string>{iss}, std::istream_iterator<std::string>{}};
    std::vector<std::shared_ptr<Operand>> ops;
    for(auto& op : tokens) {
        //On essaye de fabriquer une littérale
        try {
            ops.push_back(LiteralFactory::getInstance().makeLiteralFromString(op));
        }
        catch(std::invalid_argument&) {
            //Non-littérale, on tente d'identifier un opérateur
            try {
                ops.push_back(OperatorManager::getInstance().getOperator(op));
            }
            catch(std::invalid_argument&) {
                //Non-opérateur, on tente de trouver un identificateur
                try {
                    auto id = getIdentifier(op);
                    //Atome correspondant à un programme : on l'évalue.
                    if(std::dynamic_pointer_cast<ProgramLiteral>(id)) ops.push_back(OperatorManager::getInstance().getEvalOperator());
                    //On pushe la littérale correspondant à l'identificateur.
                    ops.push_back(id);
                }
                //Non-identificateur, on crée une littérale expression si possible.
                catch(std::out_of_range&) {
                    //Atome bien formé, on l'encapsule dans une LiteralExpression.
                    if(!command.empty() && std::isupper(op.at(0)) && std::find_if(op.begin(), op.end(), [](char c) { return !(std::isdigit(c) || std::isupper(c)); }) == op.end()) {
                        ops.push_back(LiteralFactory::getInstance().makeLiteral(op));
                    }
                    //Impossible de construire une opérande, on le signale
                    else throw std::invalid_argument(op + std::string(" : unable to parse operand (syntax error)."));
                }
            }
        }
    }
    //On évalue ensuite les opérandes
    eval(ops);
}

void Manager::eval(std::vector<std::shared_ptr<Operand>> operands) {
    //Pour chaque opérande
    for(auto operand : operands) {
        //Si on trouve une littérale, on l'empile
        if(auto lit = std::dynamic_pointer_cast<Literal>(operand)) pile.push_back(lit);
        //Si on trouve un opérateur, on déclenche l'évaluation
        else if(auto op = std::dynamic_pointer_cast<Operator>(operand)) {
            if(pile.size() < op->getArity()) throw std::invalid_argument(std::string("Not enough operands for operator : ") + op->toString());
            //Construction des arguments
            Arguments<std::shared_ptr<Literal>> args;
            for(unsigned int i = 0; i < op->getArity(); ++i) {
                args.push_back(pile.back());
                pile.pop_back();
            }
            //On tente d'effectuer l'opération (si elle est implémentée et si les types correspondent)
            try {
                //On évalue le retour de l'opération, au cas où elle contiendrait de nouveaux opérateurs (e.g. EVAL pour une expression)
                eval(OperatorManager::getInstance().dispatchOperation(op, args));
            }
            //Impossible d'effectuer l'opération : on restitue la pile avant l'opération en cours.
            //TODO : classe d'exception avec objet Operand responsable de l'exception s'il existe par exemple
            catch(std::exception& e) {
                //TODO : restauration de la pile avant l'opération (avec Memento)
                throw std::invalid_argument(std::string("Failed to apply operation") + e.what() + std::string(" Stack restored."));
            }
        }
    }
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
