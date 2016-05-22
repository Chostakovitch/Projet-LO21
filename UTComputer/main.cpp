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

int main(int argc, char *argv[])
{
    /*
    //Fonctionnement des opérations sur littérales expressions
    auto l1 = LiteralFactory::getInstance().makeLiteralFromString("\"4+3\"");
    auto l2 = LiteralFactory::getInstance().makeLiteralFromString("\"VAR*3\"");
    auto l3 = LiteralFactory::getInstance().makeLiteralFromString("\"5*(4+3)*2\"");
    auto op1 = OperatorManager::getInstance().getOperator("DUP");
    auto op2 = OperatorManager::getInstance().getOperator("+");
    auto op3 = OperatorManager::getInstance().getOperator("*");
    auto result1 = OperatorManager::getInstance().dispatchOperation(op1, Arguments<std::shared_ptr<Literal>>{l1, l2});
    auto result2 = OperatorManager::getInstance().dispatchOperation(op2, Arguments<std::shared_ptr<Literal>>{l1, l2});
    auto result3 = OperatorManager::getInstance().dispatchOperation(op3, Arguments<std::shared_ptr<Literal>>{l1, l2});
    auto result4 = OperatorManager::getInstance().dispatchOperation(op3, Arguments<std::shared_ptr<Literal>>{l3, l2});
    std::cout << l1->toString() << " " << op1->toString() << " " << l2->toString() << " = ";
    for(auto res : result1) std::cout << res->toString() << std::endl;
    std::cout << l1->toString() << " " << op2->toString() << " " << l2->toString() << " = ";
    for(auto res : result2) std::cout << res->toString() << std::endl;
    std::cout << l1->toString() << " " << op3->toString() << " " << l2->toString() << " = ";
    for(auto res : result3) std::cout << res->toString() << std::endl;
    std::cout << l3->toString() << " " << op3->toString() << " " << l2->toString() << " = ";
    for(auto res : result4) std::cout << res->toString() << std::endl;

    auto a1 = LiteralFactory::getInstance().makeLiteralFromString("[4 + 3]");
    Manager::getInstance().addIdentifier("PROG1", a1);
    auto a2 = LiteralFactory::getInstance().makeLiteralFromString("[4 + 3]");
    Manager::getInstance().addIdentifier("PROG2", a2);
    auto a3 = LiteralFactory::getInstance().makeLiteralFromString("\"4+3\"");
    Manager::getInstance().addIdentifier("EXP1", a3);

    std::cout << "Tableau des prog :" << std::endl;
    auto tab = Manager::getInstance().getProgramsIdentifiers();
    for(auto res :tab) std::cout << res.first << std::endl;

    std::cout << "Tableau des variables :" << std::endl;
    auto tab2 = Manager::getInstance().getVariablesIdentifiers();
    for(auto res :tab2) std::cout << res.first << std::endl;*/

    std::string expr = "3+4";
    std::cout << "Expression : " << expr << std::endl;
    ExpressionParser e(expr);
    for(auto l : e.parse()) {
        std::cout << l->toString() << " " << std::endl;
    }
    std::cout << std::endl;

    /*QApplication a(argc, argv);
    UTComputer w;
    w.show();
    return a.exec();*/

    return 0;
}
