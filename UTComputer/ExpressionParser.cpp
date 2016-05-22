#include "ExpressionParser.h"
#include "Manager.h"
#include "LiteralFactory.h"
#include "OperatorManager.h"
#include <cctype>

/**
 * @details Implémentation de l'algorithme de Shunting-Yard.
 */
std::vector<std::shared_ptr<Operand>> ExpressionParser::parse() {
    //Tant qu'il reste des jetons à lire
    std::string token;
    while(!expr.empty()) {
        //Jeton vide, intraitable
        if((token = readToken()).empty()) throw std::invalid_argument("Unreadable token.");

        //Cas où le jeton est une littérale, on l'enfile
        if(auto lit = getLiteral(token)) queue.push_back(lit);

        //Cas où le jeton est une fonction, on l'empile
        else if(auto fun = getFunction(token)) stack.push(fun);

        //Cas où le jeton est un séparateur d'arguments de fonction
        else if(token.at(0) == function_param_sep) {
            //Jusqu'à ce qu'on trouve un délimiteur gauche, on dépile et enfile chaque opérateur
            while(!stack.empty() && stack.top()->toString().at(0) != left_del) {
                queue.push_back(stack.top());
                stack.pop();
            }
            if(stack.empty()) throw std::invalid_argument("Parentheses mismatch.");
        }

        //Cas où le jeton est un opérateur symbolique
        else if(auto op = getOperator(token)) {
            /* Tant qu'on trouve un opérateur symbolique sur la pile,
             * Si l'opérateur est associatif à gauche et de priorité inférieure ou égale au nouveau,
             * ou s'il est associatif à droite et de priorité inférieure au nouveau, on le dépile et l'enfile*/
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
            while(!stack.empty() && stack.top()->toString().at(0) != left_del) {
                queue.push_back(stack.top());
                stack.pop();
            }
            if(stack.empty()) throw std::invalid_argument("Parentheses mismatch.");
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
            throw std::invalid_argument("Unrecognized token.");
        }
    }

    //Tant qu'il reste des opérateurs sur la pile
    while(!stack.empty()) {
        //S'il reste un délimiteur gauche, expression malformée
        if(stack.top()->toString().at(0) == left_del) throw std::invalid_argument("Parentheses mismatch.");
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
    //Cas n°1 : le premier élément est un symbole.
    if(!std::isalnum(c) && std::isgraph(c)) return res;
    //Cas n°2 : le premier élément est une lettre capitale, on trouve l'atome correspondant.
    if(std::isupper(c)) {
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
        if(std::dynamic_pointer_cast<ProgramLiteral>(id)) throw std::invalid_argument("A program identifier can't be part of expression.");
        return id;
    }
    //Construction d'une littérale
    catch(std::out_of_range& e) {
        try {
            return LiteralFactory::getInstance().makeLiteralFromString(token);
        }
        catch(std::exception&) { return nullptr; }
    }
}

std::shared_ptr<FunctionOperator> ExpressionParser::getFunction(std::string token) {
    try {
        return std::dynamic_pointer_cast<FunctionOperator>(OperatorManager::getInstance().getOperator(token));
    } catch(std::exception&) { return nullptr; }
}

std::shared_ptr<SymbolicOperator> ExpressionParser::getOperator(std::string token) {
    try {
        return std::dynamic_pointer_cast<SymbolicOperator>(OperatorManager::getInstance().getOperator(token));
    } catch(std::exception&) { return nullptr; }
}
