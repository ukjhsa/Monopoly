#include <QApplication>
#include <QDesktopWidget>
#include <QMessageBox>
#include <QString>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include "UI/GameStart.h"
#include "UI/GameRoom.h"
#include "UI/GameScene.h"
#include "UI/GameEnd.h"
#include "Monopoly/MapProperty.h"
#include "Monopoly/Map.h"
#include "Monopoly/WorldMap.h"
#include "Monopoly/Player.h"
#include "Monopoly/WorldPlayer.h"
#include "Monopoly/UpgradableMap.h"
#include "Monopoly/CollectableMap.h"
#include "Monopoly/RandomCostMap.h"
#include "Monopoly/PrisonMap.h"
#include "Widget.h"

using namespace std;
using namespace Monopoly;

Widget::Widget(QObject *parent)
    : QObject(parent), currentPlayerNumber(0)
{
    startGameStart();
}

Widget::~Widget()
{
    clearGameData();
    // Mainly delete Map* in data.

    // QWidget objects will automatically delete when called QWidget destructor,
    // so GameStart/GameRoom/GameScene/GameEnd don't delete QWidget objects by myself.
    // ps: QLabel, QPushButton, etc., all of them are inherits QWidget.
    // QWidget has destroy() function, it called from the QWidget destructor,
    // and then destroy() calls itself recursively for all the child widgets.
    // That's why they don't delete them such as QLabel, QPushButton by myself.
    // And another issue about delete GameStart/GameRoom/GameScene/GameEnd,
    // this action also do not do by myself because they have specified by "Qt::WA_DeleteOnClose".
    // It means when calling close() function (QWidget provided), the object will also deleted.
    // Therfore it just be careful for deleting worldMap.
}

void Widget::clearGameData()
{
    worldMap.clear();
    worldPlayer.clear();
}

void Widget::startGameStart()
{
    // Maybe called by GameEnd, so must clear first.
    clearGameData();
    // Start GameStart.
    gameStart = new GameStart();
    setWindowAlignCenter(gameStart,
                         QApplication::desktop()->availableGeometry());
    connect(gameStart, SIGNAL(startGameRoom()), this, SLOT(startGameRoom()));
    gameStart->show();
}

void Widget::setWindowAlignCenter(QWidget *child, const QRect &size)
{
    QRect childSize = child->frameGeometry();
    child->setGeometry((size.width() - childSize.width())/2,
                       (size.height() - childSize.height())/2,
                       childSize.width(),
                       childSize.height());
}

void Widget::startGameRoom()
{
    gameRoom = new GameRoom();
    setWindowAlignCenter(gameRoom,
                         QApplication::desktop()->availableGeometry());
    connect(gameRoom, SIGNAL(createPlayer(unsigned, const char *)),
            this, SLOT(createPlayer(unsigned, const char *)));
    connect(gameRoom, SIGNAL(loadMap(const char*)),
            this, SLOT(loadMap(const char*)));
    connect(gameRoom, SIGNAL(startGameScene()),
            this, SLOT(startGameScene()));
    gameRoom->show();
}

void Widget::createPlayer(unsigned id, const char *name)
{
    worldPlayer.addPlayer(Player(id, name));
}

void Widget::loadMap(const char *fileName)
{
    ifstream ifs(fileName);
    if (ifs.is_open()) {
        size_t location = 0;
        do {
            string str;
            getline(ifs, str);
            stringstream ss(str);
            char type = '\0';
            ss >> type;
            switch (type) {
            case WorldMap::UPGRADE:
                readUpgradableMap(ss, location);
                break;
            case WorldMap::COLLECT:
                readCollectableMap(ss, location);
                break;
            case WorldMap::RANDOM:
                readRandomCostMap(ss, location);
                break;
            case WorldMap::JAIL:
                readPrisonMap(ss, location);
                break;
            default :
                // If it is format error, rather than file error flag.
                if (ifs.good()) {
                    QMessageBox box(QMessageBox::Warning, "Warning",
                                    "The format of map file has error!!",
                                    QMessageBox::Ok, 0);
                    box.exec();
                }
                break;
            }
            ++location;
        } while (ifs.good());
    }
}

void Widget::readUpgradableMap(istream &is, size_t location)
{
    string name;
    is >> name;
    int purchasePrice = 0, upgradePrice = 0;
    is >> purchasePrice;
    is >> upgradePrice;
    vector<int> fine;
    while (is.good()) {
        int number = 0;
        is >> number;
        fine.push_back(number);
    }
    worldMap.addMap(new UpgradableMap(name, location, purchasePrice, upgradePrice, fine));
}

void Widget::readCollectableMap(istream &is, size_t location)
{
    string name;
    is >> name;
    int purchasePrice = 0, fine = 0;
    is >> purchasePrice;
    is >> fine;
    worldMap.addMap(new CollectableMap(name, location, purchasePrice, fine));
}

void Widget::readRandomCostMap(istream &is, size_t location)
{
    string name;
    is >> name;
    int purchasePrice = 0, fine = 0;
    is >> purchasePrice;
    is >> fine;
    worldMap.addMap(new RandomCostMap(name, location, purchasePrice, fine));
}

void Widget::readPrisonMap(istream &is, size_t location)
{
    string name;
    is >> name;
    worldMap.addMap(new PrisonMap(name, location));
}

void Widget::startGameScene()
{
    // Initialize worldPlayer on worldMap[0].
    for (size_t i = 0; i < worldPlayer.size(); ++i) {
        worldMap[0]->arrivalAction(worldPlayer[i]);
    }
    // New GameScene.
    gameScene = new GameScene(0, worldMap.size(), worldPlayer.size());
    this->setWindowAlignCenter(gameScene,
                               QApplication::desktop()->availableGeometry());
    connect(gameScene, SIGNAL(playerDice(int)),
            this, SLOT(playerDice(int)));
    connect(gameScene, SIGNAL(newRound()),
            this, SLOT(newRound()));
    connect(gameScene, SIGNAL(playerDoAction(const std::string &)),
            this, SLOT(playerDoAction(const std::string &)));
    connect(gameScene, SIGNAL(displayAllMapProperty(int)),
            this, SLOT(displayAllMapProperty(int)));
    connect(this, SIGNAL(passAllMapProperty(int, std::vector<std::string>)),
            gameScene, SIGNAL(passAllMapProperty(int, std::vector<std::string>)));

    // Initialize GameScene.
    gameScene->changeGameSceneStatus("\n", currentPlayerNumber, worldMap, worldPlayer);
    gameScene->show();
}

void Widget::playerDice(int diceNumber)
{
    playerMove(diceNumber);
    // Change GameScene.
    gameScene->changeGameSceneStatus(
                worldPlayer[currentPlayerNumber].getDoWhatAction().c_str(),
                currentPlayerNumber, worldMap, worldPlayer);
    playerDoSomeoneAction();
}

void Widget::playerMove(int diceNumber)
{
    // Player leave the original map.
    worldMap[worldPlayer[currentPlayerNumber].getLocation()]->leavingAction(
                worldPlayer[currentPlayerNumber]);
    // Player move.
    worldPlayer[currentPlayerNumber].move(diceNumber, worldMap.size());
    // Player arrive the new map.
    worldMap[worldPlayer[currentPlayerNumber].getLocation()]->arrivalAction(
                worldPlayer[currentPlayerNumber]);
}

void Widget::playerDoSomeoneAction()
{
    // Get actions which is according to player's location map and player's status.
    vector<std::string> actionList =
        worldMap[worldPlayer[currentPlayerNumber].getLocation()]->getMapAction(
                worldPlayer[currentPlayerNumber]);
    // If PAY/STOP/MOVE action, there are no listAction on UI.
    if (isActionDontList(actionList, Monopoly::MapProperty::PAY) ||
        isActionDontList(actionList, Monopoly::MapProperty::STOP) ||
        isActionDontList(actionList, Monopoly::MapProperty::MOVE)) {
        // There is one action.
        gameScene->playerChooseAction(actionList[0]);
    }
    else {
        // List all action that player can doing.
        gameScene->listPlayerAction(
                worldMap[worldPlayer[currentPlayerNumber].getLocation()],
                worldPlayer[currentPlayerNumber],
                actionList);
    }
}

bool Widget::isActionDontList(const vector<std::string> &actionList,
                              const std::string &action) const
{
    vector<std::string>::const_iterator it = find(actionList.begin(),
                                                  actionList.end(),
                                                  action);
    return it != actionList.end();
}

void Widget::playerDoAction(const string &action)
{
    // Do action.
    worldMap[worldPlayer[currentPlayerNumber].getLocation()]->doAction(
            worldPlayer[currentPlayerNumber], worldPlayer, action);
    // Change GameScene.
    gameScene->changeGameSceneStatus(
                worldPlayer[currentPlayerNumber].getDoWhatAction().c_str(),
                currentPlayerNumber, worldMap, worldPlayer);
    // If there has player is bankrupted but is still in game, set it out of game.
    setPlayerOutOfGame();

    if (isGameOver()) {
        // Close GameScene when game over.
        gameScene->close();
        // Call GameEnd.
        gameEnd = new GameEnd();
        setWindowAlignCenter(gameEnd,
                             QApplication::desktop()->availableGeometry());
        connect(gameEnd, SIGNAL(startGameStart()), this, SLOT(startGameStart()));
        gameEnd->setWinnerInfo(worldPlayer[getWinnerPlayerId()]);
        gameEnd->show();
    }
    else {
        nextRound();
    }
}

void Widget::setPlayerOutOfGame()
{
    for (auto itPlayer = worldPlayer.getAllPlayers().begin();
         itPlayer != worldPlayer.getAllPlayers().end(); ++itPlayer) {
        // If player is bankrupted but player is still in game.
        if ((*itPlayer).isBankrupted() && ! (*itPlayer).isPlayerOutOfGame()) {
            // Set out of game.
            (*itPlayer).setPlayerOutOfGame();
            gameScene->changeGameSceneStatus(
                    worldPlayer[currentPlayerNumber].getDoWhatAction().c_str(),
                    currentPlayerNumber, worldMap, worldPlayer);
            // Free all map which host is this player.
            for (size_t i = 0; i < worldMap.size(); ++i) {
                worldMap[i]->doAction((*itPlayer), worldPlayer, MapProperty::FREE);
            }
        }
    }
}

bool Widget::isGameOver() const
{
    int counter = 0;
    for (auto itPlayer = worldPlayer.getAllPlayers().begin();
         itPlayer != worldPlayer.getAllPlayers().end(); ++itPlayer) {
        // Compute in game player number.
        if ( ! (*itPlayer).isPlayerOutOfGame()) {
            ++counter;
        }
    }
    return counter <= 1;
}

void Widget::nextRound()
{
    // Change player.
    do {
        currentPlayerNumber = (currentPlayerNumber + 1) % worldPlayer.size();
    } while (worldPlayer[currentPlayerNumber].isPlayerOutOfGame());
}

void Widget::newRound()
{
    gameScene->changeGameSceneStatus("----------", currentPlayerNumber,
                                     worldMap, worldPlayer);
    // If player can not move.
    if ( ! worldPlayer[currentPlayerNumber].isPlayerMovable()) {
        playerDoSomeoneAction();
    }
    else {
        // Waitting for player dice.
    }
}

void Widget::displayAllMapProperty(int mapLocation) const
{
    vector<string> actionList = worldMap[mapLocation]->getAllMapProperty();
    passAllMapProperty(mapLocation, actionList);
}

int Widget::getWinnerPlayerId() const
{
    for (auto itPlayer = worldPlayer.getAllPlayers().begin();
         itPlayer != worldPlayer.getAllPlayers().end(); ++itPlayer) {
        if ( ! (*itPlayer).isPlayerOutOfGame()) {
            return (*itPlayer).getId();
        }
    }
    return -1;
}
