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

    const std::shared_ptr<Litteral>& getIdentifier(const std::string&) const;
    void addIdentifier(const std::string&, const std::shared_ptr<Litteral>);
};

#endif // MANAGER_H
