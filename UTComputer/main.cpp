#include <QApplication>
#include <iostream>

#include "utcomputer.h"
#include "OperatorManager.h"
#include "Literal.h"
#include "Operateurs.h"
#include "LiteralFactory.h"
#include "Operation.h"

int main(int argc, char *argv[])
{
    //Parsing des littéraux
    auto l1 = LiteralFactory::getInstance().makeLiteralFromString("2.4");
    auto l2 = LiteralFactory::getInstance().makeLiteralFromString("5");

    //Instance de l'opérateur
    auto op = OperatorManager::getInstance().getOperator("+");

    //Liste d'arguments générique
    Arguments<std::shared_ptr<Literal>> args = { l1, l2 };

    //Promotion des arguments et appel de la bonne fonction de calcul
    try {
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

    return 0;
}
