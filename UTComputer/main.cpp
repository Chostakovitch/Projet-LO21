#include <QApplication>
#include <iostream>
#include <QSound>
#include <QDir>
#include "UTComputer.h"
#include "OperatorManager.h"
#include "Literal.h"
#include "Operateurs.h"
#include "LiteralFactory.h"
#include "Operation.h"
#include "Calculator.h"
#include "Manager.h"
#include "ExpressionParser.h"
#include "UTException.h"

int main(int argc, char *argv[])
{
    int exitCode = EXIT_SUCCESS;
    do {
        QApplication a(argc, argv);
        UTComputer w;
        w.show();
        exitCode = a.exec();
    } while(exitCode == UTComputer::EXIT_CODE_REBOOT);
    return exitCode;
}
