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
#include "CDirection.h"
#include <SDL/SDL.h> // SDL
#include <math.h>

extern int RES_X,RES_Y,world_x,world_y;
extern CZone zone1;

class CSpell;

class CCharacter
{
    public:

    GLuint frame;
    int x_pos,y_pos;
    float casting_percentage;

    virtual void Draw() = 0;
    virtual void Move() = 0;
    void MoveUp(int world_y_ = 0);
    void MoveDown(int world_y_ = 0);
    void MoveLeft(int world_x_ = 0);
    void MoveRight(int world_x_ = 0);
    void giveMovePoints( uint32_t movePoints );
    void Init(int x, int y) { x_pos = x; y_pos = y; direction_texture = S; remainingMovePoints = 0; is_casting = false; alive = true; curSpell = NULL; }
    bool IsCasting();
    int CollisionCheck(Direction direction);

    void CastSpell(CSpell *spell );


    void CastingInterrupted();
    Direction GetDirection();
    Direction WanderDirection, MovingDirection;

    Uint8 *keys;
    uint32_t casting_currentframe, casting_startframe, casting_offset;


    int GetDirectionTexture();
    int current_texture, direction_texture;
    int CheckForCollision(int x, int y);
    uint32_t remainingMovePoints;

    bool is_casting;
    void CastingComplete();
    void CastingAborted();
    void abortCurrentSpell();

    CSpell *curSpell;

    void baseOnType( std::string otherType );

    void setStrength( uint16_t newStrength );
    uint16_t getStrength() const;
    void modifyStrength( int16_t strengthModifier );

    void setDexterity( uint16_t newDexterity );
    uint16_t getDexterity() const;
    void modifyDexterity( int16_t dexterityModifier );

    void setVitality( uint16_t newVitality );
    uint16_t getVitality() const;
    void modifyVitality( int16_t vitalityModifier );

    void setIntellect( uint16_t newIntellect );
    uint16_t getIntellect() const;
    void modifyIntellect( int16_t intellectModifier );

    void setWisdom( uint16_t newWisdom );
    uint16_t getWisdom() const;
    void modifyWisdom( int16_t wisdomModifier );

    void setMaxHealth( uint16_t newMaxHealth );
    uint16_t getMaxHealth() const;
    uint16_t getCurrentHealth() const;
    void modifyMaxHealth( int16_t maxHealthModifier );

    void setMaxMana( uint16_t newMaxMana );
    uint16_t getMaxMana() const;
    uint16_t getCurrentMana() const;
    void modifyMaxMana( int16_t maxManaModifier );

    void setMaxEnergy( uint16_t newMaxEnergy );
    uint16_t getMaxEnergy() const;
    uint16_t getCurrentEnergy() const;
    void modifyMaxEnergy( int16_t maxEnergyModifier );

    void setWanderRadius( uint16_t newWanderRadius );
    uint16_t getWanderRadius() const;

    void setName( std::string newName );
    std::string getName() const;

    void setLevel ( uint8_t newLevel );
    uint8_t getLevel() const;

    bool isAlive() const
    {
        return alive;
    }

    // NPC attributes
    std::string name;
    uint16_t strength, dexterity, vitality, intellect, wisdom;
    uint16_t wander_radius;
    uint16_t max_health, max_mana, max_energy, current_health, current_mana, current_energy, armor;
    uint8_t alignment, level;

    bool in_target;

    void DrawLifebar();

    void CheckMouseOver(int _x_pos, int _y_pos);
    void Damage(int amount);
    void Heal(int amount);
    void Die();

    void setTexture( CTexture *newTexture );
    CTexture *getTexture() const;
    void setLifebar( CTexture *newLifebar );
    CTexture *getLifebar() const;
    void setMoveTexture( int direction, std::string filename );
    void setLifeTexture( std::string filename );
    CTexture *texture;
    CTexture *lifebar;


    bool alive;

    // states of the NPC
    bool wandering, moving, in_combat;

    // timers
    float wander_thisframe, wander_lastframe;
    float respawn_thisframe, respawn_lastframe;

    // stats
    float life_percentage, mana_percentage, energy_percentage;
    void CalculateStats();

    int wander_every_seconds, wander_points_left;
    bool do_respawn;
    int x_spawn_pos, y_spawn_pos;
    int NPC_id;
    int seconds_to_respawn;

    CZone *zone;
};

class Player : public CCharacter
{
    private:

    public:

    void Move();
    void Draw();
};

class CNPC : public CCharacter
{
    private:

    public:

    CNPC ( int _x_spawn_pos, int _y_spawn_pos, int _NPC_id, int _seconds_to_respawn, int _do_respawn, CZone *_zone) {
        alive = true;
        current_texture = 1; // this will be altered later on to draw what animation frame we want to draw.
        respawn_thisframe = 0.0f; respawn_lastframe = 0.0f; // helps us count when to respawn the NPC.
        wander_thisframe = 0.0f; wander_lastframe = 0.0f; // helping us decide when the mob will wander.
        wander_every_seconds = 1; // this mob wanders every 1 seconds.
        wandering = false;
        MovingDirection = STOP;

        remainingMovePoints = 0;
        direction_texture = S;
    }

    void setSpawnInfo( int _x_spawn_pos, int _y_spawn_pos, int _seconds_to_respawn, int _do_respawn, CZone *_zone )
    {
        x_pos = _x_spawn_pos;
        y_pos = _y_spawn_pos;
        x_spawn_pos = _x_spawn_pos;
        y_spawn_pos = _y_spawn_pos;
        do_respawn = _do_respawn;
        seconds_to_respawn = _seconds_to_respawn;
        zone = _zone;
    }

    void Draw();
    void Move();
    void Respawn();
    void Wander();
};

#endif
