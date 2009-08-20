/**
    Copyright (C) 2009  Dawn - 2D roleplaying game

    This file is a part of the dawn-rpg project.

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

#include "CZone.h"
#include "CMessage.h"
#include "CTexture.h"
#include <stdio.h>
#include <iostream>

extern int world_x, world_y, mouseX, mouseY, RES_X, RES_Y, done;
extern CMessage message;

class CEditor
{
	public:
		CEditor() {
			enabled = false;
			tilepos_offset = 0;
			tilepos = 1;
			current_tilepos = 1;
			current_object = 0;
			objectedit_selected = -1;
			zoneToEdit = NULL;
		};

		void initFonts();

		bool KP_toggle_editor;
		void DrawEditor();
		int SaveZone();
		void HandleKeys();
		void LoadTextures();

		void setEditZone( CZone *zoneToEdit );
		bool isEnabled() const;
		void setEnabled( bool enabled );

	private:
		void inc_tilepos();
		void dec_tilepos();

		void DrawEditFrame(sEnvironmentMap *editobject, CTexture *texture, int object_id);

		bool enabled;
		int tilepos_offset, tilepos, current_tilepos, current_object, objectedit_selected;
		bool KP_tile_dec, KP_tile_inc, KP_add_environment, KP_delete_environment, KP_toggle_tileset, KP_save_zone;

		CTexture interfacetexture;
		GLFT_Font objectDescriptionFont;
		GLFT_Font keybindingFont;
		CZone *zoneToEdit;
};

#endif
