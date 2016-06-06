#include <sstream>
#include <iostream>
#include "CompositeLiteral.h"

std::string ProgramLiteral::toString() const {
    static int count;
    ++count;
    std::stringstream ss;
    //ss << "Program(debug)" << std::endl;
    for (int i = 0; i < count - 1; ++i) ss << "\t";
    ss << "[" << std::endl;
    for (auto op : operands) {
        for (int i = 0; i < count; ++i) ss << "\t";
        ss << op->toString();
        //ss << "\t" << typeid(*op).name() <<"(debug)";
        ss << std::endl;
    }
    for (int i = 0; i < count - 1; ++i) ss << "\t";
    ss << "]" << std::endl;
    --count;
    return ss.str();
}
