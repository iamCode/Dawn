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

#include "tileset.h"

#include <iostream>
#include <memory>
#include <cassert>
#include "texture.h"

void AdjacencyEquivalenceClass::addEquivalentTile( int tile, int offsetX, int offsetY )
{
	equivalentTiles.push_back( tile );
	offsets.push_back( Point( offsetX, offsetY ) );
}

std::auto_ptr<TileSet> theTileSet;
static TileSet* getTheTileSet()
{
	if ( theTileSet.get() == NULL ) {
		theTileSet = std::auto_ptr<TileSet>( new TileSet() );
	}
	return theTileSet.get();
}

TileSet::TileSet()
{
	preparedTiles.resize( TileClassificationType::COUNT );
	for ( size_t curTileType=0; curTileType < static_cast<size_t>(TileClassificationType::COUNT); ++curTileType ) {
		preparedTiles[ curTileType ] = std::vector<Tile*>();
	}
}

// The following functions are in the LUA EditorInterface
int TileSet::addTile( std::string filename, TileClassificationType::TileClassificationType tileType )
{
	for ( size_t curTileNr=0; curTileNr<tiles.size(); ++curTileNr ) {
		Tile *curTile = tiles[ curTileNr ];
		if ( curTile->filename == filename && curTile->tileType == tileType ) {
			return curTileNr;
		}
	}

	int position = tiles.size();
	std::auto_ptr<Tile> newTile = std::auto_ptr<Tile>( new Tile() );
	newTile->filename = filename;
	newTile->tileType = tileType;
	newTile->tileID = position;
	newTile->texture = new CTexture();
	newTile->texture->LoadIMG( filename, 0 );
	Tile *tilePtr = newTile.release();
	tiles.push_back( tilePtr );
	preparedTiles[ static_cast<size_t>(tileType) ].push_back( tilePtr );

	return position;
}

int TileSet::addTileWithCollisionBox( std::string filename, TileClassificationType::TileClassificationType tileType, int cbx, int cby, int cbw, int cbh ) {
	int newPos = addTile( filename, tileType );
	Tile *newTile = tiles[ newPos ];
	newTile->texture->getTexture(0).contains_collision_box = true;
	newTile->texture->getTexture(0).collision_box.x = cbx;
	newTile->texture->getTexture(0).collision_box.y = cby;
	newTile->texture->getTexture(0).collision_box.w = cbw;
	newTile->texture->getTexture(0).collision_box.h = cbh;

	return newPos;
}

void TileSet::addAdjacency( int tile1, AdjacencyType::AdjacencyType adjacencyType, int tile2, int offsetX, int offsetY )
{
	if ( adjacencyType == AdjacencyType::LEFT ) {
		addAdjacency( tile2, AdjacencyType::RIGHT, tile1, -offsetX, -offsetY );
		return;
	}
	if ( adjacencyType == AdjacencyType::BOTTOM ) {
		addAdjacency( tile2, AdjacencyType::TOP, tile1, -offsetX, -offsetY );
		return;
	}

	for ( size_t curAdjacencyNr=0; curAdjacencyNr<adjacencyList.size(); ++curAdjacencyNr ) {
		AdjacencyStruct *curAdjacency = adjacencyList[ curAdjacencyNr ];
		if ( curAdjacency->baseTile == tile1 && curAdjacency->adjacencyType == adjacencyType && curAdjacency->adjacentTile == tile2 ) {
			return;
		}
	}

	std::auto_ptr<AdjacencyStruct> newAdjacency = std::auto_ptr<AdjacencyStruct>( new AdjacencyStruct() );
	newAdjacency->baseTile = tile1;
	newAdjacency->adjacentTile = tile2;
	newAdjacency->adjacencyType = adjacencyType;
	newAdjacency->offset = Point( offsetX, offsetY );
	adjacencyList.push_back( newAdjacency.release() );
}

AdjacencyEquivalenceClass *TileSet::createAdjacencyEquivalenceClass()
{
	myEquivalenceClasses.push_back( new AdjacencyEquivalenceClass() );
	return myEquivalenceClasses[ myEquivalenceClasses.size() - 1 ];
}

void TileSet::addEquivalenceAdjacency( AdjacencyEquivalenceClass *class1, AdjacencyType::AdjacencyType adjacencyType, AdjacencyEquivalenceClass *class2, int allOffsetX, int allOffsetY )
{
	std::vector<int> &firstTiles = class1->equivalentTiles;
	std::vector<int> &secondTiles = class2->equivalentTiles;
	for ( size_t curFirstTileIndex=0; curFirstTileIndex<firstTiles.size(); ++curFirstTileIndex ) {
		for ( size_t curSecondTileIndex=0; curSecondTileIndex<secondTiles.size(); ++curSecondTileIndex ) {
			addAdjacency( firstTiles[curFirstTileIndex], adjacencyType, secondTiles[curSecondTileIndex],
			              class2->offsets[curSecondTileIndex].x - class1->offsets[curFirstTileIndex].x + allOffsetX,
			              class2->offsets[curSecondTileIndex].y - class1->offsets[curFirstTileIndex].y + allOffsetY );
		}
	}
}

void TileSet::printTileSet() const
{
	std::cout << "-- all " << tiles.size() << " Tiles in TileSet" << std::endl;
	for ( size_t curTileNr=0; curTileNr<tiles.size(); ++curTileNr ) {
		Tile *curTile = tiles[ curTileNr ];
		std::cout << curTileNr << ": " << curTile->filename << std::endl;
	}
	std::cout << std::endl;
	std::cout << "-- all " << adjacencyList.size() << " Adjacencies in TileSet" << std::endl;
	for ( size_t curAdjacencyNr=0; curAdjacencyNr<adjacencyList.size(); ++curAdjacencyNr ) {
		AdjacencyStruct *curAdjacency = adjacencyList[ curAdjacencyNr ];
		Tile *startTile = tiles[ curAdjacency->baseTile ];
		Tile *endTile = tiles[ curAdjacency->adjacentTile ];
		if ( curAdjacency->adjacencyType == AdjacencyType::RIGHT ) {
			std::cout << startTile->filename << " [on right] <--> [on left] " << endTile->filename << std::endl;
		} else {
			std::cout << startTile->filename << " [on top] <--> [on bottom] " << endTile->filename << std::endl;
		}
	}
	std::cout << std::endl;
}

Tile* TileSet::getTile( int tileID ) const
{
	return tiles[ tileID ];
}

Tile* TileSet::getEmptyTile() const
{
	return tiles[0];
}

size_t TileSet::numberOfTiles() const
{
	return tiles.size();
}

void TileSet::clear()
{
	tiles.clear();
}

std::vector<Tile*> TileSet::getAllTiles() const
{
	return tiles;
}

std::vector<Tile*> TileSet::getAllTilesOfType( TileClassificationType::TileClassificationType tileType )
{
	// NOTE: For optimization we could (and should) precache a vector for each type here
	return preparedTiles[ static_cast<size_t>( tileType ) ];
}

void TileSet::getAllAdjacentTiles( Tile *searchTile, std::vector< std::vector<Tile*> > &result, std::vector< std::vector<Point> > &matchOffsets ) const
{
	result.clear();
	result.resize( 4 );
	matchOffsets.clear();
	matchOffsets.resize( 4 );

	for ( size_t curAdjacencyNr=0; curAdjacencyNr<adjacencyList.size(); ++curAdjacencyNr ) {
		AdjacencyStruct *curAdjacency = adjacencyList[ curAdjacencyNr ];
		if ( tiles[ curAdjacency->baseTile ] == searchTile ) {
			if ( curAdjacency->adjacencyType == AdjacencyType::RIGHT ) {
				result[ AdjacencyType::RIGHT ].push_back( tiles[ curAdjacency->adjacentTile ] );
				matchOffsets[ AdjacencyType::RIGHT ].push_back( Point( curAdjacency->offset.x, curAdjacency->offset.y ) );
			} else {
				assert( curAdjacency->adjacencyType == AdjacencyType::TOP );
				result[ AdjacencyType::TOP ].push_back( tiles[ curAdjacency->adjacentTile ] );
				matchOffsets[ AdjacencyType::TOP ].push_back( Point( curAdjacency->offset.x, curAdjacency->offset.y ) );
			}
		}
		if ( tiles[ curAdjacency->adjacentTile ] == searchTile ) {
			if ( curAdjacency->adjacencyType == AdjacencyType::RIGHT ) {
				result[ AdjacencyType::LEFT ].push_back( tiles[ curAdjacency->baseTile ] );
				matchOffsets[ AdjacencyType::LEFT ].push_back( Point( -curAdjacency->offset.x, -curAdjacency->offset.y ) );
			} else {
				assert( curAdjacency->adjacencyType == AdjacencyType::TOP );
				result[ AdjacencyType::BOTTOM ].push_back( tiles[ curAdjacency->baseTile ] );
				matchOffsets[ AdjacencyType::BOTTOM ].push_back( Point( -curAdjacency->offset.x, -curAdjacency->offset.y ) );
			}
		}
	}
}

namespace EditorInterface
{

TileSet *getTileSet()
{
	return getTheTileSet();
}

} // EditorInterface
