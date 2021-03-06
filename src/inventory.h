/* Copyright (C) 2009,2010,2011,2012  Dawn - 2D roleplaying game

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

#ifndef INVENTORY_H
#define INVENTORY_H

#include <vector>
#include "tooltip.h"
#include "item.h"

class Player;

class InventoryItem
{
public:
  InventoryItem( Item* item, size_t inventoryPosX, size_t inventoryPosY, Player* player, InventoryItem* copyFrom = NULL );
  ~InventoryItem();
  size_t getInventoryPosX() const;
  size_t getInventoryPosY() const;
  void setInventoryPos( size_t inventoryPosX, size_t inventoryPosY );
  itemTooltip* getTooltip() const;

  size_t getSizeX() const;
  size_t getSizeY() const;

  size_t getCurrentStackSize() const;
  void setCurrentStackSize( size_t currentStackSize );
  void increaseCurrentStack();
  void decreaseCurrentStack();
  bool isItemStackFull() const;

  void copyAttributes( InventoryItem *copyFrom );
  Item* getItem() const;
  bool canPlayerUseItem() const;


private:
  Item* item;
  Player* player;
  itemTooltip* tooltip;

  size_t currentStackSize;

  size_t inventoryPosX;
  size_t inventoryPosY;
};

class Inventory
{
public:
  Inventory( size_t sizeX, size_t sizeY, Player* player );
  ~Inventory();
  bool insertItem( Item* item, InventoryItem* oldInventoryItem = NULL );
  bool hasSufficientSpaceAt( size_t invPosX, size_t invPosY, size_t itemSizeX, size_t itemSizeY ) const;
  bool hasSufficientSpaceWithExchangeAt( size_t inventoryPosX, size_t inventoryPosY, size_t itemSizeX, size_t itemSizeY );
  bool stackItemIfPossible( Item* item, InventoryItem* itemToStack ) const;

  std::vector<InventoryItem*> getEquippedItems() const;
  std::vector<InventoryItem*> getBackpackItems() const;

  void wieldItemAtSlot( ItemSlot::ItemSlot slotToUse, InventoryItem *item );
  InventoryItem* getItemAtSlot( ItemSlot::ItemSlot slotToUse );

  bool isPositionFree( size_t invPosX, size_t invPosY ) const;
  InventoryItem* getItemAt( size_t invPosX, size_t invPosY );
  std::vector<InventoryItem*> getIdenticalItemsFromBackpack( Item* item ) const;
  bool doesItemExistInBackpack( Item* item, int quantity ) const;

  bool isWieldingTwoHandedWeapon() const;
  WeaponType::WeaponType getWeaponTypeBySlot( ItemSlot::ItemSlot itemSlot) const;

  InventoryItem* insertItemWithExchangeAt( InventoryItem* inventoryItem, size_t invPosX, size_t invPosY );
  bool containsItem( InventoryItem* inventoryItem ) const;
  void removeItem( InventoryItem* inventoryItem );
  void removeItem( Item* item );
  std::string getReloadText();

  void clear();

  static EquipPosition::EquipPosition getEquipType( ItemSlot::ItemSlot itemSlot );

private:
  void insertItemAt( InventoryItem* inventoryItem, size_t invPosX, size_t invPosY );
  InventoryItem* findFirstBlockingItem( size_t inventoryPosX, size_t inventoryPosY, size_t itemSizeX, size_t itemSizeY );

  size_t sizeX;
  size_t sizeY;
  bool** slotUsed;
  Player* player;
  std::vector<InventoryItem*> backpackItems;
  InventoryItem** equippedItems;
};

#endif
