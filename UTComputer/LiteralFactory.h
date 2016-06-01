/**
  @file LiteralFactory.h
  @brief Fichier de référence pour le parsing et l'instanciation de littéraux.
  */

#ifndef LITERALFACTORY_H
#define LITERALFACTORY_H
#include "Literal.h"
#include "CompositeLiteral.h"
#include <memory>
#include <functional>
#include <vector>
#include <complex>

class LiteralFactory
{
    /**
     * @brief Constructeur privé qui initialise la fabrique.
     */
    LiteralFactory();
    /**
     * @brief Création d'une littérale entière à partir d'une chaîne.
     * @param s Chaîne de caractères représentant un nombre entier positif.
     * @exception invalid_argument si le format de la chaîne est incorrect.
     * @return Pointeur sur Literal.
     */
    std::shared_ptr<Literal> makeInteger(const std::string& s) const;
    /**
     * @brief Création d'une littérale réelle à partir d'une chaîne.
     * @param s Chaîne de caractères sous la forme _entier.entier_.
     * @exception invalid_argument si le format de la chaîne est incorrect.
     * @return Pointeur sur Literal.
     */
	std::shared_ptr<Literal> makeReal(const std::string& s) const;
    /**
     * @brief Création d'une littérale expression à partir d'une chaîne.
     * @param s Chaîne de caractères sous la forme __"sample"__, guillemets inclus.
     * @exception invalid_argument si le format de la chaîne est incorrect.
     * @return Pointeur sur Literal.
     */
	std::shared_ptr<Literal> makeExpression(const std::string& s) const;
    /**
     * @brief Création d'une littérale programme comportant potientiellement des littérales programmes.
     * @param s Chaîne de caractères sous la forme __[op1 op2 op3]__, crochets inclus.
     * @exception invalid_argument si le format de la chaîne est incorrect.
     * @return Pointeur sur Literal.
     */
	std::shared_ptr<Literal> makeCompositeProgram(const std::string& s) const;
    /**
     * @brief Remplissage d'une littérale programme feuille, i.e. sans sous-programme.
     * @param s Chaîne de caractères terminales, contenant des représentations de littérales (hors programme).
     * @param prog Pointeur sur un objet ProgramLiteral à remplir.
     */
	void makeLeafProgram(const std::string &s, std::shared_ptr<ProgramLiteral> prog) const;
    /**
     * @brief Vecteur de fonctions de création de Literal.
     * @details Les fonctions sont pushées dans l'ordre croissant de généralité. On essayera d'abord de fabriquer
     * les types les moins généraux, et ensuite les plus généraux.
     */
    std::vector<std::function<std::shared_ptr<Literal>(const std::string&)>> allocatorsPriority;
public:
    /**
     * @brief Récupération de l'instance du singleton.
     * @return Référence constance sur LiteralFactory.
     */
    static const LiteralFactory& getInstance();
    /**
     * @brief Suppression du constructeur de recopie.
     */
	LiteralFactory(const LiteralFactory&) = delete;
    /**
     * @brief Suppression de l'opérateur d'affectation.
     */
	void operator=(const LiteralFactory&) = delete;
    /**
     * @brief Méthode générale de fabrication d'une littérale quelconque à partir d'une chaîne.
     * @details Appels successifs et ordonnées des fonctions référencés par _allocatorsPriority_.
     * @param str Chaîne à parser.
     * @exception invalid_argument Si aucun modèle de fabrique n'a reconnu le format de la chaîne.
     * @return Pointeur sur Literal.
     */
	std::shared_ptr<Literal> makeLiteralFromString(std::string str) const;
    /**
     * @brief Fabrique d'un objet IntegerLiteral.
     * @param n Entier relatif.
     * @return Pointeur sur Literal.
     */
	std::shared_ptr<Literal> makeLiteral(int n) const;
    /**
     * @brief Fabrique d'un objet RationalLiteral ou IntegerLiteral (voir description complète).
     * @details Avant instanciation, le numérateur et le dénominateur sont divisés par leur PGCD et le signe moins passe au numérateur s'il existe.
     * Si le nouveau dénominateur vaut 1, un objet IntegerLiteral est construit. Sinon, un objet RationalLiteral simplifié est construit.
     * @param num Entier relatif représentant le numérateur.
     * @param den Entier relatif représentant le dénominateur.
     * @return Pointeur sur Literal.
     */
	std::shared_ptr<Literal> makeLiteral(int num, int den) const;
    /**
     * @brief Fabrique d'un objet RealLiteral.
     * @param f Nombre à virgule flottante.
     * @return Pointeur sur Literal.
     */
	std::shared_ptr<Literal> makeLiteral(double f) const;
    /**
     * @brief Fabrique d'un objet ComplexLiteral.
     * @param re Partie réelle.
     * @param im Partie imaginaire.
     * @return Pointeur sur Literal.
     */
    std::shared_ptr<Literal> makeLiteral(std::shared_ptr<NumericLiteral> re, std::shared_ptr<NumericLiteral> im) const;
    /**
     * @brief Fabrique d'un objet ComplexLiteral.
     * @param c std::complex de la librairie standard.
     * @return Pointeur sur Literal.
     */
    std::shared_ptr<Literal> makeLiteral(std::complex<double> c) const;
    /**
     * @brief Fabrique d'un objet ExpressionLiteral.
     * @param s Chaîne quelconque.
     * @return Pointeur sur Literal.
     */
	std::shared_ptr<Literal> makeLiteral(const std::string& s) const;
};
#endif
