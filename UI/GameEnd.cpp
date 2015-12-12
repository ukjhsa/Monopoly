#include <QLabel>
#include <QFont>
#include <QPushButton>
#include <QString>
#include "../Monopoly/Player.h"
#include "GameEnd.h"

GameEnd::GameEnd(QWidget *parent) :
    QWidget(parent)
{
    init();
}

void GameEnd::init()
{
    this->resize(500, 500);
    // Quit when closed.
    this->setAttribute(Qt::WA_DeleteOnClose);

    winInfo = new QLabel(this);
    winInfo->setFont(QFont("default", 20, QFont::DemiBold));
    winInfo->setGeometry(0, 0, this->width(), 300);
    winInfo->setAlignment(Qt::AlignCenter);

    returnGame = new QPushButton("Return GameStart", this);
    returnGame->setFont(QFont("default", 15, QFont::DemiBold));
    returnGame->setGeometry(25, 350, 200, 50);
    connect(returnGame, SIGNAL(clicked()), this, SLOT(returnGameStart()));

    exitGame = new QPushButton("Exit Game", this);
    exitGame->setFont(QFont("default", 15, QFont::DemiBold));
    exitGame->setGeometry(returnGame->x() + returnGame->width() + 50,
                          returnGame->y(),
                          200, 50);
    connect(exitGame, SIGNAL(clicked()), this, SLOT(close()));
}

void GameEnd::returnGameStart()
{
    this->close();
    // Start GameStart by calling Widget's slot.
    startGameStart();
}

void GameEnd::setWinnerInfo(const Monopoly::Player &player)
{
    winInfo->setText(
        "<< The winner is: " + QString::fromLocal8Bit(player.getName().c_str()) + " >>\n" +
        "Player " + QString::fromLocal8Bit(player.getName().c_str()) + " finally obtained $" +
        QString::number(player.getMoney()) + ",\n and " +
        QString::fromLocal8Bit(player.getName().c_str()) + " has " +
        QString::number(player.getNumberOfOwnMap()) + " maps!!\n\n" +
        "Let's congratulate player " + QString::fromLocal8Bit(player.getName().c_str()) + " !!!");
}
