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
    std::stringstream ss;
    for (int i = 0; i < count - 1; ++i) ss << "\t";
    ss << "[";
    if(operands.size() > 6) ss << std::endl;
    ++count;
    for (auto op : operands) {
        if(operands.size() > 6) for (int i = 0; i < count; ++i) ss << "\t";
        else ss << " ";
        if(auto prog = std::dynamic_pointer_cast<ProgramLiteral>(op))
            ss << prog->toStringExtended();
        else ss << op->toString();
        if(operands.size() > 6) ss << std::endl;
    }
    --count;
    if(operands.size() <= 6) ss << " ";
    else for (int i = 0; i < count; ++i) ss << "\t";
    ss << "]";
    return ss.str();
}
