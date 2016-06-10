#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QWidget>
#include <QLineEdit>
#include <QTextEdit>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QHeaderView>
#include <QDebug>
#include <QEvent>
#include <QObject>
#include <QKeyEvent>

class UTException;
class Button;
class Settings;
class MainFrame;
class Manager;
class UTComputer;

class Calculator : public QWidget
{
private:
    Q_OBJECT
    /**
     * @brief Element contenant le message d'erreur à destination de l'utilisateur.
     */
    QTextEdit* message;
    /**
     * @brief Element contenant la pile du calculateur.
     */
    QTableWidget* viewPile;
    /**
     * @brief Element contenant la ligne de commande entrée par l'utilisateur.
     * @details On ne peut naviguer dans la ligne de commande qu'avec les fleches du clavier.
     * Les fléches haut et bas permettent de naviguer dans l'historique des commandes dèja entrées.
     * La saisi d'un opérateur symbolique ou de la touche entrée provoque l'évaluation de la ligne.
     */
    QLineEdit* command;
    /**
     * @brief Element contenant le clavier cliquable piuvant étre utiliser par l'utilisateur pour compléter la ligne de commande.
     */
    MainFrame* keyBoard;
    /**
     * @brief Chaine de charactére contenant les details du message d'erreur à l'intention de l'utilisateur.
     */
    std::string messageDetail;
    /**
     * @brief Vecteur de chaine de caractères contenant l'historique des commandes évaluées par le calculateur.
     */
    std::vector<QString> commands;
    /**
     * @brief Position dans le vecteur commands représentant la commande affichée actuellement dans la ligne de commande.
     */
    int commands_pos;
    /**
     * @brief Element contenant le parent UTComputer de l'instance de Calculator.
     */
    UTComputer* parentComputer;

    /**
     * @brief Affichage le résumé de l'erreur dans la ligne de message d'erreur et mise a jour des details de l'erreur pour affichage dans la fenétre de details.
     * @param e UTCException dont on veut afficher le résumé.
     */
    void setMessage(const UTException& e);
    /**
     * @brief Vide la ligne de message d'erreur.
     */
    void deleteMessage();
    /**
     * @brief Seems like you're taking a look at something hidden...
     * @param s Some magic word
     * @return kappa
     */
    bool damnBoyWhatIsThisMysteriousFunction(const std::string& s);
protected:
    /**
     * @brief Filtre les évenements de la ligne de commande.
     * @details Gére l'utilisation des fléches haut et bas pour naviguer dans l'historique des commandes.
     * Empéche l'utilisation des fléches droite et gauche. Déclenche le calcul à l'utilisation d'un opérateur
     * arithmétique en dehors d'une expression ou d'un programme. Déclenche le calcul quand l'utilisateur appuie sur entré.
     * @param obj Element sur lequel l'évenement s'applique.
     * @param event Evenement ayant déclenché la focntion.
     * @return Boolean true si l'évenement a été filtré, false sinon.
     */
    bool eventFilter (QObject *obj, QEvent *event) override;
public:
    /**
     * @brief Constructeur de Calculator.
     * @Details Initialise les éléments graphiques de la fenétre.
     * @param parent UTComputer parent du Calculator.
     */
    explicit Calculator(UTComputer *parent = 0);

    /**
     * @brief Accesseur pour commands.
     * @return Un vecteur de string contenant l'historique des commandes.
     */
    std::vector<QString> getCommands() const { return commands; }

    /**
     * @brief Ajoute une commande dans le vecteur commands contenant l'historique des commandes.
     * @param value Chaine de caractère représentant la commande à enregistrer.
     */
    void addCommand (QString& value) { commands.push_back(value);}

    /**
     * @brief Formate une chaine de caractère pour qu'elle s'affiche correctement dans l'élement graphique de la pile.
     * @details La fonction coupe la chaine de caractère pour correspondre à la longueur de la pile et ajoute ".." à la fin.
     * S'il la chaine commence par '"' ou pas '[', la fonction referme le caractère à la fin après les "...".
     * @param value Chaine de caractère à formatter.
     * @return La chaine de caractère formatée.
     */
    QString formatLiteralString(QString value);

public slots:
    /**
     * @brief Slot mettant à jour l'affichage de la pile, en actualisant selon la pile contenue dans le Manager.
     */
    void refreshPile();
    /**
     * @brief Slot appelé lors de l'utilisation d'un chiffre du clavier clickable, ajoute ce chiffre à la ligne de commande.
     */
    void addDigitToCommand();
    /**
     * @brief Slot appelé lors de l'utilisation de la touche espace du clavier clickable, ajoute un espace à la ligne de commande.
     */
    void addSpaceToCommand();
    /**
     * @brief Slot appelé lors de l'utilisation d'un operateur du clavier clickable, ajoute cet opérateur à la ligne de commande et déclenche le calcul de celle-ci.
     */
    void addOperatorToCommand();
    /**
     * @brief Slot appelé lors de l'utilisation du backspace du clavier clickable, enléve le dernier caractère de la ligne de commande.
     */
    void backspaceToCommand();
    /**
     * @brief Slot lançant l'évaluation de la ligne de commande en utilisant la classe Manager.
     */
    void calculate();
    /**
     * @brief Slot appelé lorsque l'option du nombre de ligne de la pile affichée change, enregistre cette valeur dans le Manager.
     * @param newValue Entier représentant le nombre de ligne de la pile à afficher.
     */
    void nbLineDisplayPileChanged(int newValue);
    /**
     * @brief Slot appelé lorsque l'option de l'affichage du clavier clickable change, enregistre cette valeur dans le Manager.
     * @param newValue Entier représentant la valeur de l'option.
     */
    void displayKeyboardChanged(int newValue);
    /**
     * @brief Slot appelé lorsque l'option concernant l'utilisation d'un son avertissant l'utilisateur d'une erreur change, enregistre cette valeur dans le Manager.
     * @param newValue Entier représentant la valeur de l'option.
     */
    void beepMessageChanged(int newValue);
    /**
     * @brief Fonction ouvrant une fenétre contenant les details de l'erreur à destination de l'utilisateur.
     */
    void openDetailErrorWindow();
    /**
     * @brief Fonction ouvrant une fenétre contenant les boutons des opérateurs.
     */
    void openMoreOperatorsWindow();

};

#endif // CALCULATOR_H
