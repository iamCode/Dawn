/**
    Copyright (C) 2009,2010,2011  Dawn - 2D roleplaying game

    This file is a part of the dawn-rpg project <http://sourceforge.net/projects/dawn-rpg/>.

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
#include "callindirection.h"

namespace Attitude
{
	enum Attitude
	{
		FRIENDLY,
		NEUTRAL,
		HOSTILE
	};
}

class CNPC : public CCharacter
{
	private:
		Attitude::Attitude attitudeTowardsPlayer;
		std::vector<sLootTable> lootTable;
		std::vector<CallIndirection*> onDieEventHandlers;
		bool markedAsDeleted;
		bool chasingPlayer;
	public:

		CNPC ( int _x_spawn_pos, int _y_spawn_pos, int _NPC_id, int _seconds_to_respawn, int _do_respawn );
		~CNPC();

		void setSpawnInfo( int _x_spawn_pos, int _y_spawn_pos, int _seconds_to_respawn, int _do_respawn );

		void Draw();
		void chasePlayer( CCharacter *player );
		void Move();
		Direction GetDirection();
		void Respawn();
		void Wander();
        void Die();
		virtual bool canBeDamaged() const;
		void Damage(int amount, bool criticalHit);

		void markAsDeleted();
		bool isMarkedAsDeletable() const;

		void addOnDieEventHandler( CallIndirection *eventHandler );
		bool hasOnDieEventHandler() const;

		void onDie();
		void setAttitude( Attitude::Attitude attitude );
		Attitude::Attitude getAttitude() const;

        /// \brief this function is used when saving the current state of the NPCs in a savegame.
		std::string getLuaSaveText() const;

		/// \brief this function is used when saving the NPCs in the editor.
        std::string getLuaEditorSaveText() const;
};

#endif // __CNPC_H__
