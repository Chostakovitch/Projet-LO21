#include "Manager.h"
#include "Literal.h"
#include "CompositeLiteral.h"
#include <memory>

Manager::Manager() {}

Manager& Manager::getInstance() {
    static Manager instance;
    return instance;
}

const std::shared_ptr<Literal>& Manager::getIdentifier(const std::string& id) const {
    return identifiers.at(id);
}

void Manager::addIdentifier(const std::string& id, std::shared_ptr<Literal> lit) {
    identifiers[id] = lit;
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

