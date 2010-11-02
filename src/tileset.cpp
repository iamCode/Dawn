#include "tileset.h"

#include <iostream>
#include <memory>
#include <cassert>
#include "CTexture.h"

void AdjacencyEquivalenceClass::addEquivalentTile( int tile )
{
	equivalentTiles.push_back( tile );
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
	newTile->texture->texture.resize( 1 );
	newTile->texture->LoadIMG( filename, 0 );
	Tile *tilePtr = newTile.release();
	tiles.push_back( tilePtr );
	preparedTiles[ static_cast<size_t>(tileType) ].push_back( tilePtr );
	
	return position;
}

int TileSet::addTileWithCollisionBox( std::string filename, TileClassificationType::TileClassificationType tileType, int cbx, int cby, int cbw, int cbh ) {
	int newPos = addTile( filename, tileType );
	Tile *newTile = tiles[ newPos ];
	newTile->texture->texture[0].contains_collision_box = true;
	newTile->texture->texture[0].collision_box.x = cbx;
	newTile->texture->texture[0].collision_box.y = cby;
	newTile->texture->texture[0].collision_box.w = cbw;
	newTile->texture->texture[0].collision_box.h = cbh;
	
	return newPos;
}

void TileSet::addAdjacency( int tile1, AdjacencyType::AdjacencyType adjacencyType, int tile2 )
{
	if ( adjacencyType == AdjacencyType::LEFT ) {
		addAdjacency( tile2, AdjacencyType::RIGHT, tile1 );
		return;
	}
	if ( adjacencyType == AdjacencyType::BOTTOM ) {
		addAdjacency( tile2, AdjacencyType::TOP, tile1 );
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
	adjacencyList.push_back( newAdjacency.release() );
}

AdjacencyEquivalenceClass *TileSet::createAdjacencyEquivalenceClass()
{
	myEquivalenceClasses.push_back( new AdjacencyEquivalenceClass() );
	return myEquivalenceClasses[ myEquivalenceClasses.size() - 1 ];
}

void TileSet::addEquivalenceAdjacency( AdjacencyEquivalenceClass *class1, AdjacencyType::AdjacencyType adjacencyType, AdjacencyEquivalenceClass *class2 )
{
	std::vector<int> &firstTiles = class1->equivalentTiles;
	std::vector<int> &secondTiles = class2->equivalentTiles;
	for ( size_t curFirstTileIndex=0; curFirstTileIndex<firstTiles.size(); ++curFirstTileIndex ) {
		for ( size_t curSecondTileIndex=0; curSecondTileIndex<secondTiles.size(); ++curSecondTileIndex ) {
			addAdjacency( firstTiles[curFirstTileIndex], adjacencyType, secondTiles[curSecondTileIndex] );
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

std::vector< std::vector<Tile*> > TileSet::getAllAdjacentTiles( Tile *searchTile ) const
{
	std::vector< std::vector<Tile*> > result;
	result.resize( 4 );
	
	for ( size_t curAdjacencyNr=0; curAdjacencyNr<adjacencyList.size(); ++curAdjacencyNr ) {
		AdjacencyStruct *curAdjacency = adjacencyList[ curAdjacencyNr ];
		if ( tiles[ curAdjacency->baseTile ] == searchTile ) {
			if ( curAdjacency->adjacencyType == AdjacencyType::RIGHT ) {
				result[ AdjacencyType::RIGHT ].push_back( tiles[ curAdjacency->adjacentTile ] );
			} else {
				assert( curAdjacency->adjacencyType == AdjacencyType::TOP );
				result[ AdjacencyType::TOP ].push_back( tiles[ curAdjacency->adjacentTile ] );
			}
		} else if ( tiles[ curAdjacency->adjacentTile ] == searchTile ) {
			if ( curAdjacency->adjacencyType == AdjacencyType::RIGHT ) {
				result[ AdjacencyType::LEFT ].push_back( tiles[ curAdjacency->baseTile ] );
			} else {
				assert( curAdjacency->adjacencyType == AdjacencyType::TOP );
				result[ AdjacencyType::BOTTOM ].push_back( tiles[ curAdjacency->baseTile ] );
			}
		}
	}
	
	return result;
}

namespace EditorInterface
{

TileSet *getTileSet()
{
	return getTheTileSet();
}

} // EditorInterface
