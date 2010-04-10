/**
    Copyright (C) 2009,2010  Dawn - 2D roleplaying game

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

void formatMultilineText( std::string text, std::vector< std::string > &textLines, int lineWidth, GLFT_Font *font );

QuestWindow::QuestWindow()
{
	selectedQuestNr = -1;
	posX = 20;
	posY = 100;
	visible = false;
	font = NULL;
	backgroundTexture = NULL;

	font = FontCache::getFontFromCache("data/verdana.ttf", 14);
	backgroundTexture = new CTexture();
	backgroundTexture->texture.resize(1);
	backgroundTexture->LoadIMG( "data/interface/QuestScreen/questscreen.tga", 0 );

	width = backgroundTexture->texture[0].width;
	height = backgroundTexture->texture[0].height;
}

QuestWindow::~QuestWindow()
{
	if ( backgroundTexture != NULL ) {
		delete backgroundTexture;
	}
}

void QuestWindow::draw()
{
	DrawingHelpers::mapTextureToRect( backgroundTexture->texture[0].texture,
	                                  posX + world_x, width,
	                                  posY + world_y, height );

	int textX = world_x + posX + 64;
	int textY = world_y + posY + height - 64 - font->getHeight();

	glColor4f( 1.0f, 1.0f, 1.0f, 1.0f );
	for ( size_t curQuestNameNr = 0; curQuestNameNr<questNames.size(); ++curQuestNameNr ) {
		if ( static_cast<int>(curQuestNameNr) == selectedQuestNr ) {
			// draw selected text in yellow
			glColor4f( 1.0f, 1.0f, 0.0f, 1.0f );
		}

		font->drawText( textX, textY, questNames[ curQuestNameNr ] );

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

void QuestWindow::addQuest( std::string name, std::string description )
{
	questNames.push_back( name );
	size_t newQuestNr = questDescriptions.size();
	questDescriptions.push_back( std::vector<std::string>() );
	formatMultilineText( description, questDescriptions[ newQuestNr ], width - 128, font );

	if ( selectedQuestNr == -1 && questNames.size() > 0) {
		selectedQuestNr = 0;
	}
}

void QuestWindow::removeQuest( std::string name )
{
	size_t foundQuestNr = 0;
	for ( foundQuestNr=0; foundQuestNr<questNames.size(); ++foundQuestNr ) {
		if ( questNames[ foundQuestNr ] == name ) {
			break;
		}
	}

	if ( foundQuestNr < questNames.size() ) {
		// found the quest
		questNames.erase( questNames.begin() + foundQuestNr );
		questDescriptions.erase( questDescriptions.begin() + foundQuestNr );
		if ( selectedQuestNr == static_cast<int>(foundQuestNr) ) {
			selectedQuestNr = -1;
		} else if ( selectedQuestNr > static_cast<int>(foundQuestNr) ) {
			--selectedQuestNr;
		}
	}

	if ( selectedQuestNr == -1 && questNames.size() > 0 ) {
		selectedQuestNr = 0;
	}
}

void QuestWindow::removeAllQuests()
{
	questNames.clear();
	questDescriptions.clear();
	selectedQuestNr = -1;
}

void QuestWindow::changeQuestDescription( std::string name, std::string newDescription )
{
	size_t foundQuestNr = 0;
	for ( foundQuestNr=0; foundQuestNr<questNames.size(); ++foundQuestNr ) {
		if ( questNames[ foundQuestNr ] == name ) {
			break;
		}
	}

	if ( foundQuestNr < questNames.size() ) {
		// found the quest
		questDescriptions[ foundQuestNr ].clear();
		formatMultilineText( newDescription, questDescriptions[ foundQuestNr ], width - 128, font );
	}
}

bool QuestWindow::isOnThisScreen( int posX, int posY ) const
{
	if ( posX < this->posX + 64 || posX > this->posX + width - 64
	     || posY > this->posY + height - 64 || posY < this->posY + 246 ) {
	     return false;
	}
	return true;
}

void QuestWindow::clicked( int mouseX, int mouseY )
{
	if ( ! isOnThisScreen( mouseX, mouseY ) ) {
		return;
	}

	size_t curEntryNr = (posY + height - 64 - mouseY) / (font->getHeight() * 1.5);
	if ( curEntryNr < questNames.size() ) {
		selectedQuestNr = curEntryNr;
	}
}

void QuestWindow::setVisible( bool visible )
{
	this->visible = visible;
}

bool QuestWindow::isVisible() const
{
	return visible;
}

std::string QuestWindow::getReloadScriptText() const
{
	std::ostringstream oss;
	for ( size_t curQuestNr=0; curQuestNr<questNames.size(); ++curQuestNr ) {
		oss << "DawnInterface.addQuest( '" << questNames[ curQuestNr ] << "', '";
		for ( size_t curQuestDescriptionNr=0; curQuestDescriptionNr<questDescriptions[curQuestNr].size(); ++curQuestDescriptionNr ) {
			oss << questDescriptions[curQuestNr][curQuestDescriptionNr];
			if ( curQuestDescriptionNr < questDescriptions[curQuestNr].size() - 1 ) {
				oss << " ";
			}
		}
		oss << "' );" << std::endl;
	}
	return oss.str();
}

extern std::auto_ptr<QuestWindow> questWindow;

namespace DawnInterface
{
	void addQuest( std::string questName, std::string questDescription )
	{
		questWindow->addQuest( questName, questDescription );
	}

	void removeQuest( std::string questName )
	{
		questWindow->removeQuest( questName );
	}

	void changeQuestDescription( std::string questName, std::string newDescription )
	{
		questWindow->changeQuestDescription( questName, newDescription );
	}
	
	std::string getQuestSaveText()
	{
		return questWindow->getReloadScriptText();
	}
}

