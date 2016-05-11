#include "utcomputer.h"
#include "OperatorManager.h"
#include "Literal.h"
#include "Operateurs.h"
#include "LiteralFactory.h"
#include "Operation.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    //Singletons
    LiteralFactory& factory = LiteralFactory::getInstance();
    OperatorManager& manager = OperatorManager::getInstance();
    /*
    //Parsing des littéraux
    auto l1 = factory.makeLiteralFromString("2");
    auto l2 = factory.makeLiteralFromString("5.4");

    //Instance de l'opérateur
    auto op = manager.getOperator("+");

    //Liste d'arguments générique
    Arguments<std::shared_ptr<Literal>> args = { l1, l2 };

    //Promotion des arguments et appel de la bonne fonction de calcul
    auto result = manager.dispatchOperation(op, args);

    for (auto arg : args) std::cout << typeid(*arg).name() << " : " << arg->toString() << std::endl;
    //Affichage du vecteur de retour
    for (auto res : result) std::cout << typeid(*res).name() << " : " << res->toString() << std::endl;
    */

    auto p1 = factory.makeLiteralFromString("[ DUP 0.5 < [ NEG ] IFT ]");
    std::cout << p1->toString() << std::endl;
    getchar();

    /*QApplication a(argc, argv);
    UTComputer w;
    w.show();

    return a.exec();*/
    return 0;
}
