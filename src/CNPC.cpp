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

#include "CNPC.h"
#include "CDrawingHelpers.h"

#include <map>
#include <string>
#include <limits>
#include <iostream>

std::map< std::string, CNPC* > allMobTypes;

// Dawn LUA Interface
namespace DawnInterface
{
    CNPC* createNewMobType( std::string typeID )
    {
        CNPC *newMobType = new CNPC(0, 0, 0, 0, 0, NULL);
        newMobType->texture = NULL;
        newMobType->lifebar = NULL;
        allMobTypes[ typeID ] = newMobType;
        return newMobType;
    }
}

void CNPC::baseOnType( std::string otherName )
{
    CNPC *other;
    if ( allMobTypes.count( otherName ) != 1 )
    {
        std::cerr << "mob type \"" << otherName << "\" found " << allMobTypes.count( otherName ) << " times!!! aborting." << std::endl;
        abort();
    }
    other = allMobTypes[ otherName ];
    setStrength( other->getStrength() );
    setDexterity( other->getDexterity() );
    setVitality( other->getVitality() );
    setIntellect( other->getIntellect() );
    setWisdom( other->getWisdom() );
    setMaxHealth( other->getMaxHealth() );
    setMaxMana( other->getMaxMana() );
    setMaxEnergy( other->getMaxEnergy() );
    setTexture( other->getTexture() );
    setLifebar( other->getLifebar() );
}

void CNPC::setStrength( uint16_t newStrength )
{
    strength = newStrength;
}

uint16_t CNPC::getStrength() const
{
    return strength;
}

void CNPC::modifyStrength( int16_t strengthModifier )
{
    if ( strengthModifier < 0 && static_cast<uint16_t>(-strengthModifier) > getStrength() )
        // don't modify the max_XXXXX since modifier < maxXXXXX
        std::cout << "Error during modifyStrength." << std::endl;
    else if ( strengthModifier > 0 && (std::numeric_limits<uint16_t>::max() - strengthModifier) > getStrength() )
        setStrength( std::numeric_limits<uint16_t>::max() );
    else
        setStrength( getStrength() + strengthModifier );
}

void CNPC::setDexterity( uint16_t newDexterity )
{
    dexterity = newDexterity;
}

uint16_t CNPC::getDexterity() const
{
    return dexterity;
}

void CNPC::modifyDexterity( int16_t dexterityModifier )
{
    if ( dexterityModifier < 0 && static_cast<uint16_t>(-dexterityModifier) > getDexterity() )
        // don't modify the max_XXXXX since modifier < maxXXXXX
        std::cout << "Error during modifyDexterity." << std::endl;
    else if ( dexterityModifier > 0 && (std::numeric_limits<uint16_t>::max() - dexterityModifier) > getDexterity() )
        setDexterity( std::numeric_limits<uint16_t>::max() );
    else
        setDexterity( getDexterity() + dexterityModifier );
}

void CNPC::setVitality( uint16_t newVitality )
{
    vitality = newVitality;
}

uint16_t CNPC::getVitality() const
{
    return vitality;
}

void CNPC::modifyVitality( int16_t vitalityModifier )
{
    if ( vitalityModifier < 0 && static_cast<uint16_t>(-vitalityModifier) > getVitality() )
        // don't modify the max_XXXXX since modifier < maxXXXXX
        std::cout << "Error during modifyVitality." << std::endl;
    else if ( vitalityModifier > 0 && (std::numeric_limits<uint16_t>::max() - vitalityModifier) > getVitality() )
        setVitality( std::numeric_limits<uint16_t>::max() );
    else
        setVitality( getVitality() + vitalityModifier );
}

void CNPC::setIntellect( uint16_t newIntellect )
{
    intellect = newIntellect;
}

uint16_t CNPC::getIntellect() const
{
    return intellect;
}

void CNPC::modifyIntellect( int16_t intellectModifier )
{
    if ( intellectModifier < 0 && static_cast<uint16_t>(-intellectModifier) > getIntellect() )
        // don't modify the max_XXXXX since modifier < maxXXXXX
        std::cout << "Error during modifyIntellect." << std::endl;
    else if ( intellectModifier > 0 && (std::numeric_limits<uint16_t>::max() - intellectModifier) > getIntellect() )
        setIntellect( std::numeric_limits<uint16_t>::max() );
    else
        setIntellect( getIntellect() + intellectModifier );
}

void CNPC::setWisdom( uint16_t newWisdom )
{
    wisdom = newWisdom;
}

uint16_t CNPC::getWisdom() const
{
    return wisdom;
}

void CNPC::modifyWisdom( int16_t wisdomModifier )
{
    if ( wisdomModifier < 0 && static_cast<uint16_t>(-wisdomModifier) > getWisdom() )
        // don't modify the max_XXXXX since modifier < maxXXXXX
        std::cout << "Error during modifyWisdom." << std::endl;
    else if ( wisdomModifier > 0 && (std::numeric_limits<uint16_t>::max() - wisdomModifier) > getWisdom() )
        setWisdom( std::numeric_limits<uint16_t>::max() );
    else
        setWisdom( getWisdom() + wisdomModifier );
}

void CNPC::setMaxHealth( uint16_t newMaxHealth )
{
    max_health = newMaxHealth;
    current_health = newMaxHealth;
}

uint16_t CNPC::getMaxHealth() const
{
    return max_health;
}

void CNPC::modifyMaxHealth( int16_t maxHealthModifier )
{
    if ( maxHealthModifier < 0 && static_cast<uint16_t>(-maxHealthModifier) > getMaxHealth() ) {
        // don't modify the max_XXXXX since modifier < maxXXXXX
        std::cout << "Error during modifyMaxHealth." << std::endl;
    } else if ( maxHealthModifier > 0 && (std::numeric_limits<uint16_t>::max() - maxHealthModifier) > getMaxHealth() ) {
        setMaxHealth( std::numeric_limits<uint16_t>::max() );
    } else {
        setMaxHealth( getMaxHealth() + maxHealthModifier );
    }
}

void CNPC::setMaxMana( uint16_t newMaxMana )
{
    max_mana = newMaxMana;
    current_mana = newMaxMana;
}

uint16_t CNPC::getMaxMana() const
{
    return max_mana;
}

void CNPC::modifyMaxMana( int16_t maxManaModifier )
{
    if ( maxManaModifier < 0 && static_cast<uint16_t>(-maxManaModifier) > getMaxMana() )
        // don't modify the max_XXXXX since modifier < maxXXXXX
        std::cout << "Error during modifyMaxMana." << std::endl;
    else if ( maxManaModifier > 0 && (std::numeric_limits<uint16_t>::max() - maxManaModifier) > getMaxMana() )
        setMaxMana( std::numeric_limits<uint16_t>::max() );
    else
        setMaxMana( getMaxMana() + maxManaModifier );
}

void CNPC::setMaxEnergy( uint16_t newMaxEnergy )
{
    max_energy = newMaxEnergy;
    current_energy = newMaxEnergy;
}

uint16_t CNPC::getMaxEnergy() const
{
    return max_energy;
}

void CNPC::modifyMaxEnergy( int16_t maxEnergyModifier )
{
    if ( maxEnergyModifier < 0 && static_cast<uint16_t>(-maxEnergyModifier) > getMaxEnergy() )
        // don't modify the max_XXXXX since modifier < maxXXXXX
        std::cout << "Error during modifyMaxEnergy." << std::endl;
    else if ( maxEnergyModifier > 0 && (std::numeric_limits<uint16_t>::max() - maxEnergyModifier) > getMaxEnergy() )
        setMaxEnergy( std::numeric_limits<uint16_t>::max() );
    else
        setMaxEnergy( getMaxEnergy() + maxEnergyModifier );
}

void CNPC::setTexture( CTexture *newTexture )
{
    this->texture = newTexture;
}

CTexture* CNPC::getTexture() const
{
    return this->texture;
}

void CNPC::setLifebar( CTexture *newLifebar )
{
    this->lifebar = newLifebar;
}

CTexture* CNPC::getLifebar() const
{
    return this->lifebar;
}

void CNPC::setMoveTexture( int direction, std::string filename )
{
    if ( texture == NULL )
    {
        texture = new CTexture();
        texture->texture.reserve( 10 );
    }
    texture->LoadIMG( filename, direction );
}

void CNPC::setLifeTexture( std::string filename )
{
    if ( lifebar == NULL )
    {
        lifebar = new  CTexture();
        lifebar->texture.reserve( 2 );
    }
    lifebar->LoadIMG( filename, 1 );
}

// end of Dawn LUA Interface

int CNPC::CheckForCollision(int x_pos, int y_pos) {
    for (unsigned int t=0;t<zone->CollisionMap.size();t++) {
        if ((zone->CollisionMap[t].CR.x+zone->CollisionMap[t].CR.w >= x_pos) && (zone->CollisionMap[t].CR.x <= x_pos)) {
            if ((zone->CollisionMap[t].CR.y+zone->CollisionMap[t].CR.h >= y_pos) && (zone->CollisionMap[t].CR.y <= y_pos)) {
                return 1;
            }
        }
    }
    return 0;
}

int CNPC::CollisionCheck(Direction direction) {
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

void CNPC::MoveUp() {
    if (CollisionCheck(N) == 0) {
        y_pos++;
    }
};

void CNPC::MoveDown() {
    if (CollisionCheck(S) == 0) {
        y_pos--;
    }
};

void CNPC::MoveLeft() {
    if (CollisionCheck(W) == 0) {
        x_pos--;
    }
};

void CNPC::MoveRight() {
    if (CollisionCheck(E) == 0) {
        x_pos++;
    }
};

void CNPC::Move(int direction)
{
    // should probably add Ansgar's movepoint function here so characters move at the
    // correct speed, regardless of framerates.
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

void CNPC::Wander() {
    if (wandering) {
        if (wander_points_left > 0) {
            // checking if character is moving more than the wander_radius. if he does we'll stop him.
            // probably is some other function we could use here that doesnt require as much power... /arnestig
            if (sqrt((pow(x_pos - x_spawn_pos,2)+pow(y_pos - y_spawn_pos,2))) < wander_radius) {
                Move(wander_direction);
                wander_points_left--;
            } else {
                wander_lastframe = SDL_GetTicks();
                wandering = false;
            }
        } else {
            wander_lastframe = SDL_GetTicks();
            wandering = false;
        }
    } else {
        wander_thisframe = SDL_GetTicks();
        if ((wander_thisframe-wander_lastframe) > (wander_every_seconds*1000)) {
            wandering = true;
            wander_points_left = rand() % 50 + 10;  // how far will the NPC wander?
            wander_direction = rand() % 8 + 1;  // random at which direction NPC will go.
            current_texture = wander_direction;
            Move(wander_direction);
        }
    }
};

void CNPC::Die() {
    alive = false;
    respawn_lastframe = SDL_GetTicks();
};

void CNPC::Respawn() {
    if (alive == false && do_respawn == true) {
        respawn_thisframe = SDL_GetTicks();
        if ((respawn_thisframe-respawn_lastframe) > (seconds_to_respawn * 1000)) {
                alive = true;
                x_pos = x_spawn_pos;
                y_pos = y_spawn_pos;
                respawn_thisframe = 0.0f;
                respawn_lastframe = 0.0f;
                current_health = max_health;
                current_mana = max_mana;
                current_energy = max_energy;
                CalculateStats();
        }
    }
};

void CNPC::Draw() {
    if (alive == true) {
        texture->DrawTexture(x_pos,y_pos,current_texture);
    }
    if (in_target == true) {
        DrawLifebar();
    }
};

void CNPC::DrawLifebar() {
    glColor4f(1.0f-life_percentage,life_percentage,0.0f,1.0f);
    DrawingHelpers::mapTextureToRect( lifebar->texture[1].texture,
                                      x_pos, 64*life_percentage,
                                      y_pos+texture->texture[current_texture].height, 8 );
    glColor4f(1.0f,1.0f,1.0f,1.0f);
};

void CNPC::Damage(int amount) {
    if (alive) {
        if (current_health <= amount) {
            current_health = 0;
            Die();
        } else {
            current_health -= amount;
        }
        CalculateStats();
    }
};

void CNPC::Heal(int amount) {
    if (alive) {
        if ((max_health - current_health) <= amount) {
            current_health = max_health;
        } else {
            current_health += amount;
        }
        CalculateStats();
    }
};

void CNPC::CalculateStats() {
     life_percentage = static_cast<float>(current_health) / static_cast<float>(max_health);
     mana_percentage = static_cast<float>(current_mana) / static_cast<float>(max_mana);
     energy_percentage = static_cast<float>(current_energy) / static_cast<float>(max_energy);
};

void CNPC::CheckMouseOver(int _x_pos, int _y_pos) {
    if (((x_pos < _x_pos) && ((x_pos+texture->texture[current_texture].width ) > _x_pos))
    && (( y_pos < _y_pos) && ((y_pos+texture->texture[current_texture].height) > _y_pos))) {
        in_target = true;
    } else {
        in_target = false;
    }
};
