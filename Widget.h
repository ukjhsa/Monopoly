#ifndef WIDGET_H
#define WIDGET_H

#include <QObject>
#include "UI/GameStart.h"
#include "UI/GameRoom.h"
#include "UI/GameScene.h"
#include "UI/GameEnd.h"
#include "Monopoly/WorldPlayer.h"
#include "Monopoly/WorldMap.h"

namespace Monopoly {
    class Player;
}

class Widget : public QObject
{
    Q_OBJECT

public:
    Widget(QObject *parent = 0);
    ~Widget();

signals:
    // Pass all map property to BasicSceneBlock in GameScene.
    void passAllMapProperty(int, const std::vector<std::string> &) const;

private slots:
    // Start GameStart called by self-constructor or GameEnd.
    void startGameStart();
    // Start GameRoom called by GameStart.
    void startGameRoom();
    // Add players passed by GameRoom.
    void createPlayer(unsigned id, const char *name);
    // Load map file passed by GameRoom.
    void loadMap(const char *fileName);
    // Start GameScene called by GameRoom.
    void startGameScene();
    // Player dice passed by GameScene.
    void playerDice(int);
    // To the new round called by GameScene.
    void newRound();
    // Player do action called by GameScene.
    void playerDoAction(const std::string &);
    // Get signal from BasicSceneBlock to get all map property in GameScene.
    void displayAllMapProperty(int) const;

private:
    // UI.
    GameStart *gameStart;
    GameRoom *gameRoom;
    GameScene *gameScene;
    GameEnd *gameEnd;
    // Data.
    Monopoly::WorldPlayer worldPlayer;
    Monopoly::WorldMap worldMap;
    // Current player id number.
    int currentPlayerNumber;

    void init();
    // Clear all game data.
    void clearGameData();
    // Set window be AlignCenter.
    void setWindowAlignCenter(QWidget *child, const QRect &size);
    // Read different map.
    void readUpgradableMap(std::istream &is, size_t location);
    void readCollectableMap(std::istream &is, size_t location);
    void readRandomCostMap(std::istream &is, size_t location);
    void readPrisonMap(std::istream &is, size_t location);
    // Player move.
    void playerMove(int diceNumber);
    // Player decide to do someone action.
    void playerDoSomeoneAction();
    // Is action don't list on UI.
    bool isActionDontList(const std::vector<std::string> &actionList, const std::string &action) const;
    // If there has player is bankrupted but is still in game, set it out of game.
    void setPlayerOutOfGame();
    // Is game over.
    bool isGameOver() const;
    // To the next round.
    void nextRound();
    // To get winner player id pass to GameEnd.
    int getWinnerPlayerId() const;
};

#endif // WIDGET_H
