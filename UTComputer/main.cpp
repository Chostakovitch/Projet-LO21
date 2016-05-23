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

    std::cout << "backup 1 :" << std::endl;
    Manager::getInstance().afficherBackUp();

    auto a1 = LiteralFactory::getInstance().makeLiteralFromString("[4 + 3]");
    Manager::getInstance().addIdentifier("STO", a1);
    std::cout << "backup 2 :" << std::endl;
    Manager::getInstance().afficherBackUp();

    auto a2 = LiteralFactory::getInstance().makeLiteralFromString("[4 + 3]");
    Manager::getInstance().addIdentifier("PROG2", a2);
    std::cout << "backup 3 :" << std::endl;
    Manager::getInstance().afficherBackUp();

    auto a3 = LiteralFactory::getInstance().makeLiteralFromString("\"4+3\"");
    Manager::getInstance().addIdentifier("EXP1", a3);
    std::cout << "backup 4 :" << std::endl;
    Manager::getInstance().afficherBackUp();

    std::cout << "Changement de nom de PROG1 en TMP" << std::endl;
    Manager::getInstance().changeIdentifier("PROG1", "TMP", a1);
    std::cout << "backup 5 :" << std::endl;
    Manager::getInstance().afficherBackUp();

    std::cout << "Undo" << std::endl;
    Manager::getInstance().undo();
    std::cout << "backup 6 :" << std::endl;
    Manager::getInstance().afficherBackUp();

    std::cout << "Undo" << std::endl;
    Manager::getInstance().undo();
    std::cout << "backup 7 :" << std::endl;
    Manager::getInstance().afficherBackUp();

    std::cout << "Redo" << std::endl;
    Manager::getInstance().redo();
    std::cout << "backup 8 :" << std::endl;
    Manager::getInstance().afficherBackUp();

    auto a4 = LiteralFactory::getInstance().makeLiteralFromString("\"4+3\"");
    Manager::getInstance().addIdentifier("EXP2", a4);
    std::cout << "backup 9 :" << std::endl;
    Manager::getInstance().afficherBackUp();

    // Declenche une erreur comme prevu
    std::cout << "Redo" << std::endl;
    Manager::getInstance().redo();
    std::cout << "backup 10 :" << std::endl;
    Manager::getInstance().afficherBackUp();*/

    /*std::cout << "Tableau des prog :" << std::endl;
    auto tab = Manager::getInstance().getProgramsIdentifiers();
    for(auto res :tab) std::cout << res.first << std::endl;

    std::cout << "Tableau des variables :" << std::endl;
    auto tab2 = Manager::getInstance().getVariablesIdentifiers();
    for(auto res :tab2) std::cout << res.first << std::endl;*/

    /*auto l1 = LiteralFactory::getInstance().makeLiteralFromString("4");
    auto l2 = LiteralFactory::getInstance().makeLiteralFromString("4.5");
    auto l3 = LiteralFactory::getInstance().makeLiteralFromString("[4+3]");
    Manager::getInstance().addIdentifier("X", l1);
    Manager::getInstance().addIdentifier("X1", l2);
    Manager::getInstance().addIdentifier("X2", l3);
    std::string expr = "(3+45.8)+4*POW(X1,3.4)*(SIN(X)+5$2)";
    std::string expr1 = "X2";
    std::string expr2 = "(4+3";
    std::string expr3 = "4/2";
    std::string expr4 = "X3";
    std::string expr5 = "4+3)";
    std::vector<std::string> v1{expr, expr1, expr2, expr3, expr4, expr5};
    for(auto s : v1) {
        std::cout << "Expression : " << s << std::endl;
        ExpressionParser e(s);
        try {
            for(auto l : e.parse()) {
                std::cout << l->toString() << " ";
            }
        }
        catch(std::exception& e) {
            std::cout << e.what();
        }
        std::cout << std::endl << std::endl;
    }*/

    QApplication a(argc, argv);
    UTComputer w;
    w.show();
    return a.exec();

    //return 0;
}
