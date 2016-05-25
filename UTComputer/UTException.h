#ifndef UTEXCEPTION_H
#define UTEXCEPTION_H
#include <stdexcept>
#include <memory>
#include <vector>

#include "Literal.h"
class Operator;

/**
 * @brief Un objet UTException représente une exception générée par UTComputer à tout moment
 * du programme. Elle est affinée par des classes d'exception filles en fonction du contexte.
 */
class UTException : public std::exception
{
protected:
    /**
     * @brief Message représentant l'exception.
     */
    std::string msg;
    /**
     * @brief Informations sur la raison de l'exception.
     */
    std::string info;
    /**
     * @brief Exceptions sous-jacentes pour complément d'information.
     */
    std::vector<std::shared_ptr<UTException>> subexcs;
    /**
     * @brief Nom de classe représentant l'expression.
     * @return Chaîne de caractères format C.
     */
    virtual const char* classname() const { return "UTException";}
public:
    /**
     * @brief Constructeur explicite.
     * @param info Information sur l'exception.
     */
    explicit UTException(const std::string& info);
    /**
     * @brief Retourne les informations de l'expression.
     * @return Chaîne de caractères C.
     */
    virtual const char* what() const throw() override { return msg.c_str(); }
    /**
     * @brief Retourne les détails de l'exception, i.e. incluant ses expressions sous-jacentes.
     * @return std::string.
     */
    std::string details() const;
    /**
     * @brief Ajout d'une expression parente.
     * @param exc Exception à ajouter.
     */
    UTException& add(const UTException& exc) { subexcs.push_back(exc.clone()); return *this; }
    /**
     * @brief Renvoie un pointeur vers un objet similaire à l'actuel.
     * @return Pointeur sur UTException.
     */
    virtual std::shared_ptr<UTException> clone() const { return std::make_shared<UTException>(*this); }
    /**
     * @brief Destructeur virtuel vide.
     */
    virtual ~UTException() { }
};

/**
 * @brief Un objet ParsingError décrit une erreur rencontrée lors de la transformation d'une chaîne de caractères
 * en objets métiers ou lorsque une expression mal formée est rencontrée.
 */
class ParsingError : public UTException {
    /**
     * @brief Chaîne de caractères impossible à parser.
     */
    std::string token;
    const char* classname() const override { return "ParsingError";}
public:
    ParsingError(std::string token, std::string info);
    std::shared_ptr<UTException> clone() const override { return std::make_shared<ParsingError>(*this); }
};

/**
 * @brief Un objet OperationError décrit une erreur rencontrée lors de l'application d'une opération.
 * Exemple : Types incompatibles, opération non-implémentée.
 */
class OperationError : public UTException {
    /**
     * @brief Operator qui n'a pas pu effectuer l'opération.
     */
    std::shared_ptr<Operator> op;
    /**
     * @brief Operandes n'ayant pas pu être utilisées dans l'opération.
     */
    Arguments<std::shared_ptr<Literal>> ops;
    const char* classname() const override { return "OperationError";}
public:
    OperationError(const std::shared_ptr<Operator>& op, const Arguments<std::shared_ptr<Literal>>& ops, std::string info);
    std::shared_ptr<UTException> clone() const override { return std::make_shared<OperationError>(*this); }
};

/**
 * @brief Un objet TypeError décrit une erreur concernant les types des littérales.
 * Plus généralement, cette classe doit être utilisée quand des littérales ne peuvent pas être uniformisées.
 */
class TypeError : public UTException {
    /**
     * @brief Littérales ne pouvant pas être uniformisées.
     */
    Arguments<std::shared_ptr<Literal>> ops;

    const char* classname() const override { return "TypeError";}
public:
    TypeError(const Arguments<std::shared_ptr<Literal>>& ops, std::string info);
    std::shared_ptr<UTException> clone() const override { return std::make_shared<TypeError>(*this); }
};

#endif // UTEXCEPTION_H
