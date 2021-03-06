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

#ifndef QUESTWINDOW_H
#define QUESTWINDOW_H

#include <string>
#include <vector>
#include "framesbase.h"
#include "player.h"

class CTexture;
class GLFT_Font;
class Quest;

class QuestWindow : public FramesBase
{
	public:
		QuestWindow();
		~QuestWindow();
		void draw( int mouseX, int mouseY );
		bool anyQuestNeedThis( Item *item ) const;
		void addQuest( Quest *quest );
		void addQuestToBeRemoved( Quest *quest );
		void tryToPurgeQuests();
		void removeQuest( Quest *quest );
		void removeAllQuests();
		void changeQuestDescription( Quest *quest, std::string newDescription );
		void clicked( int mouseX, int mouseY, uint8_t mouseState );

	private:
		std::vector<Quest*> quests;
		/// \brief For each quest the description. Formatted for multiline output.
		std::vector< std::vector< std::string > > questDescriptions;
		std::vector< Quest* > questsToBeRemoved;
		int selectedQuestNr;
		CTexture *backgroundTexture;
		GLFT_Font *font;
};

#endif // QUESTWINDOW_H
