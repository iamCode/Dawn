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

#ifndef __CNPC_H__
#define __CNPC_H__

#include "CCharacter.h"

class CNPC : public CCharacter
{
	private:
		enum { friendly, neutral, hostile } attitudeTowardsPlayer;
		std::vector<sLootTable> lootTable;
	public:

		CNPC ( int _x_spawn_pos, int _y_spawn_pos, int _NPC_id, int _seconds_to_respawn, int _do_respawn, CZone *_zone) {
			Init( x_spawn_pos, y_spawn_pos );
			alive = true;
			current_texture = 1; // this will be altered later on to draw what animation frame we want to draw.
			respawn_thisframe = 0.0f;
			respawn_lastframe = 0.0f; // helps us count when to respawn the NPC.
			wander_thisframe = 0.0f;
			wander_lastframe = 0.0f; // helping us decide when the mob will wander.
			wander_every_seconds = 1; // this mob wanders every 1 seconds.
			wandering = false;
			MovingDirection = STOP;

			remainingMovePoints = 0;
			direction_texture = S;
			attitudeTowardsPlayer = neutral;
		}

		void setSpawnInfo( int _x_spawn_pos, int _y_spawn_pos, int _seconds_to_respawn, int _do_respawn, CZone *_zone ) {
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
		Direction GetDirection();
		void Respawn();
		void Wander();
        void Die();
		void Damage(int amount, bool criticalHit);
};

#endif // __CNPC_H__
