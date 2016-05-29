#include <QApplication>
#include <iostream>

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
    try {
        Manager::getInstance().handleOperandLine("3 4.5 $ NEG");
        auto pile = Manager::getInstance().getPile();
        for(auto it = pile.begin(); it != pile.end(); ++it) {
            std::cout << (*it)->toString() << " " << std::endl;
        }
    } catch(UTException& e) {
        std::cout << e.details() << std::endl;
    }

    putchar('\n');

    /*QApplication a(argc, argv);
    UTComputer w;
    w.show();
    return a.exec();*/

    return 0;
}
