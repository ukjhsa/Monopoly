#ifndef MAP_H
#define MAP_H

#include <vector>
#include <string>
#include <list>

namespace Monopoly {

class Player;
class WorldPlayer;

class Map
{
public:
    Map(const std::string &name = "", size_t location = 0);
    virtual ~Map();

    // Getter.
    const std::string & getName() const;
    size_t getLocation() const;
    const std::list<size_t> & getAllWhoIsHere() const;

    // Get property of this map.
    virtual std::vector<std::string> getAllMapProperty() const;
    virtual std::string getMapProperty(const std::string &attribute) const;

    // Map change whoIsHere.
    // Maybe there are gods in the game, they will change player's status at arriving/leaving map,
    // so the parameter of arrivalAction and leavingAction be non-const.
    void arrivalAction(Player &player);
    void leavingAction(Player &player);

    // Get all possible action.
    virtual std::vector<std::string> getMapAction(const Player &) const;
    // Player do something and that maybe change other players.
    virtual void doAction(Player &player, WorldPlayer &, const std::string &action);
    // Return false if player can't do this action.
    // For example, player has no money, so player can't buy this map.
    virtual bool isActionActive(const Player &, const std::string &action) const;

protected:
    std::string name;
    size_t location;
    // Store who is here by player's id.
    // It usually remove player's id, so using list.
    std::list<size_t> whoIsHere;

    void addWhoIsHere(size_t playerId);
    void removeWhoIsHere(size_t playerId);
};

}

#endif // MAP_H
