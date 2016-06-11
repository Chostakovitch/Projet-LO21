#ifndef MAINFRAME_H
#define MAINFRAME_H

#include <QFrame>
#include <memory>

class Button;

/**
 * @brief La classe MainFrame est un élément graphique qui contient le clavier clickable
 * @details Le clavier clickable est constitué des chiffres, des opérateurs symbolique, d'un bouton vers la fenétre des autres opérateurs, et de touches tel que "Entré", backspace etc.
 */
class MainFrame : public QFrame
{
    Q_OBJECT
public:
    /**
     * @brief Constructeur public de la classe MainFrame.
     * @param parent Element graphique parent de l'objet.
     */
    MainFrame(QWidget *parent = 0);
public slots:

private:
    /**
     * @brief La fonction createButton crée un élement Button.
     * @param text Le texte du bouton.
     * @param member Le nom du SLOT auquel sera attaché le bouton.
     * @return Le Button créé.
     */
    Button* createButton(const QString &text, const char *member);

    enum { NumDigitButtons = 10 };
    /**
     * @brief Le tableau digitButtons contient les boutons des chiffres du clavier clickable.
     */
    Button* digitButtons[NumDigitButtons];
};

/**
 * @brief La classe WindowMoreOperators est une fenétre affichant les boutons des opérateurs non-symbolique.
 */
class WindowMoreOperators : public QWidget {
    Q_OBJECT
public :
    /**
     * @brief Constructeur public de la classe WindowMoreOperators.
     * @param parent Element graphique parent de l'objet.
     */
    WindowMoreOperators(QWidget* parent = 0);
};

/**
 * @brief La classe HistoryWindow est une fenêtre affichant l'historique des commandes évaluées.
 */
class HistoryWindow : public QWidget {
    Q_OBJECT
public :
    /**
     * @brief Constructeur public de la classe HistoryWindow.
     * @param parent Element graphique parent de l'objet.
     */
    HistoryWindow(QWidget* parent = 0);
};

#endif // MAINFRAME_H
