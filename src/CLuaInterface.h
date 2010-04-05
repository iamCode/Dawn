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

#include "CCharacter.h"
#include "interactionpoint.h"
#include "textwindow.h"
#include "CNPC.h"
#include "Player.h"
#include "shop.h"
#include "item.h"

namespace DawnInterface
{
	CCharacter* createNewMobType( std::string typeID );
	CNPC* addMobSpawnPoint( std::string mobID, int x_pos, int y_pos, int respawn_rate, int do_respawn );
	void removeMobSpawnPoint( CNPC *spawnPointToRemove );
	LuaCallIndirection* createEventHandler();
	Item* createNewItem(std::string name,
	                    int sizeX,
	                    int sizeY,
	                    std::string symbolFile,
	                    ItemQuality::ItemQuality itemQuality,
	                    EquipPosition::EquipPosition equipPosition,
	                    ItemType::ItemType itemType,
	                    ArmorType::ArmorType armorType,
	                    WeaponType::WeaponType weaponType );
	void giveItemToPlayer( Item* item );
	GeneralRayDamageSpell* createGeneralRayDamageSpell();
	GeneralBoltDamageSpell* createGeneralBoltDamageSpell();
	GeneralHealingSpell* createGeneralHealingSpell();
	GeneralBuffSpell* createGeneralBuffSpell();
	void inscribeSpellInPlayerSpellbook( CSpell *inscribedSpell );
	void addQuest( std::string questName, std::string questDescription );
	void removeQuest( std::string questName );
	void changeQuestDescription( std::string questName, std::string newDescription );
	std::string getQuestSaveText();
	std::string getInventorySaveText();
	void restoreItemInBackpack( Item *item, size_t inventoryPosX, size_t inventoryPosY );
	void restoreWieldItem( size_t slot, Item *item );
	Player* getPlayer();
}

