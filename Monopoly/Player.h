#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include "GameConstant.h"

namespace Monopoly {

class Player
{
public:
    Player(size_t id, const std::string &name = "", size_t location = 0,
           int money = GameConstant::INITIAL_PLAYER_MONEY);

    // Getter.
    size_t getId() const;
    const std::string & getName() const;
    size_t getLocation() const;
    int getMoney() const;
    int getNumberOfOwnMap() const;
    bool isPlayerMovable() const;
    bool isPlayerOutOfGame() const;
    const std::string & getDoWhatAction() const;

    // Is player payable $price.
    bool isPayable(int price) const;
    // Is player bankrupted.
    bool isBankrupted() const;

    // Player move.
    void move(size_t distance, size_t mapSize);
    // Player spend $price doing something.
    void spend(int price);
    // Player earn $price.
    void earn(int price);
    // Player increase the number of own map.
    void increaseNumberOfOwnMap();
    // Player decrease the number of own map.
    void decreaseNumberOfOwnMap();
    // Player is sent to prison.
    void sentToPrison();
    // Player is released from prison.
    void releasedFromPrison();
    // Set player is out of game.
    void setPlayerOutOfGame();
    // Set doWhatAction.
    void setDoWhatAction(const std::string &str);
private:
    size_t id;
    std::string name;
    size_t location;
    int money;
    int numberOfOwnMap;
    bool isMovable;
    // If player is bankrupted, player out of game.
    bool isOutOfGame;
    // Store player do what action on the map.
    std::string doWhatAction;
};

}

#endif // PLAYER_H
