#ifndef PILE_H
#define PILE_H

#include <stack>
#include "Literal.h"

class Pile
{
    std::vector<std::shared_ptr<Literal>> p;
public:
    unsigned int size () { return p.size(); }
    bool empty() { return p.empty(); }
    std::shared_ptr<Literal> pop() {
        std::shared_ptr<Literal> temp = p.back();
        p.pop_back();
        return temp;
    }
    void push(std::shared_ptr<Literal> l) { p.push_back(l);}

    std::vector<std::shared_ptr<Literal>>::const_iterator begin() const { return p.begin(); }
    std::vector<std::shared_ptr<Literal>>::const_iterator end() const { return p.end(); }
};

#endif // PILE_H
