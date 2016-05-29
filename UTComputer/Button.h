#ifndef BUTTON_H
#define BUTTON_H


#include <QToolButton>
#include <QPushButton>

class Button : public QToolButton
{
    Q_OBJECT

public:
    explicit Button(const QString &text, QWidget *parent = 0);
    QSize sizeHint() const Q_DECL_OVERRIDE;
};

class ButtonIdentifier : public QPushButton
{
    Q_OBJECT
    std::string keyIdentifier;
public :
    explicit ButtonIdentifier(const QString &text, std::string key) : QPushButton(text), keyIdentifier(key) {}
    std::string getKeyIdentifier() const { return keyIdentifier; }
};

#endif // BUTTON_H
