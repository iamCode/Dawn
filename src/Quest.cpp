/**
    Copyright (C) 2009,2010,2011  Dawn - 2D roleplaying game

    This file is a part of the dawn-rpg project <http://sourceforge.net/projects/dawn-rpg/>.

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>. **/

#include "Quest.h"

Quest::Quest( std::string name, std::string description )
    :   name( name ),
        description( description ),
        experienceReward( 0 ),
        itemReward( NULL ),
        coinReward( 0 )
{
}

Quest::~Quest()
{
}

void Quest::addRequiredItemForCompletion( Item *requiredItem, uint8_t quantity )
{
    requiredItems.push_back( std::pair<Item*,uint8_t> ( requiredItem, quantity ) );
}

bool Quest::isItemRequiredInQuest( Item *item ) const
{
    for ( size_t curItem = 0; curItem < requiredItems.size(); curItem++ ) {
        if ( requiredItems[ curItem ].first == item ) {
            return true;
        }
    }
    return false;
}

void Quest::setExperienceReward( uint16_t experienceReward )
{
    this->experienceReward = experienceReward;
}

uint16_t Quest::getExperienceReward() const
{
    return experienceReward;
}

void Quest::setCoinReward( uint16_t coinReward )
{
    this->coinReward = coinReward;
}

uint16_t Quest::getCoinReward() const
{
    return coinReward;
}

void Quest::setItemReward( Item *itemReward )
{
    this->itemReward = itemReward;
}

Item* Quest::getItemReward() const
{
    return itemReward;
}

void Quest::setDescription( std::string description )
{
    this->description = description;
}

std::string Quest::getDescription() const
{
    return description;
}

std::string Quest::getName() const
{
    return name;
}
