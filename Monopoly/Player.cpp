#include <string>
#include <sstream>
#include "GameConstant.h"
#include "Player.h"

using namespace Monopoly;

Player::Player(size_t id, const std::string &name, size_t location, int money)
    : id(id), name(name), location(location), money(money),
    numberOfOwnMap(0), isMovable(true), isOutOfGame(false)
{
}

size_t Player::getId() const
{
    return id;
}

const std::string & Player::getName() const
{
    return name;
}

size_t Player::getLocation() const
{
    return location;
}

int Player::getMoney() const
{
    return money;
}

int Player::getNumberOfOwnMap() const
{
    return numberOfOwnMap;
}

bool Player::isPlayerMovable() const
{
    return isMovable;
}

bool Player::isPlayerOutOfGame() const
{
    return isOutOfGame;
}

const std::string & Player::getDoWhatAction() const
{
    return doWhatAction;
}

bool Player::isPayable(int price) const
{
    return money >= price;
}

bool Player::isBankrupted() const
{
    return money < 0;
}

void Player::move(size_t distance, size_t mapSize)
{
    // Move.
    location += distance;
    // Do what action.
    std::stringstream ss;
    ss << "<Dice>\nPlayer " << this->getId()+1 << " dice " << distance << "\n";
    // If player pass starting point.
    if (location >= mapSize) {
        location -= mapSize;
        // Player can obtain some reward.
        earn(GameConstant::PASS_ORIGIN_REWARD);
        ss << "<Passed Origin>\nreward $" << GameConstant::PASS_ORIGIN_REWARD << "\n";
    }
    ss << "Move to map[" <<  location << "]\n";
    this->setDoWhatAction(ss.str());
}

void Player::spend(int price)
{
    money -= price;
}

void Player::earn(int price)
{
    money += price;
}

void Player::increaseNumberOfOwnMap()
{
    ++numberOfOwnMap;
}

void Player::decreaseNumberOfOwnMap()
{
    --numberOfOwnMap;
}

void Player::sentToPrison()
{
    isMovable = false;
}

void Player::releasedFromPrison()
{
    isMovable = true;
}

void Player::setPlayerOutOfGame()
{
    isOutOfGame = true;
    // Do what action.
    std::stringstream ss;
    ss << "<Out Of Game>\nPlayer " << this->getId()+1 << " is out of game\n";
    this->setDoWhatAction(ss.str());
}

void Player::setDoWhatAction(const std::string &str)
{
    doWhatAction = str;
}
