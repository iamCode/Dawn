/**                    Dawn - 2D roleplaying game
    Copyright (C) 2009  Tobias Eliasson (arnestig@users.sourceforge.net)

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

struct sTileMap {
    int x_pos, y_pos, id;
    sTileMap(int _x, int _y, int _tex_id) { x_pos = _x; y_pos = _y; id = _tex_id; };
};

struct sEnvironmentMap {
    int x_pos, y_pos, id;
    float transparency;
    bool walkable;
    SDL_Rect CR; // collision rectangle
    sEnvironmentMap( int _x, int _y, int _tex_id, bool _walkable, int _CR_x, int _CR_y, int _CR_h, int _CR_w) {
        x_pos = _x; y_pos = _y; id = _tex_id; walkable = _walkable; CR.x = _CR_x; CR.y = _CR_y; CR.h = _CR_h; CR.w = _CR_w; transparency = 1.0f;
    };
};

struct sCollisionMap {
    SDL_Rect CR; // Collision Rectangle
    sCollisionMap(int _x, int _y, int _h, int _w) { CR.x = _x; CR.y = _y; CR.h = _h; CR.w = _w; };
};

struct sShadowMap {
    int x_pos, y_pos, id;
    float transparency;
    sShadowMap( int _x, int _y, int _tex_id) { x_pos = _x; y_pos = _y; id = _tex_id; transparency = 1.0f; };
};

class CZone {
    private:
    void DrawTiles();
    void DrawEnvironment();
    void DrawShadows();

    public:
    void DrawZone();

    void LoadZone(char *file);
    int LoadMap(char *file);
    int LoadEnvironment(char *file);
    int LoadShadow(char *file);
    int LoadCollisions(char *file);

    int LocateTile(int x, int y);
    int LocateTexture(int x, int y);
    int LocateShadow(int x, int y);

    void ChangeTile(int iId, int texture);
    void AddEnvironment(int x_pos, int y_pos, int texture);
    void AddShadow(int x_pos, int y_pos, int texture);
    int DeleteEnvironment(int x, int y);
    int DeleteShadow(int x, int y);
    int LocateEnvironment(int x, int y);
    void DeleteTile(int iId);

    std::vector<sTileMap> TileMap;
    std::vector<sEnvironmentMap> EnvironmentMap;
    std::vector<sShadowMap> ShadowMap;
    std::vector<sCollisionMap> CollisionMap;

    CTexture ZoneTiles;
    CTexture ZoneEnvironment;
    CTexture ZoneShadow;
};

#endif
