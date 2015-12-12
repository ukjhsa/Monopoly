#ifndef UPGRADABLEMAP_H
#define UPGRADABLEMAP_H

#include <vector>
#include <string>
#include "BuyableMap.h"

namespace Monopoly {

class Player;
class WorldPlayer;

class UpgradableMap : public BuyableMap
{
public:
    UpgradableMap(const std::string &name = "", size_t location = 0, int purchasePrice = 0,
                  int upgradePrice = 0, const std::vector<int> &fines = std::vector<int>(), int level = 0);
    virtual ~UpgradableMap();

    // Getter.
    int getUpgradePrice() const;
    virtual int getFine() const;

    virtual std::vector<std::string> getAllMapProperty() const;
    virtual std::string getMapProperty(const std::string &attribute) const;

    virtual std::vector<std::string> getMapAction(const Player &player) const;
    virtual void doAction(Player &player, WorldPlayer &worldPlayer, const std::string &action);
    virtual bool isActionActive(const Player &player, const std::string &action) const;
protected:
    int upgradePrice;
    std::vector<int> fines;
    int level;

    virtual void buy(Player &player);
    void upgrade(Player &player);
    virtual void free(Player &player);
};

}

#endif // UPGRADABLEMAP_H
