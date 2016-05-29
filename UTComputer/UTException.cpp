#include "UTException.h"
#include "Operateurs.h"
#include "Literal.h"
#include <sstream>
ParsingError::ParsingError(std::string token, std::string info) : UTException(info), token(token) {
    std::ostringstream oss;
    oss << "Unable to parse token : " << token << " (" << UTException::what() << ").";
    msg = oss.str();
}

OperationError::OperationError(const std::shared_ptr<Operator> &op, const Arguments<std::shared_ptr<Literal>> &ops, std::string info) : UTException(info), op(op), ops(ops) {
    std::ostringstream oss;
    oss << "Unable to perform operation : " << op->toString() << " on literals : " << ops.toString() << " (" << UTException::what() << ").";
    msg = oss.str();
}

TypeError::TypeError(std::string info, const Arguments<std::shared_ptr<Literal>> &ops) : UTException(info), ops(ops) {
    std::ostringstream oss;
    oss << "Unable to handle or to cast operands : " << ops.toString() << " (" << UTException::what() << ").";
    msg = oss.str();
}

UTException::UTException(const std::string &info) : info(info) {
    msg = info;
}

std::string UTException::details() const {
    static int tab_count;
    std::string tabs(tab_count, '\t');
    std::ostringstream oss;
    oss << tabs << classname() << " : " << what() << std::endl;
    if(!subexcs.empty()) oss << tabs << "{" << std::endl;
    for(auto& exc : subexcs) {
        ++tab_count;
        oss << exc->details();
        --tab_count;
    }
    if(!subexcs.empty()) oss << tabs << "}" << std::endl;
    return oss.str();
}
