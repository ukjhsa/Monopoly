#include <vector>
#include <string>
#include <sstream>
#include "MapProperty.h"
#include "Player.h"
#include "WorldPlayer.h"
#include "BuyableMap.h"

using namespace Monopoly;

BuyableMap::BuyableMap(const std::string &name, size_t location, int purchasePrice, int fine)
    : Map(name, location), purchasePrice(purchasePrice), fine(fine)
{
}

BuyableMap::~BuyableMap()
{
}

int BuyableMap::getPurchasePrice() const
{
    return purchasePrice;
}

const std::string & BuyableMap::getHost() const
{
    return host;
}

int BuyableMap::getFine() const
{
    return fine;
}

void BuyableMap::setHost(const std::string &host)
{
    this->host = host;
}

void BuyableMap::pay(Player &player, Player &hostPlayer) const
{
    player.spend(this->getFine());
    hostPlayer.earn(this->getFine());
    // Do what action.
    std::stringstream ss;
    ss << "<Pay>\n" << "Player " << player.getId()+1 << " pay $" << this->getFine() <<
            "\nto host " << hostPlayer.getId()+1 << "\n";
    player.setDoWhatAction(ss.str());
}

void BuyableMap::buy(Player &player)
{
    // To ckeck player isPayable in UI.
    player.spend(this->getPurchasePrice());
    this->setHost(player.getName());
    player.increaseNumberOfOwnMap();
    // Do what action.
    std::stringstream ss;
    ss << "<Buy>\n" << "Player " << player.getId()+1 << " spend $" << this->getPurchasePrice() <<
            "\nto buy the map\n";
    player.setDoWhatAction(ss.str());
}

void BuyableMap::free(Player &player)
{
    this->setHost("");
    player.decreaseNumberOfOwnMap();
    // Do what action.
    std::stringstream ss;
    ss << "<Free>\n" << "Player " << player.getId()+1 << " free map[" << this->getLocation() << "]\n";
    player.setDoWhatAction(ss.str());
}

std::vector<std::string> BuyableMap::getAllMapProperty() const
{
    std::vector<std::string> allInfo;
    allInfo = Map::getAllMapProperty();
    allInfo.push_back(MapProperty::PURCHASE_PRICE + " " + this->getMapProperty(MapProperty::PURCHASE_PRICE));
    allInfo.push_back(MapProperty::HOST + " " + this->getMapProperty(MapProperty::HOST));
    allInfo.push_back(MapProperty::FINE + " " + this->getMapProperty(MapProperty::FINE));
    return allInfo;
}

std::string BuyableMap::getMapProperty(const std::string &attribute) const
{
    std::stringstream info;
    if (attribute == MapProperty::PURCHASE_PRICE) {
        info << this->purchasePrice;
    }
    else if (attribute == MapProperty::HOST) {
        info << this->host;
    }
    else if (attribute == MapProperty::FINE) {
        info << this->fine;
    }
    else {
        info << Map::getMapProperty(attribute);
    }
    return info.str();
}

std::vector<std::string> BuyableMap::getMapAction(const Player &player) const
{
    std::vector<std::string> actionList;
    // If this map is no host.
    if (host.empty()) {
        actionList.push_back(MapProperty::BUY);
        actionList.push_back(MapProperty::NOTHING);
    }
    // If this map is purchased by someone.
    else if (host != player.getName()) {
        actionList.push_back(MapProperty::PAY);
    }
    else {
        actionList = Map::getMapAction(player);
    }
    return actionList;
}

void BuyableMap::doAction(Player &player, WorldPlayer &worldPlayer, const std::string &action)
{
    if (action == MapProperty::PAY) {
        // Find host player.
        // In class using find_if must be overloading opeartor(), ...
        for (std::vector<Player>::iterator itPlayer = worldPlayer.getAllPlayers().begin();
        itPlayer != worldPlayer.getAllPlayers().end(); ++itPlayer) {
            if (itPlayer->getName() == this->getHost()) {
                this->pay(player, *itPlayer);
                break;
            }
        }
    }
    else if (action == MapProperty::BUY) {
        buy(player);
    }
    else if (action == MapProperty::FREE) {
        if (this->getHost() == player.getName()) {
            free(player);
        }
    }
    else {
        Map::doAction(player, worldPlayer, action);
    }
}

bool BuyableMap::isActionActive(const Player &player, const std::string &action) const
{
    if (action == MapProperty::BUY) {
        return player.isPayable(this->getPurchasePrice());
    }
    else if (action == MapProperty::PAY) {
        return false;
    }
    else {
        return Map::isActionActive(player, action);
    }
}
