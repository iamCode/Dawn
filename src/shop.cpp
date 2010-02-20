/**    Copyright (C) 2009,2010  Dawn - 2D roleplaying game    This file is a part of the dawn-rpg project <http://sourceforge.net/projects/dawn-rpg/>.    This program is free software: you can redistribute it and/or modify    it under the terms of the GNU General Public License as published by    the Free Software Foundation, either version 3 of the License, or    (at your option) any later version.    This program is distributed in the hope that it will be useful,    but WITHOUT ANY WARRANTY; without even the implied warranty of    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the    GNU General Public License for more details.    You should have received a copy of the GNU General Public License    along with this program.  If not, see <http://www.gnu.org/licenses/>. **/
#include "shop.h"#include <sstream>

void currency::exchangeCoins( uint32_t &copper, uint32_t &silver, uint32_t &gold, uint32_t &coins )
{
    // exchanging coins to copper coins.
    copper = coins%100;
    coins -= copper;
    if ( coins == 0 )
        return;

    coins /= 100;
    silver =  coins%100;
    coins -= silver;
    if ( coins == 0 )
        return;

    gold = coins/100;
}

std::string currency::convertCoinsToString( currency::currency currency, uint32_t coins )
{
    std::stringstream ss;
    std::string output;

    uint32_t copper = 0, silver = 0, gold = 0;

    exchangeCoins( copper, silver, gold, coins );

    switch ( currency )
    {
        case currency::COPPER:
            ss << copper;
        break;
        case currency::SILVER:
            ss << silver;
        break;
        case currency::GOLD:
            ss << gold;
        break;
    };

    output = ss.str();

    return output;
}
