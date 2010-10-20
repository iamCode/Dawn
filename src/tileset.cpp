#include "tileset.h"

#include <iostream>
#include <memory>

std::auto_ptr<TileSet> theTileSet;
static TileSet* getTheTileSet()
{
	if ( theTileSet.get() == NULL ) {
		theTileSet = std::auto_ptr<TileSet>( new TileSet() );
	}
	return theTileSet.get();
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
	tiles.push_back( newTile.release() );
	
	return position;
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

namespace EditorInterface
{

TileSet *getTileSet()
{
	return getTheTileSet();
}

} // EditorInterface
