/**
    Copyright (C) 2009,2010,2011  Dawn - 2D roleplaying game

    This file is a part of the dawn-rpg project <https://github.com/frusen/Dawn>.

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

#include "character.h"
#include "interactionpoint.h"
#include "interactionregion.h"
#include "configuration.h"
#include "textwindow.h"
#include "npc.h"
#include "player.h"
#include "shop.h"
#include "item.h"
#include "quest.h"

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
	void giveExpToPlayer( uint16_t experience );
	GeneralRayDamageSpell* createGeneralRayDamageSpell();
	GeneralAreaDamageSpell* createGeneralAreaDamageSpell();
	GeneralBoltDamageSpell* createGeneralBoltDamageSpell();
	GeneralHealingSpell* createGeneralHealingSpell();
	GeneralBuffSpell* createGeneralBuffSpell();
	MeleeDamageAction* createMeleeDamageAction();
	RangedDamageAction* createRangedDamageAction();
	GeneralRayDamageSpell* copySpell( GeneralRayDamageSpell *other );
	GeneralAreaDamageSpell* copySpell( GeneralAreaDamageSpell *other );
	GeneralBoltDamageSpell* copySpell( GeneralBoltDamageSpell *other );
	GeneralHealingSpell* copySpell( GeneralHealingSpell *other );
	GeneralBuffSpell* copySpell( GeneralBuffSpell *other );
	MeleeDamageAction* copySpell( MeleeDamageAction *other );
	RangedDamageAction* copySpell( RangedDamageAction *other );
	void inscribeSpellInPlayerSpellbook( CSpellActionBase *inscribedSpell );
	Quest* addQuest( std::string questName, std::string questDescription );
	void enterZone( std::string zoneName, int enterX, int enterY );
	bool isSavingAllowed();
	void setSavingAllowed( bool savingAllowed );
	void setBackgroundMusic( std::string filename );

	Player *getPlayer();

	// functions used for loading only
	std::string getQuestSaveText();
	std::string getInventorySaveText();
	std::string getSpellbookSaveText();
	void restoreItemInBackpack( Item *item, int inventoryPosX, int inventoryPosY, size_t stackSize = 1 );
	void restoreWieldItem( int slot, Item *item );
	void restoreGroundLootItem( Item *item, int xPos, int yPos );
	void restoreGroundGold( int amount, int xPos, int yPos );
	void setCurrentZone( std::string zoneName );
	std::string getAllZonesSaveText();
	std::string getReenterCurrentZoneText();
	std::string getItemReferenceRestore( CCharacter *character );
	std::string getItemReferenceRestore( InteractionPoint *interactionPoint );
	std::string getItemReferenceRestore( InteractionRegion *interactionRegion );
	std::string getItemReferenceRestore( Shop *shop );
	std::string getItemReferenceRestore( CallIndirection *eventHandler );
	std::string getItemReferenceRestore( Quest *quest );
	std::string getItemReferenceRestore( TextWindow *textWindow );
	std::string getReinitialisationString( std::string fullVarName, Quest *quest );
	std::string getReinitialisationString( std::string fullVarName, void *ignore );
	CCharacter* restoreCharacterReference( std::string zoneName, int posInArray );
	InteractionPoint* restoreInteractionPointReference( std::string zoneName, int posInArray );
	InteractionRegion* restoreInteractionRegionReference( std::string zoneName, int posInArray );
	CallIndirection* restoreEventHandlerReference( std::string zoneName, int posInArray );
	std::string getActionbarSaveText();
	void restoreActionBar( int buttonNr, CSpellActionBase *action );
	void addTextToLogWindow( GLfloat color[], const char *text, ... );
}

#include "tileset.h"

namespace EditorInterface
{
	TileSet *getTileSet();
	void addGroundTile( int posX, int posY, int tile );
	void addEnvironment( int posX, int posY, int posZ, int tile );
	void adjustLastRGBA( double red, double green, double blue, double alpha );
	void adjustLastScale( double scaleX, double scaleY );
	void addCollisionRect( int lrx, int lry, int width, int height );
}
