#ifndef WINDOWEXCEPTION_H
#define WINDOWEXCEPTION_H

#include <QWidget>
#include "UTException.h"

class WindowException : public QWidget
{
    Q_OBJECT
    std::string details;
public:
    WindowException(std::string details);
};

#endif // WINDOWEXCEPTION_H
