#ifndef ACTIONBUTTON_H
#define ACTIONBUTTON_H

#include <QPushButton>

class ActionButton : public QPushButton
{
    Q_OBJECT
public:
    ActionButton(QWidget *parent = 0);
signals:
    // Pass signal to GameScene to choose action.
    void chooseAction(const std::string &);
private slots:
    // Player choosed myself action called by clicked self.
    void clickAction();
};

#endif // ACTIONBUTTON_H
