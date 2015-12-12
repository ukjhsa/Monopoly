#ifndef GAMECONSTANT_H
#define GAMECONSTANT_H

#include <string>

namespace Monopoly {

class GameConstant
{
public:
    static const int MIN_NUMBER_PLAYER = 1;
    static const int MAX_NUMBER_PLAYER = 4;
    static const int DICE_SIZE = 6;
    static const int PASS_ORIGIN_REWARD = 500;
    static const int INITIAL_PLAYER_MONEY = 20000;
};

}

#endif // GAMECONSTANT_H
