#ifndef UTEXCEPTION_H
#define UTEXCEPTION_H
#include <stdexcept>

/**
 * @brief Un objet UTException représente une exception générée par UTComputer à tout moment
 * du programme. Elle est affinée par des classes d'exception filles en fonction du contexte.
 */
class UTException : public std::logic_error
{
public:
    using std::logic_error::logic_error;
    virtual const char* what() const throw() override = 0;
    virtual ~UTException() { }
};

#endif // UTEXCEPTION_H
