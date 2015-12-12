#include <vector>
#include "Map.h"
#include "WorldMap.h"

using namespace Monopoly;

void WorldMap::addMap(Map *map)
{
    maps.push_back(map);
}

Map * WorldMap::operator[] (std::vector<Map *>::size_type index)
{
    return const_cast<Map *>(static_cast<const WorldMap &>(*this)[index]);
}

std::vector<Map *> & WorldMap::getAllMaps()
{
    return const_cast<std::vector<Map *> &>(static_cast<const WorldMap *>(this)->getAllMaps());
}

const Map * WorldMap::operator[] (std::vector<Map *>::size_type index) const
{
    return maps[index];
}

const std::vector<Map *> & WorldMap::getAllMaps() const
{
    return maps;
}

size_t WorldMap::size() const
{
    return maps.size();
}

void WorldMap::clear()
{
    for (std::vector<Map *>::iterator itMap = maps.begin(); itMap != maps.end(); ++itMap) {
        delete *itMap;
    }
    maps.clear();
}
