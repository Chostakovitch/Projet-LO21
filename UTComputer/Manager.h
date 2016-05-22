#ifndef MANAGER_H
#define MANAGER_H

#include <map>
#include <vector>
#include <memory>

class Literal;

class Manager
{
    std::map<const std::string, std::shared_ptr<Literal>> identifiers;
    Manager();
public:
    Manager(const Manager&) = delete;
    Manager& operator= (const Manager&) = delete;
    static Manager& getInstance();

    const std::shared_ptr<Literal>& getIdentifier(const std::string&) const;
    void addIdentifier(const std::string&, const std::shared_ptr<Literal>);

    const std::map<const std::string,std::shared_ptr<Literal>> getProgramsIdentifiers() const;
    const std::map<const std::string,std::shared_ptr<Literal>> getVariablesIdentifiers() const;
};
#endif // MANAGER_H
