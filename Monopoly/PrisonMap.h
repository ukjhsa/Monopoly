#ifndef PRISONMAP_H
#define PRISONMAP_H

#include <vector>
#include <string>
#include "UnbuyableMap.h"

namespace Monopoly {

class Player;
class WorldPlayer;

class PrisonMap : public UnbuyableMap
{
public:
    PrisonMap(const std::string &name = "", size_t location = 0);
    virtual ~PrisonMap();

    virtual std::vector<std::string> getAllMapProperty() const;
    virtual std::string getMapProperty(const std::string &attribute) const;

    virtual std::vector<std::string> getMapAction(const Player &player) const;
    virtual void doAction(Player &player, WorldPlayer &, const std::string &action);
    virtual bool isActionActive(const Player &player, const std::string &action) const;
private:
    void stop(Player &player) const;
    void move(Player &player) const;
};

}

#endif // PRISONMAP_H
