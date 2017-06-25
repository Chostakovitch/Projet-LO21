#ifndef WINDOWEXCEPTION_H
#define WINDOWEXCEPTION_H

#include <QWidget>
#include "UTException.h"

/**
 * @brief La classe WindowException est une fenétre qui affiche les details de l'exception UTCException.
 */
class WindowException : public QWidget
{
    Q_OBJECT
    /**
     * @brief Chaine de caractères représentant les details de l'UTCException.
     */
    std::string details;
public:
    /**
     * @brief Constructeur public de la classe WindowException
     * @param details Chaine de caractères représentant les details de l'exception concernée.
     */
    WindowException(std::string details);
};

#endif // WINDOWEXCEPTION_H
