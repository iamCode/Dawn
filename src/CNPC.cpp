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
#include "Player.h"
#include "CAction.h"

extern Player character;

Direction CNPC::GetDirection()
{
	if ( attitudeTowardsPlayer == hostile ) {
		return getDirectionTowards( character.x_pos, character.y_pos );
	}
	if ( wandering ) {
		return WanderDirection;
	} else {
		return MovingDirection;
	}
}

void CNPC::Damage(int amount)
{
	attitudeTowardsPlayer = hostile;
	CCharacter::Damage( amount );
}

void CNPC::Draw()
{
	CalculateStats(); // always calculate the stats of the NPC.
	direction_texture = GetDirectionTexture();
	if (alive == true) {
		texture->DrawTexture(x_pos,y_pos,direction_texture);
	}
}

void CNPC::Respawn()
{
	if (alive == false && do_respawn == true) {
		respawn_thisframe = SDL_GetTicks();
		if ((respawn_thisframe-respawn_lastframe) > (seconds_to_respawn * 1000)) {
			Init( x_spawn_pos, y_spawn_pos );
			alive = true;
			x_pos = x_spawn_pos;
			y_pos = y_spawn_pos;
			respawn_thisframe = 0.0f;
			respawn_lastframe = 0.0f;
			setCurrentHealth( getModifiedMaxHealth() );
			setCurrentMana( getModifiedMaxMana() );
			setCurrentEnergy( getModifiedMaxEnergy() );
			attitudeTowardsPlayer = neutral;
		}
	}
}


void CNPC::Wander()
{
	if (wandering) {
		if (wander_points_left > 0) {
			// checking if character is moving more than the wander_radius. if he does we'll stop him.
			// probably is some other function we could use here that doesnt require as much power... /arnestig
			if (sqrt((pow(x_pos - x_spawn_pos,2)+pow(y_pos - y_spawn_pos,2))) < getWanderRadius() ) {
				wander_points_left--;
			} else {
				wander_lastframe = SDL_GetTicks();
				wandering = false;
				WanderDirection = STOP;
			}
		} else {
			wander_lastframe = SDL_GetTicks();
			wandering = false;
			WanderDirection = STOP;
		}
	} else {
		wander_thisframe = SDL_GetTicks();
		if ((wander_thisframe-wander_lastframe) > (wander_every_seconds*1000)) {
			wandering = true;
			wander_points_left = rand() % 50 + 10;  // how far will the NPC wander?
			WanderDirection = static_cast<Direction>( rand() % 8 + 1 );  // random at which direction NPC will go.
		}
	}
}

void CNPC::Move()
{
	if ( mayDoAnythingAffectingSpellActionWithoutAborting() && attitudeTowardsPlayer == hostile ) {
		// check distance to player
		double distance = sqrt( pow(getXPos() - character.getXPos(),2) + pow(getYPos() - character.getYPos(),2) );
		if ( distance <= 80 ) {
			executeAction( ActionCreation::createAttackAction( const_cast<CCharacter*>( dynamic_cast<CCharacter*>(this)), &character ) ); 
		}
	}
	CCharacter::Move();
}
