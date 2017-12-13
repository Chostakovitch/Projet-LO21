#ifndef UTCOMPUTER_H
#define UTCOMPUTER_H

#include <QMainWindow>
#include <QWidget>
#include <QMenuBar>

class Calculator;

/**
 * @brief La classe UTComputer est l'interface graphique principal, contenant les menus, le Widget principal.
 */
class UTComputer : public QMainWindow
{
    Q_OBJECT
    /**
     * @brief Widget central Calculator, contenant la ligne de commande, le message d'erreur, la pile et le clavier clickable.
     */
    Calculator* central;

    /**
     * @brief Action d'annulation de la dernière action.
     */
    QAction *undoAct;
    /**
     * @brief Action de restitution de l'état avant le undo.
     */
    QAction *redoAct;
    /**
     * @brief Action d'affichage des options.
     */
    QAction *paramAct;
    /**
     * @brief Action d'affichage de l'historique des commandes.
     */
    QAction *historyAct;

    /**
     * @brief Menu des paramétres de UTComputer.
     */
    QMenu* paramMenu;
    /**
     * @brief Manu d'édition de UTComputer.
     */
    QMenu* editMenu;

    /**
     * @brief Fonction créant les menus et les associants avec les actions.
     */
    void createMenus();
    /**
     * @brief Fonction créant les actions des élements des menus.
     */
    void createActions();

private slots:
    /**
     * @brief Slot d'annulation de la dernière action.
     */
    void undo();
    /**
     * @brief Slot de restitution de l'état avant le undo.
     */
    void redo();
    /**
     * @brief Slot d'affichage de l'historique des commandes.
     */
    void param();
    /**
     * @brief Slot d'enregistrement de l'état actuel.
     */
    void save();
    /**
     * @brief Slot de chargement de l'ancien état.
     */
    void load();
    /**
     * @brief Slot d'affichage de l'historique des commandes.
     */
    void history();
public:
    /**
     * @brief Constructeur public de la classe UTComputer.
     * @param parent Widget parent de l'objet.
     */
    explicit UTComputer(QWidget *parent = 0);
    /**
     * @brief Accesseur au Calculator qui est le widget central de l'objet.
     * @return Calculator
     */
    Calculator* getCalculator() { return central; }
    void showEvent(QShowEvent * e);
    void resizeEvent(QResizeEvent* event) ;


    static int const EXIT_CODE_REBOOT;
    ~UTComputer() { save(); }
};

#endif // UTCOMPUTER_H
