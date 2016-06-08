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
    /*try {
        Manager::getInstance().handleOperandLine("4.5 4.6 +");
        for(auto& lit : Manager::getInstance().getPile()) std::cout << lit->toString() << std::endl;
    } catch(UTException& e) { std::cout << e.details() << std::endl; }*/

    //auto res = ExpressionParser("AND((4+3)=<SIN(4),8.5>5$4)").parse();
    //for(auto op : res) std::cout << op->toString() << " ";
    //std::cout << std::endl;
    QApplication a(argc, argv);
    UTComputer w;
    w.show();
    return a.exec();
}
