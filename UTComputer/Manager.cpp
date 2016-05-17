#include "Manager.h"
#include "Literal.h"

Manager::Manager() {}

const Manager& Manager::getInstance() {
    static Manager instance;
    return instance;
}

const std::shared_ptr<Litteral>& Manager::getIdentifier(const std::string& id) const {
    return identifiers.at(id);
}

