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
    allocatorsPriority.push_back(std::bind(&LiteralFactory::makeRational, this, std::placeholders::_1));
    allocatorsPriority.push_back(std::bind(&LiteralFactory::makeReal, this, std::placeholders::_1));
    allocatorsPriority.push_back(std::bind(&LiteralFactory::makeComplex, this, std::placeholders::_1));
    allocatorsPriority.push_back(std::bind(&LiteralFactory::makeExpression, this, std::placeholders::_1));
    allocatorsPriority.push_back(std::bind(&LiteralFactory::makeCompositeProgram, this, std::placeholders::_1));
}

const LiteralFactory& LiteralFactory::getInstance() {
     static LiteralFactory instance; //Libérée automatiquement
     return instance;
}

std::shared_ptr<Literal> LiteralFactory::makeInteger(const std::string& s) const {
    try {
        return makeLiteral(Utility::stringToOther<int>(s));
    }
    catch(UTException& e) {
        throw ParsingError(s, "Not an integer").add(e);
    }
}

std::shared_ptr<Literal> LiteralFactory::makeRational(const std::string &s) const {
    std::string::size_type sepIdx = s.find_first_of('/');
    if(sepIdx != std::string::npos) {
        int num = Utility::stringToOther<int>(s.substr(0, sepIdx));
        auto den = Utility::stringToOther<int>(s.substr(sepIdx + 1));
        return makeLiteral(num, den);
    }
    throw UTException("Not a rational (format : integer/integer");
}

std::shared_ptr<Literal> LiteralFactory::makeReal(const std::string& s) const {
    try {
        return makeLiteral(Utility::stringToOther<double>(s));
    }
    catch(UTException& e) {
        throw ParsingError(s, "Not an integer").add(e);
    }
}

std::shared_ptr<Literal> LiteralFactory::makeComplex(const std::string &s) const {
    std::string::size_type sepIdx = s.find_first_of('$');
    if(sepIdx != std::string::npos) {
        auto num = std::dynamic_pointer_cast<NumericLiteral>(makeLiteralFromString(s.substr(0, sepIdx)));
        auto den = std::dynamic_pointer_cast<NumericLiteral>(makeLiteralFromString(s.substr(sepIdx + 1)));
        if(num && den) return makeLiteral(num, den);
        throw UTException("Well formed complex but real or imaginary part is not numeric");
    }
    throw UTException("Not a complex (format : numeric$numeric");
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
            //L'opérande n'est pas reconnue, on encapsule dans une expression
            catch (UTException& e2) {
                prog->add(makeLiteral(str));
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
    if(den == 0) {
        throw UTException("Impossible to divide by 0");
    }
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
    if (std::modf(f, &intpart) == 0.0) return makeLiteral((int)intpart);
    return std::make_shared<RealLiteral>(f);
}

std::shared_ptr<Literal> LiteralFactory::makeLiteral(std::shared_ptr<NumericLiteral> re, std::shared_ptr<NumericLiteral> im) const {
    //Cas où la littérale n'est pas numérique.
    if(std::dynamic_pointer_cast<ComplexLiteral>(re) || std::dynamic_pointer_cast<ComplexLiteral>(im)) throw TypeError("Complexs can't be part of complex.", {re, im});
    //Cas où la partie imaginaire est nulle, on crée une littérale d'un type moins général.
    if((RealLiteral)*im == 0) return makeLiteral((RealLiteral)*re);
    return std::make_shared<ComplexLiteral>(re, im);
}

std::shared_ptr<Literal> LiteralFactory::makeLiteral(std::complex<double> c) const {
    auto re = std::static_pointer_cast<NumericLiteral>(makeLiteral(c.real()));
    auto im = std::static_pointer_cast<NumericLiteral>(makeLiteral(c.imag()));
    return makeLiteral(re, im);
}

std::shared_ptr<Literal> LiteralFactory::makeLiteral(const std::string &s) const {
    return std::make_shared<ExpressionLiteral>(s);
}

