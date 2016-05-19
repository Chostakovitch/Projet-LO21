#include "ExpressionParser.h"
#include <cctype>

/**
 * @details Un jeton peut être :
 *      - Un nombre entier ou flottant;
 *      - Un symbole (i.e. caractère non chiffre et non lettre);
 *      - Une suite de lettres capitales et/ou de chiffres commençant par une lettre capitale.
 */
std::string ExpressionParser::readToken() {
    std::string res;
    try {
        //Un jeton a au moins un caractère.
        char c = expr.at(0);
        res += c;
        //Cas n°1 : le premier élément est un symbole.
        if(!std::isalnum(c) && std::isgraph(c)) expr.erase(0, 1);
        //Cas n°2 : le premier élément est une lettre capitale, on trouve l'atome correspondant.
        else if(std::isupper(c)) {
            expr.erase(0, 1);
            while(!expr.empty() && (c = expr.at(0)) && (std::isupper(c) || std::isdigit(c))) {
                res += c;
                expr.erase(0, 1);
            }
        }
        //Cas n°3 : le premier élément est un chiffre, on trouve le nombre correspondant.
        else if(std::isdigit(c)) {
            expr.erase(0, 1);
            while(!expr.empty() && (c = expr.at(0)) && (std::isdigit(c) || c == decimal_sep)) {
                res += c;
                expr.erase(0, 1);
            }
        }
    }
    //Aucun jeton n'a pu être construit sans sortir de la chaîne
    catch(std::out_of_range& e) {
        return std::string();
    }
}
