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
};

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

    if ((direction != STOP) && IsCasting()) {
        CastingAborted();
    }

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
};

void CCharacter::giveMovePoints( uint32_t movePoints )
{
    remainingMovePoints += movePoints;
};

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
};

int CCharacter::GetDirectionTexture() {
    int direction = GetDirection();
    if ( direction == STOP )
        return last_direction_texture;
    return static_cast<int>(direction);
};

// since we dont have any combat class, im putting this spellcasting here.
// in the future we could probably benefit from putting this into the combat class,
// since we probably would use the same functions for NPCs when they are casting spells etc...

void CCharacter::CastSpell(float casttime_, CNPC *target_, int spell_target_damage_) {
    if (!is_casting) { // setup all variables for a spellcasting.
        is_casting = true;
        casting_startframe = SDL_GetTicks();
        spell_casttime = casttime_;
        spell_target = target_;
        spell_target_damage = spell_target_damage_;
        IsCasting();
    }
};

bool CCharacter::IsCasting() {
    if (is_casting) {
        casting_currentframe = SDL_GetTicks();

        // casting_percentage is mostly just for the castbar display, guess we could alter this code.
        casting_percentage = (static_cast<float>(casting_currentframe-casting_startframe)/1000) / spell_casttime;
        if (casting_percentage >= 1.0f) {
            CastingComplete();
        }
    }
    return is_casting;
};

void CCharacter::CastingComplete() {
    is_casting = false;
    casting_currentframe = 0;
    casting_startframe = 0;

    // when the spellcasting is complete, we will have a pointer to a spell and the NPC id that will be affected by it.
    // So when this spellcasting is complete, we target the NPC, using the CCombat class not yet developed to to affect the mob.
    // fow now we'll just damage / heal the NPC in target
    std::cout << spell_target_damage<< std::endl;
    if (spell_target_damage > 0) {
        spell_target->Heal(spell_target_damage);
    } else {
        spell_target->Damage(-spell_target_damage);
    }
    spell_target = NULL;
};

void CCharacter::CastingAborted() {
    // if we moved, got stunned, or in some way unable to complete the spell ritual, spellcasting will fail.
    // If we are following the above instructions to use a pointer to a spell and so on, we should clear that pointer here.
    is_casting = false;
    spell_target = NULL;
};

void CCharacter::CastingInterrupted() {
    // when casting a spell, mobs attacking us in any way should interfere with our spellcasting, slowing us down a bit.
    // so if we have a spell with 5 seconds spellcast, and we're up at 4 seconds of casting.. getting hit at that moment
    // should set the current_castingtime back to say 3.2 or so..
    casting_startframe += 500; // for now using a static pushback of the spellcasting, 0.5 seconds.
    if (casting_startframe > casting_currentframe) {
        casting_startframe = casting_currentframe;
    }
};
