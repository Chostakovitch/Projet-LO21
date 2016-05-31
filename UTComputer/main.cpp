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
    Manager::getInstance().handleOperandLine("4 5.4 $ 6 7 4 / $ /");
    for(auto& lit : Manager::getInstance().getPile()) std::cout << lit->toString() << std::endl;

    /*QApplication a(argc, argv);
    UTComputer w;
    w.show();
    return a.exec();*/

    return 0;
}
