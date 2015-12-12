#include <vector>
#include <string>
#include <cstdlib>
#include <time.h>
#include <sstream>
#include "MapProperty.h"
#include "Player.h"
#include "WorldPlayer.h"
#include "GameConstant.h"
#include "RandomCostMap.h"

using namespace Monopoly;

RandomCostMap::RandomCostMap(const std::string &name, size_t location, int purchasePrice, int fine)
    : BuyableMap(name, location, purchasePrice, fine)
{
}

RandomCostMap::~RandomCostMap()
{
}

void RandomCostMap::pay(Player &player, Player &hostPlayer) const
{
    srand(time(NULL));
    int number = rand() % Monopoly::GameConstant::DICE_SIZE + 1;
    int fineMoney = this->getFine() * number;
    player.spend(fineMoney);
    hostPlayer.earn(fineMoney);
    // Do what action.
    std::stringstream ss;
    ss << "<RandomCost>\n" << "Player " << player.getId()+1 << " pay\n"
            "$" << this->getFine() << " x " << number << " = " << fineMoney <<
            "\nto host " << hostPlayer.getId()+1 << "\n";
    player.setDoWhatAction(ss.str());
}

std::vector<std::string> RandomCostMap::getAllMapProperty() const
{
    return BuyableMap::getAllMapProperty();
}

std::string RandomCostMap::getMapProperty(const std::string &attribute) const
{
    return BuyableMap::getMapProperty(attribute);
}

std::vector<std::string> RandomCostMap::getMapAction(const Player &player) const
{
    return BuyableMap::getMapAction(player);
}

void RandomCostMap::doAction(Player &player, WorldPlayer &worldPlayer, const std::string &action)
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

bool RandomCostMap::isActionActive(const Player &player, const std::string &action) const
{
    return BuyableMap::isActionActive(player, action);
}
