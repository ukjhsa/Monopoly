#include <vector>
#include <string>
#include <list>
#include <sstream>
#include "MapProperty.h"
#include "Player.h"
#include "Map.h"

using namespace Monopoly;

Map::Map(const std::string &name, size_t location)
    : name(name), location(location)
{
}

Map::~Map()
{
}

const std::string & Map::getName() const
{
    return name;
}

size_t Map::getLocation() const
{
    return location;
}

const std::list<size_t> &Map::getAllWhoIsHere() const
{
    return whoIsHere;
}

void Map::addWhoIsHere(size_t playerId)
{
    whoIsHere.push_back(playerId);
}

void Map::removeWhoIsHere(size_t playerId)
{
    whoIsHere.remove(playerId);
}

std::vector<std::string> Map::getAllMapProperty() const
{
    std::vector<std::string> allInfo;
    allInfo.push_back(MapProperty::NAME + " " + this->getMapProperty(MapProperty::NAME));
    allInfo.push_back(MapProperty::LOCATION + " " + this->getMapProperty(MapProperty::LOCATION));
    allInfo.push_back(MapProperty::WHOISHERE + " " + this->getMapProperty(MapProperty::WHOISHERE));
    return allInfo;
}

std::string Map::getMapProperty(const std::string &attribute) const
{
    std::stringstream info;
    if (attribute == MapProperty::NAME) {
        info << this->name;
    }
    else if (attribute == MapProperty::LOCATION) {
        info << this->location;
    }
    // "1->3->2" => "-1--3--2-" ,then return.
    else if (attribute == MapProperty::WHOISHERE) {
        for (auto itWho = whoIsHere.begin(); itWho != whoIsHere.end(); ++itWho) {
            info << "-" << *itWho << "-";
        }
    }
    else {
        info << MapProperty::ERROR_ATTRIBUTE;
    }
    return info.str();
}

void Map::arrivalAction(Player &player)
{
    addWhoIsHere(player.getId());
}

void Map::leavingAction(Player &player)
{
    removeWhoIsHere(player.getId());
}

std::vector<std::string> Map::getMapAction(const Player &) const
{
    std::vector<std::string> actionList;
    actionList.push_back(MapProperty::NOTHING);
    return actionList;
}

void Map::doAction(Player &player, WorldPlayer &, const std::string &action)
{
    if (action == MapProperty::NOTHING) {
        // Nothing to do.
        player.setDoWhatAction("Player do nothing\n");
    }
    else {
        // This is impossible.
    }
}

bool Map::isActionActive(const Player &, const std::string &action) const
{
    if (action == MapProperty::NOTHING) {
        return true;
    }
    else {
        return false;
    }
}
