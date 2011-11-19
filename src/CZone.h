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

#ifndef __CZONE__H_
#define __CZONE__H_

#include "CTexture.h"
#include <vector>
#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <fstream>
#include "CDrawingHelpers.h"
#include "GroundLoot.h"
#include "CMagic.h"

class CNPC;
class InteractionPoint;
class InteractionRegion;
class CallIndirection;
class Tile;

struct sTileMap {
	int x_pos, y_pos;
	Tile *tile;
	sTileMap(int _x, int _y, Tile *_tile) {
		x_pos = _x;
		y_pos = _y;
		tile = _tile;
	};

	bool operator<(const sTileMap& tile1) const;
};

struct sEnvironmentMap {
	int x_pos, y_pos, z_pos;
	Tile *tile;
	float transparency, red, green, blue, x_scale, y_scale;
	sEnvironmentMap(int _x, int _y, Tile *_tile, float _tp, float _red, float _green, float _blue, float _x_scale, float _y_scale, int _z_pos) {
		x_pos = _x;
		y_pos = _y;
		tile = _tile;
		transparency = _tp;
		red = _red;
		green = _green;
		blue = _blue;
		x_scale = _x_scale;
		y_scale = _y_scale;
		z_pos = _z_pos;
	};

	bool operator<(const sEnvironmentMap& environmentObject) const { // instead of using a predicate in our sort call.
		if ( z_pos == environmentObject.z_pos )
		{
			if ( y_pos == environmentObject.y_pos ) {
				return x_pos > environmentObject.x_pos;
			} else {
			return y_pos > environmentObject.y_pos;
			}
		} else {
			return z_pos < environmentObject.z_pos;
		}
	};

};

struct sCollisionMap {
	SDL_Rect CR; // Collision Rectangle
	sCollisionMap(int _x, int _y, int _h, int _w) {
		CR.x = _x;
		CR.y = _y;
		CR.h = _h;
		CR.w = _w;
	};
};

struct sShadowMap {
	int x_pos, y_pos, id;
	float transparency, red, green, blue, x_scale, y_scale;
	sShadowMap(int _x, int _y, int _tex_id, float _tp, float _red, float _green, float _blue, float _x_scale, float _y_scale) {
		x_pos = _x;
		y_pos = _y;
		id = _tex_id;
		transparency = _tp;
		red = _red;
		green = _green;
		blue = _blue;
		x_scale = _x_scale;
		y_scale = _y_scale;
	};
};

// TODO:
// Make the CZone a real map
// * Zone is the only point used to look for information (ok some pointers may be set by setCurrentZone)
// * Add enterZone LUA-Interface which loads a zone if it is not loaded, yet and enters that zone at a certain position
//   But it returns by just setting the current zone it does not call a new interface
class CZone
{
	private:
		void DrawTiles();
		void DrawEnvironment();
		void DrawShadows();

		std::string zoneName;
		std::vector <CNPC*> npcs;
		std::vector<InteractionPoint*> interactionPoints;
		std::vector<InteractionRegion*> interactionRegions;
		std::vector<CallIndirection*> eventHandlers;
		GroundLoot groundLoot;
		bool mapLoaded;


	public:
		CZone();
		~CZone();

		void DrawZone();

		void LoadZone(std::string file);
		bool zoneDataLoaded() const;

		int LocateTile(int x, int y);
		int LocateShadow(int x, int y);
		int LocateEnvironment(int x, int y);
		int LocateCollisionbox(int x, int y);
		int LocateNPC(int x, int y);

		void ChangeTile(int iId, Tile *tile);
		void AddEnvironment(int x_pos, int y_pos, Tile *tile, bool centeredOnPos);
		void AddShadow(int x_pos, int y_pos, Tile *tile);
		void AddCollisionbox(int x_pos, int y_pos);
		int DeleteEnvironment(int x, int y);
		int DeleteShadow(int x, int y);
		int DeleteCollisionbox(int x, int y);
		int DeleteNPC(int x, int y);

		void DeleteTile(int iId);

		std::vector<CNPC*> getNPCs();
		void addNPC( CNPC *npcToAdd );
		void removeNPC( CNPC *npcToDelete );
		void cleanupNPCList();

		std::vector<InteractionPoint*> getInteractionPoints();
		void addInteractionPoint( InteractionPoint *interactionPointToAdd );
		void cleanupInteractionList();
		void purgeInteractionList();
		bool findInteractionPointForCharacter( CCharacter *character ) const;

		std::vector<InteractionRegion*> getInteractionRegions();
		void addInteractionRegion( InteractionRegion *interactionRegionToAdd );
		void cleanupInteractionRegionList();
		void purgeInteractionRegionList();

		GroundLoot* getGroundLoot();

		std::string getZoneName() const;
		std::string getLuaSaveText() const;
		void addEventHandler( CallIndirection *newEventHandler );
		// used to restore references when loading
		void findCharacter( CCharacter *character, bool &found, size_t &foundPos ) const;
		void findInteractionPoint( InteractionPoint *interactionPoint, bool &found, size_t &foundPos ) const;
		void findInteractionRegion( InteractionRegion *interactionRegion, bool &found, size_t &foundPos ) const;
		void findEventHandler( CallIndirection *eventHandler, bool &found, size_t &foundPos ) const;
		CCharacter* getCharacterPointer( size_t posInArray ) const;
		InteractionPoint* getInteractionPointPointer( size_t posInArray ) const;
		InteractionRegion* getInteractionRegionPointer( size_t posInArray ) const;
		CallIndirection* getEventHandlerPointer( size_t posInArray ) const;

		std::vector<sTileMap> TileMap;
		std::vector<CMagic*> MagicMap;
		std::vector<sEnvironmentMap> EnvironmentMap;
		// this is the old shadowmap, keeping it here a while... std::vector<sShadowMap> ShadowMap;
		std::vector<sEnvironmentMap> ShadowMap;
		std::vector<sCollisionMap> CollisionMap;
};

#endif
