#ifndef BUTTON_H
#define BUTTON_H


#include <QToolButton>
#include <QPushButton>

/**
 * @brief La Button est un QToolButton ayant une taille spécifique.
 */
class Button : public QToolButton
{
    Q_OBJECT

public:
    /**
     * @brief Constructeur publique de la classe Button
     * @param text Chaine de caractère représentant le texte du bouton.
     * @param parent Pointeur vers le widget parent du bouton.
     */
    explicit Button(const QString &text, QWidget *parent = 0);
    QSize sizeHint() const Q_DECL_OVERRIDE;
};

/**
 * @brief La classe ButtonIdentifier est un bouton contenant un identifier.
 */
class ButtonIdentifier : public QPushButton
{
    Q_OBJECT
    std::string keyIdentifier;
public :
    /**
     * @brief Constructeur publique de ButtonIdentifier.
     * @param text Chaine de caractère représentant le texte du bouton.
     * @param key Chaine de caractère représentant la clé de l'identifieur associé au bouton.
     */
    explicit ButtonIdentifier(const QString &text, std::string key) : QPushButton(text), keyIdentifier(key) {}
    /**
     * @brief Accesseur à la clé de l'identifieur.
     * @return Une chaine de caractère représentant la clé.
     */
    std::string getKeyIdentifier() const { return keyIdentifier; }
};

#endif // BUTTON_H
