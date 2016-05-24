#include "UTException.h"
#include "Operateurs.h"
#include "Literal.h"
#include <sstream>

const char* ParsingError::what() const throw() {
    std::ostringstream oss;
    oss << "Unable to parse token : " << token << "(" << UTException::what() << ").";
    return oss.str().c_str();
}

const char* OperationError::what() const throw() {
    std::ostringstream oss;
    oss << "Unable to perform operation : " << op->toString() << "(" << UTException::what() << ").";
    return oss.str().c_str();
}

const char* CastError::what() const throw() {
    std::ostringstream oss;
    oss << "Unable to perform promotion of operands : [";
    for(auto& lit : ops) {
        oss << lit->toString();
        if(lit != *(ops.end())) oss << ", ";
    }
    oss << "] (" << UTException::what() << ").";
}
