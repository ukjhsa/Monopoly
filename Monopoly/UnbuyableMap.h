#ifndef UNBUYABLEMAP_H
#define UNBUYABLEMAP_H

#include <vector>
#include <string>
#include "Map.h"

namespace Monopoly {

class Player;
class WorldPlayer;

class UnbuyableMap : public Map
{
public:
    UnbuyableMap(const std::string &name = "", size_t location = 0);
    virtual ~UnbuyableMap();

    virtual std::vector<std::string> getAllMapProperty() const;
    virtual std::string getMapProperty(const std::string &attribute) const;

    virtual std::vector<std::string> getMapAction(const Player &player) const;
    virtual void doAction(Player &player, WorldPlayer &worldPlayer, const std::string &action);
    virtual bool isActionActive(const Player &player, const std::string &action) const;
};

}

#endif // UNBUYABLEMAP_H
