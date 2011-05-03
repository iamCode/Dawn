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
#include "CZone.h"
#include "globals.h"
#include "shop.h"
#include "CLuaInterface.h"

Quest::Quest( std::string name, std::string description, QuestWindow *questHandler )
    :   name( name ),
        questHandler( questHandler ),
        description( description ),
        experienceReward( 0 ),
        itemReward( NULL ),
        coinReward( 0 ),
        questFinished( false )
{
}

Quest::~Quest()
{
}

void Quest::addRequiredItemForCompletion( Item *requiredItem, int quantity )
{
    requiredItems.push_back( std::pair<Item*,int8_t> ( requiredItem, quantity ) );
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
    questHandler->changeQuestDescription( this, description );
}

std::string Quest::getDescription() const
{
    return description;
}

std::string Quest::getName() const
{
    return name;
}

bool Quest::finishQuest()
{
    // we will try to finish the quest here. Depending on what the quest require of us.
    Player* ourPlayer = Globals::getPlayer();

    // make sure we have all items required in the quest, if not we return false and doesn't finish the quest.
    for ( size_t requiredItemIndex = 0; requiredItemIndex < requiredItems.size(); requiredItemIndex++ ) {
        if ( ourPlayer->getInventory()->doesItemExistInBackpack( requiredItems[ requiredItemIndex ].first, requiredItems[ requiredItemIndex ].second ) == false ) {
            return false;
        }
    }

    // reward the player with experience, items and coins.
    if ( getExperienceReward() > 0 ) {
        ourPlayer->gainExperience( getExperienceReward() );
    }
    if ( getCoinReward() > 0 ) {
        ourPlayer->giveCoins( getCoinReward() );
        GLfloat blue[] = { 0.4f, 0.4f, 0.8f };
        DawnInterface::addTextToLogWindow( blue, "You received %s.",currency::getLongTextString( getCoinReward() ).c_str() );
    }
    if ( getItemReward() != NULL ) {
        DawnInterface::giveItemToPlayer( getItemReward() );
    }

    // remove all quest items from the game that was needed for this quest.

    for ( size_t requiredItemIndex = 0; requiredItemIndex < requiredItems.size(); requiredItemIndex++ ) {
        ourPlayer->getInventory()->removeItem( requiredItems[ requiredItemIndex ].first );
        CZone *curZone = Globals::getCurrentZone();
        curZone->getGroundLoot()->removeItem( requiredItems[ requiredItemIndex ].first );
    }

    questHandler->addQuestToBeRemoved( this );

    return true;
}
