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


