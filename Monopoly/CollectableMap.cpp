#include <vector>
#include <string>
#include <sstream>
#include "MapProperty.h"
#include "Player.h"
#include "WorldPlayer.h"
#include "CollectableMap.h"

using namespace Monopoly;

CollectableMap::CollectableMap(const std::string &name, size_t location, int purchasePrice, int fine)
    : BuyableMap(name, location, purchasePrice, fine)
{
}

CollectableMap::~CollectableMap()
{
}

void CollectableMap::pay(Player &player, Player &hostPlayer) const
{
    int fineMoney = this->getFine() * hostPlayer.getNumberOfOwnMap();
    player.spend(fineMoney);
    hostPlayer.earn(fineMoney);
    // Do what action.
    std::stringstream ss;
    ss << "<Collectable>\n" << "Player " << player.getId()+1 << " pay\n" <<
            "$" << this->getFine() << " x " << hostPlayer.getNumberOfOwnMap() << " = " << fineMoney <<
            "\nto host " << hostPlayer.getId()+1 << "\n";
    player.setDoWhatAction(ss.str());
}

std::vector<std::string> CollectableMap::getAllMapProperty() const
{
    return BuyableMap::getAllMapProperty();
}

std::string CollectableMap::getMapProperty(const std::string &attribute) const
{
    return BuyableMap::getMapProperty(attribute);
}

std::vector<std::string> CollectableMap::getMapAction(const Player &player) const
{
    return BuyableMap::getMapAction(player);
}

void CollectableMap::doAction(Player &player, WorldPlayer &worldPlayer, const std::string &action)
{
    if (action == MapProperty::PAY) {
        // Find host player.
        // In class using find_if must be overloading opeartor(), ...
        for (std::vector<Player>::iterator itPlayer = worldPlayer.getAllPlayers().begin(); itPlayer != worldPlayer.getAllPlayers().end(); ++itPlayer) {
            if (itPlayer->getName() == this->getHost()) {
                this->pay(player, *itPlayer);
                break;
            }
        }
    }
    else {
        BuyableMap::doAction(player, worldPlayer, action);
    }
}

bool CollectableMap::isActionActive(const Player &player, const std::string &action) const
{
    return BuyableMap::isActionActive(player, action);
}
