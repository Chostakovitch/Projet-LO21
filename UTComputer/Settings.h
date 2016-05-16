#ifndef SETTINGS_H
#define SETTINGS_H


class Settings
{
    unsigned int nbLinesDisplayPile;
    bool displayKeyboard;
    bool beepMessage;
public:
    Settings(unsigned int n = 10, bool d = true, bool b = true) : nbLinesDisplayPile(n), displayKeyboard(d), beepMessage(b) {}
    unsigned int getNbLinesDisplayPile() { return nbLinesDisplayPile; }
    bool getDisplayKeyboard() { return displayKeyboard;}
    bool getBeepMessage() { return beepMessage; }
};

#endif // SETTINGS_H
