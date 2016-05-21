#ifndef PILE_H
#define PILE_H

#include <stack>
#include "Literal.h"

class Pile
{
    std::stack<Literal> p;
public:
    Pile();
    //unsigned int size () { return p.size(); }
    //Literal pop() { return p.pop; }
    //Literal top() { return p.top(); }

};

#endif // PILE_H
