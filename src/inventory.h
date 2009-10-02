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

#ifndef __INVENTORY_H__
#define __INVENTORY_H__

#include <vector>

class Item;

class InventoryItem
{
	public:
		InventoryItem( Item *item, size_t inventoryPosX, size_t inventoryPosY );
		size_t getInventoryPosX() const;
		size_t getInventoryPosY() const;
		void setInventoryPos( size_t inventoryPosX, size_t inventoryPosY );

		size_t getSizeX() const;
		size_t getSizeY() const;

		Item* getItem() const;

	private:
		Item *item;
		
		size_t inventoryPosX;
		size_t inventoryPosY;
};

class Inventory
{
	public:
		Inventory( size_t sizeX, size_t sizeY );
		~Inventory();
		bool insertItem( Item *item );
		bool hasSufficientSpaceAt( size_t invPosX, size_t invPosY, size_t itemSizeX, size_t itemSizeY ) const;
		
		std::vector<InventoryItem*> getBackpackItems() const;
		
		bool isPositionFree( size_t invPosX, size_t invPosY ) const;
		InventoryItem* getItemAt( size_t invPosX, size_t invPosY );
		
		void insertItemAt( InventoryItem *inventoryItem, size_t invPosX, size_t invPosY );
		bool containsItem( InventoryItem *inventoryItem ) const;
		void removeItem( InventoryItem *inventoryItem );

	private:
		
		size_t sizeX;
		size_t sizeY;
		bool **slotUsed;
		std::vector<InventoryItem*> backpackItems;
};

#endif // __INVENTORY_H__
