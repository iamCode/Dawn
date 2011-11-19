/**
    Copyright (C) 2009,2010,2011  Dawn - 2D roleplaying game

    This file is a part of the dawn-rpg project <https://github.com/frusen/Dawn>.

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

#ifndef __QUESTS__H_
#define __QUESTS__H_

#include <iostream>
#include <stdint.h>
#include "item.h"
#include "questwindow.h"

class Quest;
namespace DawnInterface { std::string getReinitialisationString( std::string fullVarName, Quest *quest ); }

class Quest
{
    public:
        Quest( std::string name, std::string description, QuestWindow *questHandler );
        ~Quest();

        bool finishQuest();
        bool isQuestFinished() const;

        void addRequiredItemForCompletion( Item *requiredItem, int quantity );
        bool isItemRequiredInQuest( Item *item ) const;

        void setExperienceReward( uint16_t experienceReward );
        uint16_t getExperienceReward() const;

        void setCoinReward( uint16_t coinReward );
        uint16_t getCoinReward() const;

        void setItemReward( Item *itemReward );
        Item* getItemReward() const;

        void setDescription( std::string description );
        std::string getDescription() const;

        std::string getName() const;

    private:
        QuestWindow *questHandler;

        uint16_t experienceReward;
        uint16_t coinReward;
        Item *itemReward;

        bool questFinished;

        std::vector< std::pair< Item*, int8_t > > requiredItems;

        std::string name;
        std::string description;
        friend std::string DawnInterface::getReinitialisationString( std::string fullVarName, Quest *quest );
};

#endif
