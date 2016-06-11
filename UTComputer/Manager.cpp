#include "Manager.h"
#include "Literal.h"
#include "CompositeLiteral.h"
#include "OperatorManager.h"
#include "UTException.h"
#include "Utility.h"
#include <memory>
#include <iostream>
#include <cctype>
#include <algorithm>
#include <iterator>
#include <sstream>
#include <QDebug>

Manager::Manager() {
    std::shared_ptr<Memento> memento(new Memento(identifiers, pile, settings, lastop, lastargs));
    backup.push_back(memento);

    //Programme prédéfini pour effectuer une boucle
    addIdentifier("BOUCLE", "[ \"PROG\" STO \"J\" STO \"I\" STO [ \"I\" EVAL \"J\" EVAL < ] [ \"PROG\" EVAL EVAL \"I\" EVAL 1 + \"I\" STO ] WHILE ]");
    currentState = 0;
}

Manager& Manager::getInstance() {
    static Manager instance;
    return instance;
}

const std::shared_ptr<Literal>& Manager::getIdentifier(const std::string& k) const {
    try {
        return identifiers.at(k);
    }
    catch(std::out_of_range&) {
        throw ParsingError(k, "Identifier does not exist.");
    }
}

void Manager::addIdentifier(const std::string& id, std::shared_ptr<Literal> lit) {
    if (!Utility::isAtom(id)) throw ParsingError(id, "An identifier must begin with a uppercase character and only contain uppercase character and digit.");
    if (OperatorManager::getInstance().isOperator(id)) throw ParsingError(id, "This name is already assigned to a program.");
    identifiers[id] = lit;
}

void Manager::addIdentifier(const std::string& id, const std::string&  lit) {
    addIdentifier(id, LiteralFactory::getInstance().makeLiteralFromString(lit));
}

void Manager::changeIdentifier(const std::string& key, const std::string& newKey, const std::shared_ptr<Literal> newValue) {
    identifiers.erase(key);
    addIdentifier(newKey, newValue);
}

void Manager::changeIdentifier(const std::string& key, const std::string& newKey, const std::string newValue) {
    identifiers.erase(key);
    addIdentifier(newKey, newValue);
}

void Manager::changeIdentifier(const std::string& key, const std::string newValue) {
    handleOperandLine(newValue);
    identifiers[key] = LiteralFactory::getInstance().makeLiteralFromString(newValue);
}

void Manager::deleteIdentifier(const std::string& key) {
    identifiers.erase(key);
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

std::vector<std::string> Manager::getSymbolicOperatorToString() const {
    auto operators = OperatorManager::getInstance().getSymbolicOperators();
    std::vector<std::string> result(operators.size());
    std::transform(operators.begin(), operators.end(), result.begin(), [](const std::shared_ptr<Operator>& o){ return o->toString(); });
    return result;
}

std::vector<std::string> Manager::getFunctionOperatorToString() const {
    auto operators = OperatorManager::getInstance().getFunctionOperators();
    std::vector<std::string> result(operators.size());
    std::transform(operators.begin(), operators.end(), result.begin(), [](const std::shared_ptr<Operator>& o){ return o->toString(); });
    return result;
}

std::vector<std::string> Manager::getPileToString() const {
    std::vector<std::string> result(pile.size());
    std::transform(pile.begin(), pile.end(), result.begin(), [](const std::shared_ptr<Literal>& l){ return l->toString(); });
    return result;
}

void Manager::handleOperandLine(std::string command) {
    if(command.size() == 0) return;

    int leftPos;
    int rightPos = -1;
    //Une expression ne contient pas de sous expression, on considère seulement les paires de guillemets
    while((leftPos = command.find('"', rightPos + 1)) != std::string::npos) {
        rightPos = command.find('"', leftPos + 1);
        if(leftPos != std::string::npos && rightPos != std::string::npos && leftPos != rightPos) {
            command.erase(std::remove(command.begin() + leftPos, command.begin() + rightPos, ' '), command.begin() + rightPos);
        }
    }
    //On traite à part les programmes et le reste, les programmes doivent rester entiers (pas de split sur espaces).
    leftPos = command.find_first_of('[');
    rightPos = command.find_last_of(']');
    std::vector<std::string> tokens;
    //On a trouvé la preuve d'au moins un programme, on effectue la séparation
    if(leftPos != std::string::npos && rightPos != std::string::npos) {
        int leftBracketPos = -1; //Position courante crochet gauche
        int rightBracketPos = -1; //Position courante du crochet droit
        //Tant qu'on trouve un début de programme, on trouve la fin (on saute donc les sous-programmes)
        while((leftBracketPos = command.find('[', rightBracketPos + 1)) != std::string::npos) {
            //On traite l'expression à gauche du programme
            std::istringstream leftiss(command.substr(rightBracketPos + 1, leftBracketPos - rightBracketPos - 1));
            tokens.insert(tokens.end(), std::istream_iterator<std::string>{leftiss}, std::istream_iterator<std::string>{});
            int leftBracketCount = 1, rightBracketCount = 0;
            for(unsigned int i = leftBracketPos + 1; i < command.size(); ++i) {
                if(leftBracketCount == rightBracketCount) break; //On a trouvé un programme complet
                if(command.at(i) == '[') ++leftBracketCount;
                else if(command.at(i) == ']') {
                    ++rightBracketCount;
                    rightBracketPos = i; //Mise à jour de la position de la fin effective du programme
                }
            }

            //Traitement du programme en lui-même
            if(leftBracketPos != std::string::npos && rightBracketPos != std::string::npos) {
                tokens.push_back(command.substr(leftBracketPos, rightBracketPos - leftBracketPos + 1));
            }

            //Programme malformé
            else {
                throw ParsingError(command, "Square bracket unclosed in program.");
            }
        }
        //On traite l'expression à la fin du dernier programme
        if(rightPos != std::string::npos) {
            std::istringstream rightiss(command.substr(rightPos + 1));
            tokens.insert(tokens.end(), std::istream_iterator<std::string>{rightiss}, std::istream_iterator<std::string>{});
        }
    }
    //Sinon, on splitte tous les espaces
    else {
        std::istringstream iss(command);
        tokens.insert(tokens.end(), std::istream_iterator<std::string>{iss}, std::istream_iterator<std::string>{});
    }
    std::vector<std::shared_ptr<Operand>> ops;
    for(auto& op : tokens) {
        //On essaye de fabriquer une littérale
        try {
            ops.push_back(LiteralFactory::getInstance().makeLiteralFromString(op));
        }
        catch(UTException& e1) {
            //Non-littérale, on tente d'identifier un opérateur
            try {
                ops.push_back(OperatorManager::getInstance().getOperator(op));
            }
            catch(UTException& e2) {
                //Non-opérateur, on tente de trouver un identificateur
                try {
                    auto id = getIdentifier(op);
                    //On pushe la littérale correspondant à l'identificateur.
                    ops.push_back(id);

                    //Atome correspondant à un programme : on l'évalue.
                    if(std::dynamic_pointer_cast<ProgramLiteral>(id)) ops.push_back(OperatorManager::getInstance().getEvalOperator());
                }
                //Non-identificateur, on crée une littérale expression si possible.
                catch(UTException& e3) {
                    //Atome bien formé, on l'encapsule dans une LiteralExpression.
                    if(Utility::isAtom(op)) {
                        ops.push_back(LiteralFactory::getInstance().makeLiteral(op));
                    }
                    //Impossible de construire une opérande, on le signale
                    else throw ParsingError(op, "Atom must start with uppercase and contain only digits and uppercase chars").add(e3).add(e2).add(e1);
                }
            }
        }
    }
    //On évalue ensuite les opérandes
    try {
        eval(ops);
        saveState();
    }
    //Si quelque chose s'est mal passé, on restaure la pile avant l'évaluation
    catch(UTException& e) {
        if (backup.size() > 0) restoreState(backup[currentState]);
        throw e;
    }
}

void Manager::eval(std::vector<std::shared_ptr<Operand>> operands) {
    //Pour chaque opérande
    for(auto operand : operands) {
        //Si on trouve une littérale, on l'empile
        if(auto lit = std::dynamic_pointer_cast<Literal>(operand)) pile.push(lit);

        //Si on trouve un opérateur, on déclenche l'évaluation
        else if(auto op = std::dynamic_pointer_cast<Operator>(operand)) {
            if(pile.size() < op->getArity()) {
                std::ostringstream oss;
                oss << "Not enought operands for this operator. ";
                oss << op->getArity() << " operands needed, " << pile.size() << " given.";
                throw OperationError(op, Arguments<std::shared_ptr<Literal>>(), oss.str());
            }
            //Construction des arguments
            Arguments<std::shared_ptr<Literal>> args;
            args.reserve(pile.size());
            for(unsigned int i = 0; i < op->getArity(); ++i) {
                args.insert(args.begin(), pile.pop());
            }
            //On tente d'effectuer l'opération (si elle est implémentée et si les types correspondent)
            try {
                auto res = OperatorManager::getInstance().dispatchOperation(op, args);
                lastop = op;
                lastargs = args;
                //On évalue le résultat (il pourrait contenir des opérateurs).
                eval(res);
            }
            //Impossible d'effectuer l'opération : on restitue la pile avant l'opération en cours.
            catch(UTException& e) {
                throw OperationError(op, args, "Failed to apply operation").add(e);
            }
        }
    }
}

void Manager::saveState() {
     if(backup.size() > 0 && !isCurrentState(backup[currentState])){
        for (unsigned int i = currentState + 1; i < backup.size(); i++) backup.pop_back();
        std::shared_ptr<Memento> memento(new Memento(identifiers, pile, settings, lastop, lastargs));
        backup.push_back(memento);
        currentState++;
    }
}

bool Manager::isCurrentState(std::shared_ptr<Memento> m) {
    if (identifiers.size() != m->getIdentifiers().size()
            || !std::equal(identifiers.begin(), identifiers.end(), m->getIdentifiers().begin())
            || pile != m->getPile()) return false;
    return true;
}

void Manager::restoreState(std::shared_ptr<Memento> memento){
    pile = memento->getPile();
    identifiers = memento->getIdentifiers();
    settings = memento->getSettings();
    lastop = memento->getLastop();
    lastargs = memento->getLastargs();
}

void Manager::undo() {
    if (currentState == 0) throw UTException("There is nothing to undo.");
    currentState--;
    restoreState(backup[currentState]);
    qDebug() << "UNDO, currentState " << currentState;
}

void Manager::redo() {
    if (currentState == backup.size() - 1) throw UTException("There is nothing to redo.");
    currentState++;
    restoreState(backup[currentState]);

}

void Manager::clearPile() {
    while (!pile.empty()) pile.pop();
}
