#ifndef PILE_H
#define PILE_H

#include <stack>
#include "Literal.h"

class Pile
{
    std::vector<std::shared_ptr<Literal>> p;
public:
    Pile();
    unsigned int size () { return p.size(); }
    bool empty() { return p.empty(); }
    void pop() { p.pop_back(); }
    void push(std::shared_ptr<Literal> l) { p.push_back(l);}
    std::shared_ptr<Literal> top() { return p[0]; }

    std::vector<std::shared_ptr<Literal>>::iterator begin() { return p.begin(); }
    std::vector<std::shared_ptr<Literal>>::iterator end() { return p.end(); }
};

#endif // PILE_H
