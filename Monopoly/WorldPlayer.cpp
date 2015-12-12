#include <vector>
#include "Player.h"
#include "WorldPlayer.h"

using namespace Monopoly;

void WorldPlayer::addPlayer(const Player &player)
{
    players.push_back(player);
}

Player & WorldPlayer::operator[] (std::vector<Player>::size_type index)
{
    return const_cast<Player &>(static_cast<const WorldPlayer &>(*this)[index]);
}

std::vector<Player> & WorldPlayer::getAllPlayers()
{
    return const_cast<std::vector<Player> &>(static_cast<const WorldPlayer &>(*this).getAllPlayers());
}

const Player & WorldPlayer::operator[] (std::vector<Player>::size_type index) const
{
    return players[index];
}

const std::vector<Player> & WorldPlayer::getAllPlayers() const
{
    return players;
}

size_t WorldPlayer::size() const
{
    return players.size();
}

void WorldPlayer::clear()
{
    players.clear();
}
