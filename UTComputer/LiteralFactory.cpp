#include "LiteralFactory.h"
#include "OperatorManager.h"
#include "Utility.h"
#include "UTException.h"
#include <algorithm>
#include <sstream>
#include <vector>
#include <iterator>
#include <cmath>

/**
 * @details Ce constructeur sert à définir l'ordre des tentatives réalisées pour parser une chaîne de caractères en
 * objet de type Literal, du type le plus spécialisé au type le plus général (i.e. un type spécialisé peut toujours
 * être casté en type plus général sans perte d'information). Les types pouvant être construits directement à partir d'une
 * chaîne de caractères (i.e. sans l'application d'un opérateur) sont, dans l'ordre : IntegerLiteral, RealLiteral, ExpressionLiteral et ProgramLiteral.
 */
LiteralFactory::LiteralFactory() {
    //Push dans l'ordre de priorité descendante
    allocatorsPriority.push_back(std::bind(&LiteralFactory::makeInteger, this, std::placeholders::_1));
    allocatorsPriority.push_back(std::bind(&LiteralFactory::makeReal, this, std::placeholders::_1));
    allocatorsPriority.push_back(std::bind(&LiteralFactory::makeExpression, this, std::placeholders::_1));
    allocatorsPriority.push_back(std::bind(&LiteralFactory::makeCompositeProgram, this, std::placeholders::_1));
}

const LiteralFactory& LiteralFactory::getInstance() {
     static LiteralFactory instance; //Libérée automatiquement
     return instance;
}

std::shared_ptr<Literal> LiteralFactory::makeInteger(const std::string& s) const {
    try {
        int n = std::stoi(s);
        auto d = std::to_string(n);
        bool a = std::to_string(n) != s || n < 0;
        if(std::to_string(n) != s || n < 0) throw ParsingError(s, "Unsigned number needed.");
        return makeLiteral(n);
    }
    catch(std::exception& e) { throw ParsingError(s, e.what()); }
}

std::shared_ptr<Literal> LiteralFactory::makeReal(const std::string& s) const {
    try {
        double d = std::stod(s);
        if(d < 0) throw ParsingError(s, "Positive flotting point number needed.");
        return makeLiteral(d);
    }
    catch(std::exception& e) { throw ParsingError(s, e.what()); }
}

std::shared_ptr<Literal> LiteralFactory::makeExpression(const std::string& s) const {
    std::string copy(s);
    copy.erase(std::remove(copy.begin(), copy.end(), ' '), copy.end()); //Suppression des espaces
    if (s.front() == '"' && s.back() == '"') {
        copy.erase(0, 1);
        copy.erase(copy.size() - 1);
        return makeLiteral(copy);
    }
    throw ParsingError(s, "Expressions must be surrounded by double quotes.");
}

void LiteralFactory::makeLeafProgram(const std::string &s, std::shared_ptr<ProgramLiteral> prog) const {
    std::istringstream iss(s);

    //Construction de strings selon les espaces (istream_iterator<>() = end-of-stream iterator : équivalent du end() sur une collection)
    std::vector<std::string> ops { std::istream_iterator<std::string>(iss), std::istream_iterator<std::string>() };
    for (auto str : ops) {
        try {
            //On tente d'abord de constuire une littérale
             prog->add(makeLiteralFromString(str));
        }
        //Sinon, on tente de récupérer l'instance d'un opérateur
        catch (UTException& e1) {
            try {
                 prog->add(OperatorManager::getInstance().getOperator(str));
            }
            //L'opérande n'est pas reconnue
            catch (UTException& e2) {
                throw ParsingError(str, "Unrecognized symbol.").add(e2).add(e1);
            }
        }
    }
}

std::shared_ptr<Literal> LiteralFactory::makeCompositeProgram(const std::string& s) const {
    auto prog = std::make_shared<ProgramLiteral>();
    std::string copy(s);
    size_t first, last;
    if (s.front() == '[' && s.back() == ']') {
        //On efface les délimiteurs de programme
        copy.erase(0, 1);
        copy.erase(copy.size() - 1);

        //On trouve le plus large sous-programme (s'il existe)
        first = copy.find_first_of('[');
        last = copy.find_last_of(']');

        //Cas où n'y a pas de sous-programme (feuille)
        if (first == std::string::npos && last == std::string::npos) makeLeafProgram(copy, prog);

        //Cas où il y a un sous-programme : traitement des deux (éventuelles) feuilles et du sous-programme (appel récursif)
        else if(first != std::string::npos && last != std::string::npos) {
            makeLeafProgram(copy.substr(0, first), prog);
            prog->add(makeCompositeProgram(copy.substr(first, last - first + 1)));
            makeLeafProgram(copy.substr(last + 1, copy.size() - last + 1), prog);
        }

        //Sous-programme malformé
        else {
            throw ParsingError(s, "Square bracket unclosed in subprogram.");
        }
        return prog;
    }
    throw ParsingError(s, "Programs and subprograms must be surrounded by square brackets.");
}

std::shared_ptr<Literal> LiteralFactory::makeLiteralFromString(std::string str) const {
    //On essaye de parser dans l'ordre de priorité, sachant que chaque fonction peut déclencher une exception
    ParsingError exc(str, "No literal could match the string.");
    for (auto alloc : allocatorsPriority) {
        try {
            return alloc(str);
        }
        catch(UTException& e) { exc.add(e); }
    }
    throw exc;
}

std::shared_ptr<Literal> LiteralFactory::makeLiteral(int n) const {
    return std::make_shared<IntegerLiteral>(n);
}

std::shared_ptr<Literal> LiteralFactory::makeLiteral(int num, int den) const {
    unsigned int gcd = Utility::computeGcd(num, den);
    //Passage du signe au numérateur
    if (den < 0) {
        num = -num;
        den = -den;
    }
    //Simplification
    num /= gcd;
    den /= gcd;
    if (den == 1) return makeLiteral(num); //Cas d'une simplification en entier
    return std::make_shared<RationalLiteral>(num, den);
}

std::shared_ptr<Literal> LiteralFactory::makeLiteral(double f) const {
    double intpart;
    //modf renvoie la partie fractionnaire et stocke la partie entière dans intpart
    if (std::modf(f, &intpart) == 0) return makeLiteral((int)intpart);
    return std::make_shared<RealLiteral>(f);
}

std::shared_ptr<Literal> LiteralFactory::makeLiteral(const std::string &s) const {
    return std::make_shared<ExpressionLiteral>(s);
}

