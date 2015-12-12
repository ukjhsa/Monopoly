#include <QString>
#include "ActionButton.h"

ActionButton::ActionButton(QWidget *parent) : QPushButton(parent)
{
    connect(this, SIGNAL(clicked()), this, SLOT(clickAction()));
}

void ActionButton::clickAction()
{
    // Pass action to GameScene's slot.
    chooseAction(this->text().toLocal8Bit().constData());
}
