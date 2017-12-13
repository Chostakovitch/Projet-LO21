#ifndef SETTINGS_H
#define SETTINGS_H

/**
 * @brief La classe Settings contient les options du calculateur : le nombre lignes de la pile à afficher, le bip du message utilisateur et l'affichage du clavier clickable.
 */
class Settings
{
    /**
     * @brief Entier non signé representant le nombre lignes de la pile à afficher.
     */
    unsigned int nbLinesDisplayPile;
    /**
     * @brief Bool designant la présence clavier clickable.
     */
    bool displayKeyboard;
    /**
     * @brief Bool designant la présence du bip du message utilisateur.
     */
    bool beepMessage;
public:
    /**
     * @brief Constructeur public de la classe Settings.
     * @param n Entier non signé representant le nombre lignes de la pile à afficher.
     * @param d Bool designant la présence clavier clickable.
     * @param b Bool designant la présence du bip du message utilisateur.
     */
    Settings(unsigned int n = 6, bool d = true, bool b = true): nbLinesDisplayPile(n), displayKeyboard(d), beepMessage(b) {}
    /**
     * @brief Accesseur au nombre lignes de la pile à afficher.
     * @return Entier non signé representant le nombre lignes de la pile à afficher.
     */
    unsigned int getNbLinesDisplayPile() const { return nbLinesDisplayPile; }
    /**
     * @brief Accesseur à la présence du bip du message utilisateur.
     * @return Bool designant la présence clavier clickable.
     */
    bool getDisplayKeyboard() const { return displayKeyboard;}
    /**
     * @brief Accesseur à la présence du bip du message utilisateur.
     * @return Bool designant la présence du bip du message utilisateur.
     */
    bool getBeepMessage() const { return beepMessage; }
    /**
     * @brief Mutateur du nombre lignes de la pile à afficher.
     * @param value Entier non signé representant le nombre lignes de la pile à afficher.
     */
    void setNbLinesDisplayPile(unsigned int value) { nbLinesDisplayPile = value; }
    /**
     * @brief Mutateur de la présence du bip du message utilisateur.
     * @param value Bool designant la présence clavier clickable.
     */
    void setDisplayKeyboard(bool value) { displayKeyboard = value;}
    /**
     * @brief Mutateur de la présence du bip du message utilisateur.
     * @param value Bool designant la présence du bip du message utilisateur.
     */
    void setBeepMessage(bool value) { beepMessage = value; }

    bool operator==(Settings s) { return s.nbLinesDisplayPile == nbLinesDisplayPile && s.displayKeyboard == displayKeyboard && beepMessage == s.beepMessage; }
    bool operator!=(Settings s) {return !operator==(s); }
};

#endif // SETTINGS_H
