#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QTextEdit>
#include <vector>
#include <iosfwd>
#include "ActionButton.h"
#include "Scene.h"

namespace Monopoly {
    class Map;
    class Player;
    class WorldMap;
    class WorldPlayer;
}

class GameScene : public QWidget
{
    Q_OBJECT
public:
    GameScene(QWidget *parent, size_t mapSize, size_t playerSize);

    // Change GameScene Screen about immediateInfo, scene, player's status.
    void changeGameSceneStatus(const std::string &str, int currentPlayerId,
                               const Monopoly::WorldMap &worldMap,
                               const Monopoly::WorldPlayer &worldPlayer);
    // List all action that player can doing.
    void listPlayerAction(const Monopoly::Map *map,
                          const Monopoly::Player &player,
                          const std::vector<std::string> &actionList);

signals:
    // Pass signal to Widget to dice.
    void playerDice(int);
    // Pass signal to Widget to do action.
    void playerDoAction(const std::string &);
    // Pass signal to Widget to the new round.
    void newRound();
    // Pass signal from BasicSceneBlock to Widget to get all map property.
    void displayAllMapProperty(int) const;
    // Pass all map property from Widget to BasicSceneBlock.
    void passAllMapProperty(int, const std::vector<std::string> &) const;

public slots:
    // Player choose one action.
    void playerChooseAction(const std::string &);

private slots:
    // Do dice;
    void doDice();
    // Do the next round.
    void doNextRound();

private:
    // Menu screen.
    QLabel *menuInfo;
    QPushButton *exitButton;
    // Action screen.
    QLabel *actionInfo;
    QPushButton *diceButton, *nextTurnButton;
    std::vector<ActionButton *> actionButton;
    // Immediate info screen.
    QTextEdit *immediateInfo;
    // Scene screen.
    Scene *scene;
    // Players info screen.
    QLabel *playerInfo;
    std::vector<QLabel *> playerId;
    std::vector<QLabel *> playerName;
    std::vector<QLabel *> playerMoney;
    std::vector<QLabel *> playerOwnMap;

    void init();
    void initScene(size_t mapSize, size_t playerSize);
    void initPlayerInfo(size_t playerSize);
    void initMenu();
    void initAction();
    void initImmediateInfo();
    // Change GameScene immediate Info.
    void changeImmediateInfo(const std::string &str);
    void changePlayerStatus(size_t currentPlayerId,
                            const Monopoly::WorldPlayer &worldPlayer);
};

#endif // GAMESCENE_H
