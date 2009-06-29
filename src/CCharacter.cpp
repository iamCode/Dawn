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

#include "CCharacter.h"

#include "CDrawingHelpers.h"

void CCharacter::Draw() {
    last_direction_texture = GetDirectionTexture();
    DrawingHelpers::mapTextureToRect( texture.texture[last_direction_texture].texture,
                                      x_pos, texture.texture[last_direction_texture].width,
                                      y_pos, texture.texture[last_direction_texture].height );
};

int CCharacter::CheckForCollision(int x_pos, int y_pos) {
    for (unsigned int t=0;t<zone1.CollisionMap.size();t++) {
        if ((zone1.CollisionMap[t].CR.x+zone1.CollisionMap[t].CR.w >= x_pos) && (zone1.CollisionMap[t].CR.x <= x_pos)) {
            if ((zone1.CollisionMap[t].CR.y+zone1.CollisionMap[t].CR.h >= y_pos) && (zone1.CollisionMap[t].CR.y <= y_pos)) {
                return 1;
            }
        }
    }
    return 0;
}

int CCharacter::CollisionCheck(Direction direction) {

    switch (direction) {
        case N:
        // check upper left corner
        if (CheckForCollision(x_pos+1,y_pos+40) == 1) {
            return 1;
        }
        // check upper right corner
        if (CheckForCollision(x_pos+39,y_pos+40) == 1) {
            return 1;
        }
        break;

        case E:
        // check upper right corner
        if (CheckForCollision(x_pos+40,y_pos+39) == 1) {
            return 1;
        }
        // check lower right corner
        if (CheckForCollision(x_pos+40,y_pos+1) == 1) {
            return 1;
        }
        break;

        case S:
        // check lower left corner
        if (CheckForCollision(x_pos+1,y_pos+1) == 1) {
            return 1;
        }
        // check lower right corner
        if (CheckForCollision(x_pos+39,y_pos) == 1) {
            return 1;
        }
        break;

        case W:
        // check upper left corner
        if (CheckForCollision(x_pos,y_pos+39) == 1) {
            return 1;
        }
        // check lower left corner
        if (CheckForCollision(x_pos,y_pos) == 1) {
            return 1;
        }
        break;
    }
    return 0;
};

void CCharacter::MoveUp() {
    if (CollisionCheck(N) == 0) {
        world_y++;
        y_pos++;
        current_texture = 1;
    }
};

void CCharacter::MoveDown() {
    if (CollisionCheck(S) == 0) {
        world_y--;
        y_pos--;
        current_texture = 5;
    }
};

void CCharacter::MoveLeft() {
    if (CollisionCheck(W) == 0) {
        world_x--;
        x_pos--;
        current_texture = 7;
    }
};

void CCharacter::MoveRight() {
    if (CollisionCheck(E) == 0) {
        world_x++;
        x_pos++;
        current_texture = 3;
    }
};

void CCharacter::Move()
{
    int movePerStep = 10; // moves one step per movePerStep ms
    Direction direction = GetDirection();
    while ( remainingMovePoints > movePerStep )
    {
        remainingMovePoints -= movePerStep;

        switch( direction )
        {
            case NW:
                MoveLeft();
                MoveUp();
            break;
            case N:
                MoveUp();
            break;
            case NE:
                MoveRight();
                MoveUp();
            break;
            case W:
                MoveLeft();
            break;
            case E:
                MoveRight();
            break;
            case SW:
                MoveLeft();
                MoveDown();
            break;
            case S:
                MoveDown();
            break;
            case SE:
                MoveRight();
                MoveDown();
            break;
            default:
            break;
        }
    }
}

void CCharacter::giveMovePoints( uint32_t movePoints )
{
    remainingMovePoints += movePoints;
}

Direction CCharacter::GetDirection()
{
    keys = SDL_GetKeyState(NULL);

    if (keys[SDLK_UP]) {
        if (keys[SDLK_LEFT]) {
            return NW;
        } else if (keys[SDLK_RIGHT]) {
            return NE;
        } else {
            return N;
        }
    }

    if (keys[SDLK_DOWN]) {
        if (keys[SDLK_LEFT]) {
            return SW;
        } else if (keys[SDLK_RIGHT]) {
            return SE;
        } else {
            return S;
        }
    }

    if (keys[SDLK_LEFT]) {
        return W;
    }

    if (keys[SDLK_RIGHT]) {
        return E;
    }

    return STOP; 
}

int CCharacter::GetDirectionTexture() {
    int direction = GetDirection();
    if ( direction == STOP )
        return last_direction_texture;
    return static_cast<int>(direction);
}
