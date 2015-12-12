#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QFont>
#include "GameStart.h"

GameStart::GameStart(QWidget *parent) :
    QWidget(parent)
{
    init();
}

void GameStart::init()
{
    this->resize(300, 300);
    // Delete when closed.
    this->setAttribute(Qt::WA_DeleteOnClose);

    title = new QLabel("Welcome to simple Monopoly", this);
    title->setFont(QFont("default", 15, QFont::DemiBold));
    title->resize(250, 50);
    title->setGeometry((this->width() - title->width())/2, 25,
                       title->width(), title->height());
    title->setAlignment(Qt::AlignCenter);

    newGame = new QPushButton("New game", this);
    newGame->setFont(QFont("default", 15, QFont::DemiBold));
    newGame->resize(150, 50);
    newGame->setGeometry((this->width()-newGame->width())/2, 100,
                         newGame->width(), newGame->height());
    // When newGame be clicked, close this and start GuestRoom.
    connect(newGame, SIGNAL(clicked()), this, SLOT(startGame()));

    exitGame = new QPushButton("Exit game", this);
    exitGame->setFont(QFont("default", 15, QFont::DemiBold));
    exitGame->resize(150, 50);
    exitGame->setGeometry((this->width()-exitGame->width())/2, 200,
                          exitGame->width(), exitGame->height());
    connect(exitGame, SIGNAL(clicked()), this, SLOT(close()));
}

void GameStart::startGame()
{
    // Close self.
    this->close();
    // Start GuestRoom by pass signal to Widget's slot.
    startGameRoom();
}
