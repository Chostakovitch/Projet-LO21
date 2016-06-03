#ifndef SETTINGS_H
#define SETTINGS_H

class Settings
{
    unsigned int nbLinesDisplayPile;
    bool displayKeyboard;
    bool beepMessage;
public:
    Settings(unsigned int n = 6, bool d = true, bool b = true): nbLinesDisplayPile(n), displayKeyboard(d), beepMessage(b) {}
    unsigned int getNbLinesDisplayPile() const { return nbLinesDisplayPile; }
    bool getDisplayKeyboard() const { return displayKeyboard;}
    bool getBeepMessage() const { return beepMessage; }
    void setNbLinesDisplayPile(unsigned int value) { nbLinesDisplayPile = value; }
    void setDisplayKeyboard(bool value) { displayKeyboard = value;}
    void setBeepMessage(bool value) { beepMessage = value; }
    bool operator==(Settings s) { return s.nbLinesDisplayPile == nbLinesDisplayPile && s.displayKeyboard == displayKeyboard && beepMessage == s.beepMessage; }
    bool operator!=(Settings s) {return !operator==(s); }
};

#endif // SETTINGS_H
