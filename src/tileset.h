#ifndef TILESET_H
#define TILESET_H

#include <string>
#include <vector>

namespace TileClassificationType
{
	enum TileClassificationType
	{
		FLOOR,
		WALL,
		MAJORFILL,
		DECORATION
	};
}

namespace AdjacencyType
{
	enum AdjacencyType
	{
		RIGHT,
		LEFT,
		TOP,
		BOTTOM
	};
}

class Tile
{
	public:
		std::string filename;
		TileClassificationType::TileClassificationType tileType;
};

class AdjacencyStruct
{
	public:
		AdjacencyType::AdjacencyType adjacencyType;
		int baseTile;
		int adjacentTile;
};

class TileSet
{
  private:
	std::vector<Tile*> tiles;
	std::vector<AdjacencyStruct*> adjacencyList;

  public:
	// The following functions are in the LUA EditorInterface
	int addTile( std::string filename, TileClassificationType::TileClassificationType tileType );
	void addAdjacency( int tile1, AdjacencyType::AdjacencyType adjacencyType, int tile2 );
	void printTileSet() const;
};

#endif // TILESET_H
