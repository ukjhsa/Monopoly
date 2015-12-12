#include <QPushButton>
#include <QLabel>
#include <QFont>
#include <QTextEdit>
#include <QString>
#include <vector>
#include <cstdlib>
#include <time.h>
#include <string>
#include "../Monopoly/Map.h"
#include "../Monopoly/Player.h"
#include "../Monopoly/WorldMap.h"
#include "../Monopoly/WorldPlayer.h"
#include "../Monopoly/GameConstant.h"
#include "ActionButton.h"
#include "GameScene.h"

using namespace std;

GameScene::GameScene(QWidget *parent, size_t mapSize, size_t playerSize)
    : QWidget(parent), playerId(playerSize), playerName(playerSize),
    playerMoney(playerSize), playerOwnMap(playerSize)
{
    init();
    initScene(mapSize, playerSize);
    initPlayerInfo(playerSize);
    initMenu();
    initAction();
    initImmediateInfo();
}

void GameScene::init()
{
    this->resize(900, 600);
    // Delete when closed.
    this->setAttribute(Qt::WA_DeleteOnClose);
}

void GameScene::initScene(size_t mapSize, size_t playerSize)
{
    scene = new Scene(this, 672, 400, mapSize, playerSize);
    scene->setGeometry(0, 0, scene->width(), scene->height());
    connect(scene, SIGNAL(displayAllMapProperty(int)),
            this, SIGNAL(displayAllMapProperty(int)));
    connect(this, SIGNAL(passAllMapProperty(int, std::vector<std::string>)),
            scene, SIGNAL(passAllMapProperty(int, std::vector<std::string>)));
}

void GameScene::initPlayerInfo(size_t playerSize)
{
    playerInfo = new QLabel(this);
    playerInfo->setGeometry(0, scene->height(), scene->width(),
                            this->height()-scene->height());

    for (size_t i = 0; i < playerSize; ++i) {
        playerId[i] = new QLabel("Player " + QString::number(i+1) + ":", playerInfo);
        playerId[i]->setFont(QFont("default", 15, QFont::DemiBold));
        playerId[i]->setGeometry(i * playerInfo->width()/playerSize, 0,
                                 playerInfo->width()/playerSize, 50);
        playerId[i]->setAlignment(Qt::AlignCenter);
        playerName[i] = new QLabel(playerInfo);
        playerName[i]->setFont(QFont("default", 15, QFont::DemiBold));
        playerName[i]->setGeometry(i * playerInfo->width()/playerSize,
                                   playerId[i]->y()+playerId[i]->height(),
                                   playerId[i]->width(),
                                   playerId[i]->height());
        playerName[i]->setAlignment(Qt::AlignCenter);
        playerMoney[i] = new QLabel(playerInfo);
        playerMoney[i]->setFont(QFont("default", 15, QFont::DemiBold));
        playerMoney[i]->setGeometry(i * playerInfo->width()/playerSize,
                                    playerName[i]->y()+playerName[i]->height(),
                                    playerId[i]->width(),
                                    playerId[i]->height());
        playerMoney[i]->setAlignment(Qt::AlignCenter);
        playerOwnMap[i] = new QLabel(playerInfo);
        playerOwnMap[i]->setFont(QFont("default", 15, QFont::DemiBold));
        playerOwnMap[i]->setGeometry(i * playerInfo->width()/playerSize,
                                     playerMoney[i]->y()+playerMoney[i]->height(),
                                     playerId[i]->width(),
                                     playerId[i]->height());
        playerOwnMap[i]->setAlignment(Qt::AlignCenter);
    }
}

void GameScene::initMenu()
{
    menuInfo = new QLabel(this);
    menuInfo->setGeometry(scene->width(), 0, this->width()-scene->width(), 100);

    exitButton = new QPushButton("Exit Game", menuInfo);
    exitButton->setFont(QFont("default", 15, QFont::DemiBold));
    exitButton->resize(150, 50);
    exitButton->setGeometry((menuInfo->width()-exitButton->width())/2, 25,
                            exitButton->width(), exitButton->height());
    connect(exitButton, SIGNAL(clicked()), this, SLOT(close()));
}

void GameScene::initAction()
{
    actionInfo = new QLabel(this);
    actionInfo->setGeometry(scene->width(), menuInfo->height(),
                            this->width()-scene->width(), 300);

    diceButton = new QPushButton("Dice", actionInfo);
    diceButton->setFont(QFont("default", 15, QFont::DemiBold));
    diceButton->resize(180, 50);
    diceButton->setGeometry((actionInfo->width()-diceButton->width())/2, 0,
                            diceButton->width(), diceButton->height());
    connect(diceButton, SIGNAL(clicked()), this, SLOT(doDice()));

    nextTurnButton = new QPushButton("Next round", actionInfo);
    nextTurnButton->setFont(QFont("default", 15, QFont::DemiBold));
    nextTurnButton->resize(180, 50);
    nextTurnButton->setGeometry((actionInfo->width()-nextTurnButton->width())/2,
                                diceButton->height(),
                                nextTurnButton->width(),
                                nextTurnButton->height());
    nextTurnButton->setEnabled(false);
    connect(nextTurnButton, SIGNAL(clicked()), this, SLOT(doNextRound()));
}

void GameScene::initImmediateInfo()
{
    immediateInfo = new QTextEdit("Hint:\nYou can click map to get all map property.\n", this);
    immediateInfo->setFont(QFont("default", 12, QFont::DemiBold));
    immediateInfo->setGeometry(scene->width(),
                               actionInfo->y()+actionInfo->height(),
                               this->width()-scene->width(),
                               200);
    immediateInfo->setAlignment(Qt::AlignCenter);
    immediateInfo->setReadOnly(true);
    // Set max limit for blocks in the document.
    immediateInfo->document()->setMaximumBlockCount(100);
}

void GameScene::changeGameSceneStatus(
        const string &str, int currentPlayerId,
        const Monopoly::WorldMap &worldMap, const Monopoly::WorldPlayer &worldPlayer)
{
    this->changeImmediateInfo(str);
    scene->changeMapStatus(currentPlayerId, worldMap);
    this->changePlayerStatus(currentPlayerId, worldPlayer);
}

void GameScene::changeImmediateInfo(const string &str)
{
    immediateInfo->append(QString::fromLocal8Bit(str.c_str()));
    QTextCursor cursor =  immediateInfo->textCursor();
    cursor.movePosition(QTextCursor::End);
    immediateInfo->setTextCursor(cursor);
}

void GameScene::changePlayerStatus(size_t currentPlayerId,
                                   const Monopoly::WorldPlayer &worldPlayer)
{
    for (size_t i = 0; i < worldPlayer.size(); ++i) {
        playerName[i]->setText(QString::fromLocal8Bit(worldPlayer[i].getName().c_str()));
        playerMoney[i]->setText("$: " + QString::number(worldPlayer[i].getMoney()));
        playerOwnMap[i]->setText("#(map): " + QString::number(worldPlayer[i].getNumberOfOwnMap()));
        if (i == currentPlayerId) {
            playerName[i]->setStyleSheet("QLabel {color: red}");
        }
        else {
            playerName[i]->setStyleSheet("QLabel { none }");
        }
    }
}

void GameScene::doDice()
{
    // Disable dice button.
    diceButton->setEnabled(false);

    srand(time(NULL));
    int diceNumber = rand() % Monopoly::GameConstant::DICE_SIZE + 1;
    // Pass dice number to Widget's slot.
    playerDice(diceNumber);
}

void GameScene::doNextRound()
{
    // Enable dice button.
    diceButton->setEnabled(true);
    // Disable next turn button.
    nextTurnButton->setEnabled(false);
    // Pass signal to Widget to the new round.
    newRound();
}

void GameScene::listPlayerAction(const Monopoly::Map *map,
                                 const Monopoly::Player &player,
                                 const vector<std::string> &actionList)
{
    // Generate actions.
    actionButton.resize(actionList.size());
    for (size_t i = 0; i < actionList.size(); ++i) {
        actionButton[i] = new ActionButton(actionInfo);
        actionButton[i]->setText(actionList[i].c_str());
        actionButton[i]->setFont(QFont("default", 15, QFont::DemiBold));
        actionButton[i]->resize(180, 50);
        actionButton[i]->setGeometry(
                (actionInfo->width()-diceButton->width())/2, 150+50*i,
                actionButton[i]->width(), actionButton[i]->height());
        // Delete when closed.
        actionButton[i]->setAttribute(Qt::WA_DeleteOnClose);
        actionButton[i]->show();
        connect(actionButton[i], SIGNAL(chooseAction(const std::string &)),
                this, SLOT(playerChooseAction(const std::string &)));
        // Check action. If player has no enough money, player then can't buy the map.
        if ( ! map->isActionActive(player, actionList[i])) {
            actionButton[i]->setText("Can't to " + actionButton[i]->text());
            actionButton[i]->setEnabled(false);
        }
    }
}

void GameScene::playerChooseAction(const string &action)
{
    // Delete all action button.
    for (size_t i = 0; i < actionButton.size(); ++i) {
        actionButton[i]->close();
    }
    // Clear all action.
    actionButton.clear();
    // Disable dice button.
    diceButton->setEnabled(false);
    // Enable go next turn button.
    nextTurnButton->setEnabled(true);
    // Pass action to Widget's slot.
    playerDoAction(action);
}
