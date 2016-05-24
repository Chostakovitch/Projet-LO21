#ifndef UTEXCEPTION_H
#define UTEXCEPTION_H
#include <stdexcept>
#include <memory>
#include <vector>

class Operator;
class Literal;

/**
 * @brief Un objet UTException représente une exception générée par UTComputer à tout moment
 * du programme. Elle est affinée par des classes d'exception filles en fonction du contexte.
 */
class UTException : public std::exception
{
protected:
    std::string info;
public:
    explicit UTException(const std::string& info) : info(info) { }
    virtual const char* what() const throw() override { return info.c_str(); }
    virtual ~UTException() { }
};

/**
 * @brief Un objet ParsingError décrit une erreur rencontrée lors de la transformation d'une chaîne de caractères
 * en objets métiers ou lorsque une expression mal formée est rencontrée.
 */
class ParsingError : public UTException {
    std::string token;
public:
    ParsingError(std::string token, std::string info) : UTException(info), token(token) { }
    const char* what() const throw() override;
};

/**
 * @brief Un objet OperationError décrit une erreur rencontrée lors de l'application d'une opération.
 * Exemple : Types incompatibles, opération non-implémentée.
 */
class OperationError : public UTException {
    std::shared_ptr<Operator> op;
    OperationError(std::shared_ptr<Operator> op, std::string info) : UTException(info), op(op) { }
    const char* what() const throw() override;
};

/**
 * @brief Un objet CastError décrit une erreur rencontrée lors du cast d'une littérale vers une autre littérale.
 * Plus généralement, cette classe doit être utilisée quand des littérales ne peuvent pas être uniformisées.
 */
class CastError : public UTException {
    std::vector<std::shared_ptr<Literal>> ops;
public:
    CastError(const std::vector<std::shared_ptr<Literal>>& ops, std::string info) : UTException(info), ops(ops) { }
    const char* what() const throw() override;
};

#endif // UTEXCEPTION_H
