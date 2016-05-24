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
};

#endif // SETTINGS_H
