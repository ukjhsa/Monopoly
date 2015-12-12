#include <string>
#include <vector>
#include <sstream>
#include "Map.h"
#include "MapProperty.h"
#include "Player.h"
#include "WorldPlayer.h"
#include "UpgradableMap.h"

using namespace Monopoly;

UpgradableMap::UpgradableMap(const std::string &name, size_t location, int purchasePrice,
                             int upgradePrice, const std::vector<int> &fines, int level)
    : BuyableMap(name, location, purchasePrice), upgradePrice(upgradePrice), fines(fines), level(level)
{
}

UpgradableMap::~UpgradableMap()
{
}

int UpgradableMap::getUpgradePrice() const
{
    return upgradePrice;
}

int UpgradableMap::getFine() const
{
    if (level >= 1) {
        return fines[level-1];
    }
    else {
        return 0;
    }
}

void UpgradableMap::buy(Player &player)
{
    // To ckeck player isPayable in UI.
    level = 1;
    BuyableMap::buy(player);
    // Do what action.
    std::stringstream ss;
    ss << "<Upgradable>\n" << "Map[" << this->getLocation() << "] level set to 1\n";
    player.setDoWhatAction(ss.str());
}

void UpgradableMap::upgrade(Player &player)
{
    // To ckeck player isPayable in UI.
    player.spend(this->getUpgradePrice());
    ++level;
    // Do what action.
    std::stringstream ss;
    ss << "<Upgradable>\n" << "Player " << player.getId()+1 << " spend $" << this->getUpgradePrice() <<
            "\n to upgrade the map\n";
    player.setDoWhatAction(ss.str());
}

void UpgradableMap::free(Player &player)
{
    this->level = 0;
    BuyableMap::free(player);
}

std::vector<std::string> UpgradableMap::getAllMapProperty() const
{
    std::vector<std::string> allInfo;
    allInfo = Map::getAllMapProperty();
    allInfo.push_back(MapProperty::PURCHASE_PRICE + " " + BuyableMap::getMapProperty(MapProperty::PURCHASE_PRICE));
    allInfo.push_back(MapProperty::HOST + " " + BuyableMap::getMapProperty(MapProperty::HOST));
    allInfo.push_back(MapProperty::FINE + " " + this->getMapProperty(MapProperty::FINE));
    allInfo.push_back(MapProperty::UPGRADE_PRICE + " " + this->getMapProperty(MapProperty::UPGRADE_PRICE));
    allInfo.push_back(MapProperty::UPGRADE_FINE + " " + this->getMapProperty(MapProperty::UPGRADE_FINE));
    allInfo.push_back(MapProperty::LEVEL + " " + this->getMapProperty(MapProperty::LEVEL));
    return allInfo;
}

std::string UpgradableMap::getMapProperty(const std::string &attribute) const
{
    std::stringstream info;
    if (attribute == MapProperty::FINE) {
        info << this->getFine();
    }
    else if (attribute == MapProperty::UPGRADE_PRICE) {
        info << this->upgradePrice;
    }
    // "400->800->1200" => "-400--800--1200-" ,then return.
    else if (attribute == MapProperty::UPGRADE_FINE) {
        for (std::vector<int>::const_iterator itFines = fines.begin(); itFines != fines.end(); ++itFines) {
            info << "-" << *itFines << "-";
        }
    }
    else if (attribute == MapProperty::LEVEL) {
        info << this->level;
    }
    else {
        info << BuyableMap::getMapProperty(attribute);
    }
    return info.str();
}

std::vector<std::string> UpgradableMap::getMapAction(const Player &player) const
{
    std::vector<std::string> actionList;
    // If this map is purchased by self.
    if (host == player.getName()) {
        actionList.push_back(MapProperty::UPGRADE);
        actionList.push_back(MapProperty::NOTHING);
    }
    else {
        actionList = BuyableMap::getMapAction(player);
    }
    return actionList;
}

void UpgradableMap::doAction(Player &player, WorldPlayer &worldPlayer, const std::string &action)
{
    if (action == MapProperty::UPGRADE) {
        upgrade(player);
    }
    else if (action == MapProperty::FREE) {
        if (this->getHost() == player.getName()) {
            free(player);
        }
    }
    else {
        BuyableMap::doAction(player, worldPlayer, action);
    }
}

 bool UpgradableMap::isActionActive(const Player &player, const std::string &action) const
{
    if (action == MapProperty::UPGRADE) {
        return (player.isPayable(this->upgradePrice)) && (this->level < 5);
    }
    else {
        return BuyableMap::isActionActive(player, action);
    }
}
