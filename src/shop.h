/**    Copyright (C) 2009,2010  Dawn - 2D roleplaying game    This file is a part of the dawn-rpg project <http://sourceforge.net/projects/dawn-rpg/>.    This program is free software: you can redistribute it and/or modify    it under the terms of the GNU General Public License as published by    the Free Software Foundation, either version 3 of the License, or    (at your option) any later version.    This program is distributed in the hope that it will be useful,    but WITHOUT ANY WARRANTY; without even the implied warranty of    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the    GNU General Public License for more details.    You should have received a copy of the GNU General Public License    along with this program.  If not, see <http://www.gnu.org/licenses/>. **/#ifndef __SHOP_H__#define __SHOP_H__

#include <stdint.h>
#include <string>
namespace currency
{
    enum currency
    {
        COPPER, // 100 COPPER == 1 SILVER
        SILVER, // 100 SILVER == 1 GOLD
        GOLD
    };
    void exchangeCoins( uint32_t &copper, uint32_t &silver, uint32_t &gold, uint32_t &coins );
    std::string convertCoinsToString( currency::currency currency, uint32_t coins );
}
class Shop{};#endif
