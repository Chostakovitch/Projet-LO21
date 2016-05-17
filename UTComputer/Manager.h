#ifndef MANAGER_H
#define MANAGER_H

#include <map>

class Litteral;

class Manager
{
    std::map<const std::string, std::shared_ptr<Litteral>> identifiers;
    Manager();
public:
    Manager(const Manager&) = delete;
    Manager& operator= (const Manager&) = delete;
    const Manager& getInstance();

    const std::shared_ptr<Litteral>& getIdentifier(const std::string& id) const;

};

#endif // MANAGER_H
