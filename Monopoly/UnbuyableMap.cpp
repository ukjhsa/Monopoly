#include <vector>
#include "MapProperty.h"
#include "Player.h"
#include "WorldPlayer.h"
#include "UnbuyableMap.h"

using namespace Monopoly;

UnbuyableMap::UnbuyableMap(const std::string &name, size_t location)
    : Map(name, location)
{
}

UnbuyableMap::~UnbuyableMap()
{
}

std::vector<std::string> UnbuyableMap::getAllMapProperty() const
{
    return Map::getAllMapProperty();
}

std::string UnbuyableMap::getMapProperty(const std::string &attribute) const
{
    return Map::getMapProperty(attribute);
}

std::vector<std::string> UnbuyableMap::getMapAction(const Player &player) const
{
    return Map::getMapAction(player);
}

void UnbuyableMap::doAction(Player &player, WorldPlayer &worldPlayer, const std::string &action)
{
    Map::doAction(player, worldPlayer, action);
}

bool UnbuyableMap::isActionActive(const Player &player, const std::string &action) const
{
    return Map::isActionActive(player, action);
}
