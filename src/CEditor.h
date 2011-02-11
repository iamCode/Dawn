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

#ifndef __C_EDITOR_
#define __C_EDITOR_

#include "CTexture.h"
#include "CMessage.h"
#include <stdio.h>
#include <iostream>
#include "cameraFocusHandler.h"
#include "tileset.h"

class CZone;
class sEnvironmentMap;

extern int mouseX, mouseY, RES_X, RES_Y, done;

class CEditor
{
	public:
		CEditor() {
			enabled = false;
			tilepos_offset = 0;
			tilepos = 0;
			current_tilepos = 0;
			current_object = 0;
			objectedit_selected = -1;
			zoneToEdit = NULL;
			objectDescriptionFont = NULL;
			keybindingFont = NULL;
			adjacencyModeEnabled = false;
			for ( size_t curDirection=0; curDirection <= AdjacencyType::BOTTOM; ++curDirection ) {
				curDirectionAdjacencySelection[ curDirection ] = 0;
			}
		};

		~CEditor() {
		}

		void initFonts();

		bool KP_toggle_editor;
		void DrawEditor();
		void SaveZone();
		void HandleKeys();
		void LoadTextures();
		void initFocus( cameraFocusHandler *character);

		void setEditZone( CZone *zoneToEdit );
		bool isEnabled() const;
		void setEnabled( bool enabled );

	private:
		void inc_tilepos();
		void dec_tilepos();

		void DrawEditFrame(sEnvironmentMap *editobject);
		bool checkAndApplyAdjacencyModification( int modification );
		bool checkAndPlaceAdjacentTile();

		bool enabled;
		int tilepos_offset, current_object, objectedit_selected;
		size_t tilepos,current_tilepos;
		bool KP_increase_Zpos, KP_decrease_Zpos, KP_tile_ec, KP_tile_inc, KP_add_environment, KP_delete_environment, KP_toggle_tileset, KP_save_zone, KP_moveonce, KP_toggle_adjacencyMode;

		// Keeps track of the camera positions saves the original camera
		// to snap back to target after done editing
		cameraFocusHandler *editorFocus, *originalFocus;

		CTexture interfacetexture;
		GLFT_Font *objectDescriptionFont;
		GLFT_Font *keybindingFont;
		CZone *zoneToEdit;

		bool adjacencyModeEnabled;
		std::vector< std::vector<Tile*> > curAdjacentTiles;
		std::vector< std::vector<Point> > curAdjacencyOffsets;
		unsigned int curDirectionAdjacencySelection[AdjacencyType::BOTTOM + 1];
};

#endif
