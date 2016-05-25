#include <QApplication>
#include <iostream>

#include "utcomputer.h"
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
    try {
        Manager::getInstance().handleOperandLine("\"SIN(8) + 4\"");
        Manager::getInstance().handleOperandLine("4           3   +");
        Manager::getInstance().handleOperandLine("*");
        for(const auto& e : Manager::getInstance().getPile()) std::cout << e->toString() << " ";
    }
    catch(UTException& e) {
        std::cout << "Resume : " << e.what();
        std::cout << "\n\nDetails :\n" <<  e.details();
    }

    putchar('\n');

    /*QApplication a(argc, argv);
    UTComputer w;
    w.show();
    return a.exec();*/

    return 0;
}
