#include <sstream>
#include <iostream>
#include "CompositeLiteral.h"

std::string ProgramLiteral::toString() const {
    std::stringstream ss;
    ss << "[ ";
    for (auto op : operands) {
        ss << op->toString()+ " ";
    }
    ss << "]";
    return ss.str();
}

std::string ProgramLiteral::toStringExtended() const {
    static int count;
    ++count;
    std::stringstream ss;
    for (int i = 0; i < count - 1; ++i) ss << "\t";
    ss << "[" << std::endl;
    for (auto op : operands) {
        for (int i = 0; i < count; ++i) ss << "\t";
        ss << op->toString();
        ss << std::endl;
    }
    for (int i = 0; i < count - 1; ++i) ss << "\t";
    ss << "]" << std::endl;
    --count;
    return ss.str();
}
