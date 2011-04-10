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

#include "questwindow.h"
#include "CTexture.h"
#include "CDrawingHelpers.h"
#include "GLFT_Font.h"
#include <memory>
#include "fontcache.h"
#include "FramesBase.h"

void formatMultilineText( std::string text, std::vector< std::string > &textLines, int lineWidth, GLFT_Font *font );

extern std::auto_ptr<QuestWindow> questWindow;

namespace DawnInterface
{
    void addTextToLogWindow( GLfloat color[], const char *text, ... );

	Quest* addQuest( std::string questName, std::string questDescription )
	{
		Quest *newQuest = new Quest( questName, questDescription );
		questWindow->addQuest( newQuest );
		return newQuest;
	}

	void finishQuest( Quest *quest )
	{
		questWindow->finishQuest( quest );
	}

	void changeQuestDescription( Quest *quest, std::string newDescription )
	{
		questWindow->changeQuestDescription( quest, newDescription );
	}
}

QuestWindow::QuestWindow() : FramesBase( 20, 100, 375, 376, 20, 20 )
{
	addMoveableFrame( 375, 22, 20, 374 );
	addCloseButton( 22, 22, 373, 376 );

	selectedQuestNr = -1;
	visible = false;
	font = NULL;
	backgroundTexture = NULL;

	font = FontCache::getFontFromCache("data/verdana.ttf", 14);
	backgroundTexture = new CTexture();
	backgroundTexture->LoadIMG( "data/interface/QuestScreen/questscreen.tga", 0 );
}

QuestWindow::~QuestWindow()
{
	if ( backgroundTexture != NULL ) {
		delete backgroundTexture;
	}
}

void QuestWindow::draw( int mouseX, int mouseY )
{
	DrawingHelpers::mapTextureToRect( backgroundTexture->getTexture(0),
	                                  posX + world_x, backgroundTexture->getTexture(0).width,
	                                  posY + world_y, backgroundTexture->getTexture(0).height );

	int textX = world_x + posX + 64;
	int textY = world_y + posY + frameHeight - 24 - font->getHeight();

	glColor4f( 1.0f, 1.0f, 1.0f, 1.0f );
	for ( size_t curQuestNameNr = 0; curQuestNameNr<quests.size(); ++curQuestNameNr ) {
		if ( static_cast<int>(curQuestNameNr) == selectedQuestNr ) {
			// draw selected text in yellow
			glColor4f( 1.0f, 1.0f, 0.0f, 1.0f );
		}

		font->drawText( textX, textY, quests[ curQuestNameNr ]->getName() );

		if ( static_cast<int>(curQuestNameNr) == selectedQuestNr ) {
			// reset color after drawing selected text
			glColor4f( 1.0f, 1.0f, 1.0f, 1.0f );
		}
		textY -= font->getHeight() * 1.5;
	}

	int topOfDescriptionBox = 192;
	textY = world_y + posY + topOfDescriptionBox - font->getHeight();

	if ( selectedQuestNr >= 0 && static_cast<size_t>(selectedQuestNr) < questDescriptions.size() ) {
		// draw description of currently selected quest
		std::vector<std::string> selectedQuestDescription = questDescriptions[ selectedQuestNr ];
		for ( size_t curLineNr=0; curLineNr<selectedQuestDescription.size(); ++curLineNr ) {
			std::string curLine = selectedQuestDescription[ curLineNr ];
			font->drawText( textX, textY, curLine );
			textY -= font->getHeight() * 1.5;
		}
	}
}

void QuestWindow::addQuest( Quest *quest )
{
	quests.push_back( quest );
	size_t newQuestNr = questDescriptions.size();
	questDescriptions.push_back( std::vector<std::string>() );
	formatMultilineText( quest->getDescription(), questDescriptions[ newQuestNr ], frameWidth - 88, font );

    GLfloat green[] = { 0.15f, 1.0f, 0.15f };
    DawnInterface::addTextToLogWindow( green, "Quest accepted: %s.", quest->getName().c_str() );

	if ( selectedQuestNr == -1 && quests.size() > 0) {
		selectedQuestNr = 0;
	}
}

void QuestWindow::finishQuest( Quest *quest )
{
	size_t foundQuestNr = 0;
	for ( foundQuestNr=0; foundQuestNr<quests.size(); ++foundQuestNr ) {
		if ( quests[ foundQuestNr ] == quest ) {
			break;
		}
	}

	if ( foundQuestNr < quests.size() ) {
		// found the quest
		if ( quest->finishQuest() == true ) { // we were able to finish the quest, delete it from our questwindow
		    quests.erase( quests.begin() + foundQuestNr );
            questDescriptions.erase( questDescriptions.begin() + foundQuestNr );
            if ( selectedQuestNr == static_cast<int>(foundQuestNr) ) {
                selectedQuestNr = -1;
            } else if ( selectedQuestNr > static_cast<int>(foundQuestNr) ) {
                --selectedQuestNr;
            }

            GLfloat green[] = { 0.15f, 1.0f, 0.15f };
            DawnInterface::addTextToLogWindow( green, "Quest completed: %s.", quest->getName().c_str() );
            delete quest;
        }
	}

	if ( selectedQuestNr == -1 && quests.size() > 0 ) {
		selectedQuestNr = 0;
	}
}

void QuestWindow::removeAllQuests()
{
	for ( size_t questIndex = 0; questIndex < quests.size(); questIndex++ ) {
	    delete quests[ questIndex ];
	}

	quests.clear();
	questDescriptions.clear();
	selectedQuestNr = -1;
}

void QuestWindow::changeQuestDescription( Quest *quest, std::string newDescription )
{
	quest->setDescription( newDescription );
	size_t foundQuestNr = 0;
	for ( foundQuestNr=0; foundQuestNr<quests.size(); ++foundQuestNr ) {
		if ( quests[ foundQuestNr ] == quest ) {
			break;
		}
	}

	if ( foundQuestNr < quests.size() ) {
		// found the quest
		questDescriptions[ foundQuestNr ].clear();
		formatMultilineText( newDescription, questDescriptions[ foundQuestNr ], frameWidth - 88, font );

		GLfloat green[] = { 0.15f, 1.0f, 0.15f };
        DawnInterface::addTextToLogWindow( green, "Quest updated: %s.", quest->getName().c_str() );
	}
}

void QuestWindow::clicked( int mouseX, int mouseY, uint8_t mouseState )
{
	if ( ! isMouseOnFrame( mouseX, mouseY ) ) {
		return;
	}

	size_t curEntryNr = (posY + frameHeight - 24 - mouseY) / (font->getHeight() * 1.5);
	if ( curEntryNr < quests.size() ) {
		selectedQuestNr = curEntryNr;
	}
}
