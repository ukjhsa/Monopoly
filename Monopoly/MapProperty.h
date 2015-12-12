#ifndef MAPPROPERTY_H
#define MAPPROPERTY_H

#include <string>

namespace Monopoly {

class MapProperty
{
public:
    static const std::string
            // Action.
            NOTHING, BUY, PAY, UPGRADE, STOP, MOVE, FREE, ERROR_ACTION,
            // Attribute.
            NAME, LOCATION, WHOISHERE, PURCHASE_PRICE, HOST, UPGRADE_PRICE,
            FINE, UPGRADE_FINE, LEVEL, ERROR_ATTRIBUTE;

    static const int sizeOfAttribute = 9;
};

}

#endif // MAPPROPERTY_H
