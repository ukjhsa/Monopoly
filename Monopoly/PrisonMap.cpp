#include <vector>
#include <string>
#include <sstream>
#include "MapProperty.h"
#include "Player.h"
#include "WorldPlayer.h"
#include "PrisonMap.h"

using namespace Monopoly;

PrisonMap::PrisonMap(const std::string &name, size_t location)
    : UnbuyableMap(name, location)
{
}

PrisonMap::~PrisonMap()
{
}

void PrisonMap::stop(Player &player) const
{
    player.sentToPrison();
    // Do what action.
    std::stringstream ss;
    ss << "<Prison>\n" << "Player " << player.getId()+1 << "\nbe sent to prison\n";
    player.setDoWhatAction(ss.str());
}

void PrisonMap::move(Player &player) const
{
    player.releasedFromPrison();
    // Do what action.
    std::stringstream ss;
    ss << "<Prison>\n" << "Player " << player.getId()+1 << "\nbe released from prison\n";
    player.setDoWhatAction(ss.str());
}

std::vector<std::string> PrisonMap::getAllMapProperty() const
{
    return UnbuyableMap::getAllMapProperty();
}

std::string PrisonMap::getMapProperty(const std::string &attribute) const
{
    return UnbuyableMap::getMapProperty(attribute);
}

std::vector<std::string> PrisonMap::getMapAction(const Player &player) const
{
    std::vector<std::string> actionList;
    if (player.isPlayerMovable()) {
        actionList.push_back(MapProperty::STOP);
    }
    else {
        actionList.push_back(MapProperty::MOVE);
    }
    return actionList;
}

void PrisonMap::doAction(Player &player, WorldPlayer &, const std::string &action)
{
    if (action == MapProperty::STOP) {
        stop(player);
    }
    if (action == MapProperty::MOVE) {
        move(player);
    }
    else {
        // This is impossible.
    }
}

bool PrisonMap::isActionActive(const Player &player, const std::string &action) const
{
    if (action == MapProperty::STOP) {
        return false;
    }
    else {
        return UnbuyableMap::isActionActive(player, action);
    }
}
