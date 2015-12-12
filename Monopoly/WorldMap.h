#ifndef WORLDMAP_H
#define WORLDMAP_H

#include <vector>
#include "Map.h"

namespace Monopoly {

class WorldMap
{
public:
    enum MapCategory {
        UPGRADE = 'U',
        COLLECT = 'C',
        RANDOM = 'R',
        JAIL = 'J'
    };

    // Add map.
    void addMap(Map *map);

    // Set map.
    Map * operator[] (std::vector<Map *>::size_type index);
    std::vector<Map *> & getAllMaps();

    // Get map.
    const Map * operator[] (std::vector<Map *>::size_type index) const;
    const std::vector<Map *> & getAllMaps() const;

    // Get size.
    size_t size() const;
    // Clear data.
    void clear();
private:
    std::vector<Map *> maps;
};

}

#endif // WORLDMAP_H
