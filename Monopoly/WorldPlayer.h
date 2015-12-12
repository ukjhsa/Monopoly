#ifndef WORLDPLAYER_H
#define WORLDPLAYER_H

#include <vector>
#include "Player.h"

namespace Monopoly {

class WorldPlayer
{
public:
    // Add player.
    void addPlayer(const Monopoly::Player &player);

    // Set players.
    Monopoly::Player & operator[] (std::vector<Monopoly::Player>::size_type index);
    std::vector<Monopoly::Player> & getAllPlayers();

    // Get players.
    const Monopoly::Player & operator[] (std::vector<Monopoly::Player>::size_type index) const;
    const std::vector<Monopoly::Player> & getAllPlayers() const;

    // Get size.
    size_t size() const;
    // Clear data.
    void clear();
private:
    std::vector<Monopoly::Player> players;
};

}

#endif // WORLDPLAYER_H
