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

#ifndef __C_EDITOR_
#define __C_EDITOR_

#include "CTexture.h"
#include "CMessage.h"
#include <stdio.h>
#include <iostream>
#include "cameraFocusHandler.h"

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

		bool enabled;
		int tilepos_offset, tilepos, current_tilepos, current_object, objectedit_selected;
		bool KP_increase_Zpos, KP_decrease_Zpos, KP_tile_ec, KP_tile_inc, KP_add_environment, KP_delete_environment, KP_toggle_tileset, KP_save_zone, KP_moveonce;
		
		// Keeps track of the camera positions saves the original camera
		// to snap back to target after done editing
		cameraFocusHandler *editorFocus, *originalFocus;

		CTexture interfacetexture;
		GLFT_Font *objectDescriptionFont;
		GLFT_Font *keybindingFont;
		CZone *zoneToEdit;
};

#endif
