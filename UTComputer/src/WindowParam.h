#ifndef WINDOWPARAM_H
#define WINDOWPARAM_H

#include <QWindow>
#include <QWidget>
#include <QTableWidget>
#include <QLabel>
#include <QTextEdit>

class WindowParam;

/**
 * @brief La classe ParamTab est l'onglet réservé au paramétre du calculateur.
 */
class ParamTab : public QWidget
{
    Q_OBJECT
public:
    /**
     * @brief Constructeur public de ParamTab.
     * @param parent QWidget parent de l'objet.
     */
    explicit ParamTab(QWidget* parent = 0);
};

/**
 * @brief La classe VariableTab est l'onglet réservé à la gestion des variables du calculateur.
 */
class VariableTab : public QWidget
{
    Q_OBJECT
    /**
     * @brief Tableau affichant les variables.
     */
    QTableWidget *viewVariable;
    /**
     * @brief Widget parent de l'objet.
     */
    WindowParam* parent;
public slots:
    /**
     * @brief Slot supprimant un identifieur selon la clé contenus dans le ButtonIdentifier appelant.
     */
    void deleteIdentifier();

public:
    /**
     * @brief Constructeur public de la classe VariableTab
     * @param parent Widget parent de l'objet.
     */
    explicit VariableTab(WindowParam* parent = 0);
    /**
     * @brief Met à jour le tableau affichant les variables.
     */
    void refresh();
};

/**
 * @brief La classe ProgramTab est l'onglet réservé à la gestion des programmes du calculateur.
 */
class ProgramTab : public QWidget
{
    Q_OBJECT
    /**
     * @brief Tableau affichant les programmes.
     */
    QTableWidget *viewProgram;
    /**
     * @brief Widget parent de l'objet.
     */
    WindowParam* parent;
public slots:
    /**
     * @brief Slot supprimant un identifieur selon la clé contenus dans le ButtonIdentifier appelant.
     */
    void deleteIdentifier();
public:
    /**
     * @brief Constructeur public de la classe VariableTab
     * @param parent Widget parent de l'objet.
     */
    explicit ProgramTab(WindowParam* parent = 0);
    /**
     * @brief Met à jour le tableau affichant les programmes.
     */
    void refresh();
};

/**
 * @brief La classe WindowParam est la fenétre de gestion des options, variables et programmes.
 */
class WindowParam : public QWidget
{
    Q_OBJECT
    /**
     * @brief Onglet de gestion des paramétres.
     */
    ParamTab *paramTab;
    /**
     * @brief Onglet de gestion des variables.
     */
    VariableTab *variableTab;
    /**
     * @brief Onglet de gestion des programmes.
     */
    ProgramTab *programTab;
public slots:
    /**
     * @brief Slot ouvrant la fenétre d'ajout d'un identifieur.
     */
    void addIdentifier();
    /**
     * @brief Slot ouvrant la fenétre de modification d'un identifieur.
     */
    void editIdentifier();
    /**
     * @brief Slot mettant à jour le tableau de variables.
     */
    void refreshVariable();
    /**
     * @brief Slot mettant à jour le tableau de programmes.
     */
    void refreshProgram();
public:
    /**
     * @brief Constructeur public de la classe WindowParam.
     * @param parent Widget parent de l'objet.
     */
    explicit WindowParam(QWidget* parent = 0);
};

/**
 * @brief La classe WindowAddIdentifier est la fenétre d'ajout d'un identifieur.
 */
class WindowAddIdentifier : public QWidget {
    Q_OBJECT
    /**
     * @brief Ligne d'édition de la clé de l'identifieur.
     */
    QLineEdit* keyLineEdit;
    /**
     * @brief Ligne d'édition de la valeur de l'identifieur.
     */
    QTextEdit* valueTextEdit;
    /**
     * @brief Text affichant un message d'erreur à destination de l'utilisateur.
     */
    QLabel* messageError;
public slots:
    /**
     * @brief Slot créant le nouvel identifieur.
     */
    void save();
signals:
    /**
     * @brief Signal prevenant que les tableaux d'identifieurs ont besoin d'être mis à jour.
     */
    void needRefresh();
public :
    /**
     * @brief Constructeur public de la classe WindowAddIdentifier.
     * @param parent Widget parent de l'objet.
     */
    explicit WindowAddIdentifier(WindowParam* parent = 0);
};

class WindowEditIdentifier : public QWidget {
    Q_OBJECT
    /**
     * @brief Chaine de caractère représentant la clé de l'identifieur.
     */
    std::string key;
    /**
     * @brief Ligne d'édition de la valeur de l'identifieur.
     */
    QTextEdit* valueTextEdit;
    /**
     * @brief Text affichant un message d'erreur à destination de l'utilisateur.
     */
    QLabel* messageError;
public slots:
    /**
     * @brief Slot mettant à jour le nouvel identifieur.
     */
    void save();
signals:
    /**
     * @brief Signal prevenant que les tableaux d'identifieurs ont besoin d'être mis à jour.
     */
    void needRefresh();
public :
    /**
     * @brief Constructeur public de la classe WindowEditIdentifier.
     * @param parent Widget parent de l'objet.
     */
    explicit WindowEditIdentifier(std::string key ,WindowParam* parent = 0);
};


#endif // WINDOWPARAM_H
