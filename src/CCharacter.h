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

#ifndef __CCHARACTER_H__
#define __CCHARACTER_H__

#include "GLee/GLee.h" // OpenGL Easy Extention Library
#include "CTexture.h"
#include "CZone.h"
#include "CNPC.h"
#include "CDirection.h"
#include <SDL/SDL.h> // SDL

extern int RES_X,RES_Y,world_x,world_y;
extern CZone zone1;

class CSpell;

class CCharacter {
    public:
    GLuint frame;
    int x_pos,y_pos;
    float casting_percentage;

    void MoveUp();
    void MoveDown();
    void MoveLeft();
    void MoveRight();
    void Move();
    void Init(int x, int y) { x_pos = x; y_pos = y; last_direction_texture = 1; remainingMovePoints = 0; is_casting = false; curSpell = NULL; }
    void Draw();
    bool IsCasting();
    int CollisionCheck(Direction direction);
    void CastSpell( CSpell* spell );
    void giveMovePoints( uint32_t movePoints );
    CTexture texture;

    void modifyCurHealth( int16_t curHealthModifier );

    void CastingInterrupted();

    private:
    Uint8 *keys;
    uint32_t casting_currentframe, casting_startframe, casting_offset;
    Direction GetDirection();
    int GetDirectionTexture();
    int current_texture, last_direction_texture;
    int CheckForCollision(int x, int y);
    uint32_t remainingMovePoints;
    bool is_casting;
    void CastingComplete();
    void CastingAborted();
    void abortCurrentSpell();

    CSpell *curSpell;
};


#endif
