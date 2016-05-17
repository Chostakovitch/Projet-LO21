#include <QApplication>
#include <iostream>

#include "utcomputer.h"
#include "OperatorManager.h"
#include "Literal.h"
#include "Operateurs.h"
#include "LiteralFactory.h"
#include "Operation.h"
#include "Calculator.h"

int main(int argc, char *argv[])
{

    //Parsing des littéraux
    //auto l1 = LiteralFactory::getInstance().makeLiteralFromString("2.4");
    //auto l2 = LiteralFactory::getInstance().makeLiteralFromString("5");

    //Instance de l'opérateur
    auto op = OperatorManager::getInstance().getOperator("+");

    //Liste d'arguments générique
   // Arguments<std::shared_ptr<Literal>> args = { l1, l2 };

    //Promotion des arguments et appel de la bonne fonction de calcul
    /*try {
        auto result = OperatorManager::getInstance().dispatchOperation(op, args);
        for (auto arg : args) std::cout << typeid(*arg).name() << " : " << arg->toString() << std::endl;
        //Affichage du vecteur de retour
        for (auto res : result) std::cout << typeid(*res).name() << " : " << res->toString() << std::endl;
    } catch(std::exception& e) { std::cout << e.what() << std::endl; }

    /*auto p1 = factory.makeLiteralFromString("[ DUP 0.5 < [ NEG ] IFT ]");
    std::cout << p1->toString() << std::endl;

    QApplication a(argc, argv);
    UTComputer w;
    w.show();

    return a.exec();*/

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

    QApplication a(argc, argv);
    UTComputer w;
    w.show();

    return a.exec();
}
