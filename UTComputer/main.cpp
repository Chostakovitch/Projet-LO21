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

    /*QApplication a(argc, argv);
    UTComputer w;
    w.show();
    return a.exec();*/

    try {
        Manager::getInstance().handleOperandLine("4.5 5 $ 8 5 / 4 $ POW");
        for(auto& o : Manager::getInstance().getPile()) std::cout << o->toString() << std::endl;
    }
    catch(UTException& e) {
        std::cout << e.details() << std::endl;
    }

    return 0;
}
