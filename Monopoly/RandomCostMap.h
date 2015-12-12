#ifndef RANDOMCOSTMAP_H
#define RANDOMCOSTMAP_H

#include <vector>
#include <string>
#include "BuyableMap.h"

namespace Monopoly {

class Player;
class WorldPlayer;

class RandomCostMap : public BuyableMap
{
public:
    RandomCostMap(const std::string &name = "", size_t location = 0, int purchasePrice = 0, int fine = 0);
    virtual ~RandomCostMap();

    virtual std::vector<std::string> getAllMapProperty() const;
    virtual std::string getMapProperty(const std::string &attribute) const;

    virtual std::vector<std::string> getMapAction(const Player &player) const;
    virtual void doAction(Player &player, WorldPlayer &worldPlayer, const std::string &action);
    virtual bool isActionActive(const Player &player, const std::string &action) const;
protected:
    virtual void pay(Player &player, Player &hostPlayer) const;
};

}

#endif // RANDOMCOSTMAP_H
