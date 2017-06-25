#include "ExpressionParser.h"
#include "Manager.h"
#include "LiteralFactory.h"
#include "OperatorManager.h"
#include "UTException.h"
#include "Utility.h"
#include <cctype>
#include <algorithm>

/**
 * @brief Constructeur de base.
 * @param s Chaîne à parser
 * @param left_del Délimiteur gauche de fonction ou de priorité.
 * @param right_del Délimiteur droite de fonction ou de priorité.
 * @param function_param_sep Séparateur d'arguments de fonction.
 * @param decimal_sep Séparateur des décimales pour les nombres.
 * @details Transformation préalable du "-" unaire en "NEG".
 * @exception std::invalid_argument si la chaîne est mal formée.
 */
ExpressionParser::ExpressionParser(const std::string& s, char left_del, char right_del, char function_param_sep, char decimal_sep) \
    : expr(s), left_del(left_del), right_del(right_del), function_param_sep(function_param_sep), decimal_sep(decimal_sep), stack(std::stack<std::shared_ptr<Operand>>()), queue(std::vector<std::shared_ptr<Operand>>()) {
    //Remplacement du moins unaire représentant la négation par un moins binaire (soustraction de 0)
    std::string from = OperatorManager::getInstance().getMinusSymbol();
    std::string to = std::string("0") + from;
    size_t pos = 0;
    while((pos = expr.find(from, pos)) != std::string::npos) {
        if(pos == 0 || Utility::isSymbol(expr.at(pos - 1))) expr.replace(pos, from.length(), to);
        pos += to.length();
    }
}

/**
 * @details Implémentation de l'algorithme de Shunting-Yard.
 */
std::vector<std::shared_ptr<Operand>> ExpressionParser::parse() {
    //Tant qu'il reste des jetons à lire
    std::string token;
    while(!expr.empty()) {
        //Jeton vide, intraitable
        if((token = readToken()).empty()) throw ParsingError(token, "Empty token.");

        //Cas où le jeton est une littérale, on l'enfile
        if(auto lit = getLiteral(token)) queue.push_back(lit);

        //Cas où le jeton est une fonction, on l'empile
        else if(auto fun = getFunction(token)) stack.push(fun);

        //Cas où le jeton est un séparateur d'arguments de fonction
        else if(token.at(0) == function_param_sep) {
            //Jusqu'à ce qu'on trouve un délimiteur gauche, on dépile et enfile chaque opérateur
            while(!stack.empty() && operandToString(stack.top()).at(0) != left_del) {
                queue.push_back(stack.top());
                stack.pop();
            }
            if(stack.empty()) throw ParsingError(expr, "Parentheses mismatch.");
        }

        //Cas où le jeton est un opérateur symbolique
        else if(auto op = getOperator(token)) {
            /* Tant qu'on trouve un opérateur symbolique sur la pile,
             * Si l'opérateur est associatif à gauche et de priorité inférieure ou égale au nouveau,
             * ou s'il est associatif à droite et de priorité inférieure au nouveau, on le dépile et l'enfile */
            std::shared_ptr<SymbolicOperator> op2;
            while(!stack.empty() \
                  && (op2 = std::dynamic_pointer_cast<SymbolicOperator>(stack.top())) \
                  && ( \
                        (op->isLeftAssociative() && op->getPriority() <= op2->getPriority()) \
                      || \
                        (!op->isLeftAssociative() && op->getPriority() < op2->getPriority()) \
                     ) \
                 )
                {
                    queue.push_back(op2);
                    stack.pop();
                }
            stack.push(op);
        }

        //Délimiteur gauche, on l'empile
        else if(token.at(0) == left_del) stack.push(LiteralFactory::getInstance().makeLiteral(std::string(1, left_del)));

        //Délimiteur droit
        else if(token.at(0) == right_del) {
            //Tant qu'on ne trouve pas de délimiteur gauche
            while(!stack.empty() && operandToString(stack.top()).at(0) != left_del) {
                queue.push_back(stack.top());
                stack.pop();
            }
            if(stack.empty()) throw ParsingError(expr, "Parentheses mismatch.");
            //On dépile la parenthèse
            stack.pop();
            //S'il reste une fonction sur la pile
            std::shared_ptr<FunctionOperator> fun;
            if(!stack.empty() && (fun = std::dynamic_pointer_cast<FunctionOperator>(stack.top()))) {
                queue.push_back(fun);
                stack.pop();
            }
        }

        //Jeton non-reconnu
        else {
            throw ParsingError(token, "Unrecognized token.");
        }
    }

    //Tant qu'il reste des opérateurs sur la pile
    while(!stack.empty()) {
        //S'il reste un délimiteur gauche, expression malformée
        if(operandToString(stack.top()).at(0) == left_del) throw ParsingError(expr, "Parentheses mismatch.");
        queue.push_back(stack.top());
        stack.pop();
    }

    return queue;
}

/**
 * @details Un jeton peut être :
 *      - Un nombre entier ou flottant;
 *      - Un symbole (i.e. caractère non chiffre et non lettre);
 *      - Une suite de lettres capitales et/ou de chiffres commençant par une lettre capitale.
 */
std::string ExpressionParser::readToken() {
    std::string res;
    //Plus aucun jeton à lire.
    if(expr.empty()) return res;
    //Un jeton a au moins un caractère qu'on consumme directement.
    char c = expr.at(0);
    expr.erase(0, 1);
    res += c;
    //Cas n°1 : le premier élément est un symbole, on cherche les symboles composant éventuellement la suite d'un opérateur
    if(Utility::isSymbol(c)) {
        //On tombe sur un symbole non connu
        if(c != left_del && c != right_del && c != function_param_sep && c != decimal_sep)
        while(!expr.empty() && (c = expr.at(0)) && Utility::isSymbol(c) && c != left_del && c != right_del && c != function_param_sep && c != decimal_sep) {
            res += c;
            expr.erase(0, 1);
        }
    }
    //Cas n°2 : le premier élément est une lettre capitale, on trouve l'atome correspondant.
    else if(std::isupper(c)) {
        while(!expr.empty() && (c = expr.at(0)) && (std::isupper(c) || std::isdigit(c))) {
            res += c;
            expr.erase(0, 1);
        }
    }
    //Cas n°3 : le premier élément est un chiffre, on trouve le nombre correspondant.
    else if(std::isdigit(c)) {
        while(!expr.empty() && (c = expr.at(0)) && (std::isdigit(c) || c == decimal_sep)) {
            res += c;
            expr.erase(0, 1);
        }
    }
    return res;
}

std::shared_ptr<Literal> ExpressionParser::getLiteral(std::string token) {
    //Identificateur d'une variable
    try {
        auto id = Manager::getInstance().getIdentifier(token);
        if(std::dynamic_pointer_cast<ProgramLiteral>(id)) throw ParsingError(id->toString(), "A program identifier can't be part of expression.");
        return id;
    }
    //Construction d'une littérale
    catch(UTException&) {
        try {
            return LiteralFactory::getInstance().makeLiteralFromString(token);
        }
        catch(UTException&) { return nullptr; }
    }
}

std::shared_ptr<FunctionOperator> ExpressionParser::getFunction(std::string token) {
    try {
        return std::dynamic_pointer_cast<FunctionOperator>(OperatorManager::getInstance().getOperator(token));
    } catch(UTException&) { return nullptr; }
}

std::shared_ptr<SymbolicOperator> ExpressionParser::getOperator(std::string token) {
    try {
        return std::dynamic_pointer_cast<SymbolicOperator>(OperatorManager::getInstance().getOperator(token));
    } catch(UTException&) { return nullptr; }
}

std::string ExpressionParser::operandToString(std::shared_ptr<Operand> op) const {
    if(auto expr = std::dynamic_pointer_cast<ExpressionLiteral>(op)) return expr->getExpression();
    return op->toString();
}
