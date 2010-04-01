/**
    Copyright (C) 2009,2010  Dawn - 2D roleplaying game

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

#include "CNPC.h"
#include "Player.h"
#include "CAction.h"

extern Player character;

CNPC::CNPC ( int _x_spawn_pos, int _y_spawn_pos, int _NPC_id, int _seconds_to_respawn, int _do_respawn, CZone *_zone) {
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
	attitudeTowardsPlayer = Attitude::NEUTRAL;
	chasingPlayer = false;
	markedAsDeleted = false;
}

CNPC::~CNPC()
{
	for ( size_t curEventHandlerNr = 0; curEventHandlerNr < onDieEventHandlers.size(); ++curEventHandlerNr ) {
		delete onDieEventHandlers[ curEventHandlerNr ];
	}
	onDieEventHandlers.clear();
}

void CNPC::setSpawnInfo( int _x_spawn_pos, int _y_spawn_pos, int _seconds_to_respawn, int _do_respawn, CZone *_zone ) {
	x_pos = _x_spawn_pos;
	y_pos = _y_spawn_pos;
	x_spawn_pos = _x_spawn_pos;
	y_spawn_pos = _y_spawn_pos;
	do_respawn = _do_respawn;
	seconds_to_respawn = _seconds_to_respawn;
	zone = _zone;
}

Direction CNPC::GetDirection()
{
	if ( chasingPlayer == true ) {
		return getDirectionTowards( (character.x_pos + character.getWidth()) / 2, (character.y_pos + character.getHeight()) / 2 );
	}
	if ( wandering ) {
		return WanderDirection;
	} else {
		return MovingDirection;
	}
}

void CNPC::Damage(int amount, bool criticalHit)
{
	chasingPlayer = true;
	CCharacter::Damage( amount, criticalHit );
}

void CNPC::Die()
{
    dropItems();
    alive = false;
	respawn_lastframe = SDL_GetTicks();
	onDie();
}

void CNPC::Draw()
{
	CalculateStats(); // always calculate the stats of the NPC.
	cleanupActiveSpells();
	cleanupCooldownSpells();
	direction_texture = GetDirectionTexture();
	ActivityType::ActivityType curActivity = getCurActivity();
	if (alive == true) {
		int drawX = x_pos;
		int drawY = y_pos;
		if ( getUseBoundingBox() ) {
			drawX -= getBoundingBoxX();
			drawY -= getBoundingBoxY();
		}
		texture[ static_cast<size_t>(curActivity) ]->DrawTexture(drawX,drawY,direction_texture);
	}
}

void CNPC::Respawn()
{
	if (alive == false && do_respawn == true) {
		respawn_thisframe = SDL_GetTicks();
		if ((respawn_thisframe-respawn_lastframe) > (seconds_to_respawn * 1000)) {
			alive = true;
			chasingPlayer = false;
			x_pos = x_spawn_pos;
			y_pos = y_spawn_pos;
			respawn_thisframe = 0.0f;
			respawn_lastframe = 0.0f;
			setCurrentHealth( getModifiedMaxHealth() );
			setCurrentMana( getModifiedMaxMana() );
			Init( x_spawn_pos, y_spawn_pos );
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
	double distance = sqrt( pow((getXPos()+getWidth()/2) - (character.getXPos()+character.getWidth()/2),2)
		                       +pow((getYPos()+getHeight()/2) - (character.getYPos()+character.getHeight()/2),2) );
    // if player is inside agro range of NPC, we set NPC to attack mode.
    if ( distance < 200 && getAttitude() == Attitude::HOSTILE )
    {
        chasingPlayer = true;
    }

    if ( mayDoAnythingAffectingSpellActionWithoutAborting() && chasingPlayer == true ) {
		// check distance to player (not exact, but acceptable, need a better function soon...)
		if ( (distance - (((getWidth()+getHeight())/4) + ((character.getWidth()+character.getHeight())/4))) < 20 ) {
			executeAction( ActionCreation::createAttackAction( const_cast<CCharacter*>( dynamic_cast<CCharacter*>(this)), &character ) );
		}
	}

	CCharacter::Move();
}

void CNPC::markAsDeleted()
{
	markedAsDeleted = true;
}
bool CNPC::isMarkedAsDeletable() const
{
	return markedAsDeleted;
}

void CNPC::addOnDieEventHandler( CallIndirection *eventHandler )
{
	onDieEventHandlers.push_back( eventHandler );
}

void CNPC::onDie()
{
	for ( size_t curEventHandlerNr=0; curEventHandlerNr < onDieEventHandlers.size(); ++curEventHandlerNr ) {
		onDieEventHandlers[ curEventHandlerNr ]->call();
	}
}

void CNPC::setAttitude( Attitude::Attitude attitude )
{
	this->attitudeTowardsPlayer = attitude;
}

Attitude::Attitude CNPC::getAttitude() const
{
	return this->attitudeTowardsPlayer;
}




