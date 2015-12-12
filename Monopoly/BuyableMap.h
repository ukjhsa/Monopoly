#ifndef BUYABLEMAP_H
#define BUYABLEMAP_H

#include <vector>
#include <string>
#include "Map.h"

namespace Monopoly {

class Player;
class WorldPlayer;

class BuyableMap : public Map
{
public:
    BuyableMap(const std::string &name = "", size_t location = 0, int purchasePrice = 0, int fine = 0);
    virtual ~BuyableMap();

    // Getter.
    int getPurchasePrice() const;
    const std::string & getHost() const;
    // Because the fine of upgrade map is different.
    virtual int getFine() const;

    // Setter.
    void setHost(const std::string &host);

    virtual std::vector<std::string> getAllMapProperty() const;
    virtual std::string getMapProperty(const std::string &attribute) const;

    virtual std::vector<std::string> getMapAction(const Player &player) const;
    virtual void doAction(Player &player, WorldPlayer &worldPlayer, const std::string &action);
    virtual bool isActionActive(const Player &player, const std::string &action) const;
protected:
    int purchasePrice;
    std::string host;
    int fine;

    // Player will pay money to hostPlayer.
    virtual void pay(Player &player, Player &hostPlayer) const;
    // Player will buy this map.
    virtual void buy(Player &player);
    // Host player free this map.
    virtual void free(Player &player);
};

}

#endif // BUYABLEMAP_H
