#ifndef TILESET_H
#define TILESET_H

#include <string>
#include <vector>

class CTexture;

namespace TileClassificationType
{
	enum TileClassificationType
	{
		FLOOR,
		ENVIRONMENT,
		SHADOW,
		COUNT
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
		int tileID;
		std::string filename;
		TileClassificationType::TileClassificationType tileType;
		CTexture *texture;
};

struct Point
{
	int x;
	int y;

	Point( int x_=0, int y_=0 )
		: x( x_ ),
		  y( y_ )
	{
	}
};

class AdjacencyStruct
{
	public:
		AdjacencyType::AdjacencyType adjacencyType;
		int baseTile;
		int adjacentTile;
		Point offset;
};

class AdjacencyEquivalenceClass
{
  public:
	std::vector<int> equivalentTiles;
	std::vector<Point> offsets;
	void addEquivalentTile( int tile, int offsetX, int offsetY );
};

class TileSet
{
  private:
	std::vector<Tile*> tiles;
	std::vector<AdjacencyStruct*> adjacencyList;
	std::vector< std::vector<Tile*> > preparedTiles;
	std::vector<AdjacencyEquivalenceClass*> myEquivalenceClasses;

  public:
	TileSet();

	// The following functions are in the LUA EditorInterface
	int addTile( std::string filename, TileClassificationType::TileClassificationType tileType );
	int addTileWithCollisionBox( std::string filename, TileClassificationType::TileClassificationType tileType, int cbx, int cby, int cbw, int cbh );
	void addAdjacency( int tile1, AdjacencyType::AdjacencyType adjacencyType, int tile2, int offsetX, int offsetY );
	AdjacencyEquivalenceClass *createAdjacencyEquivalenceClass();
	void addEquivalenceAdjacency( AdjacencyEquivalenceClass *class1, AdjacencyType::AdjacencyType adjacencyType, AdjacencyEquivalenceClass *class2, int allOffsetX, int allOffsetY );
	void printTileSet() const;
	
	// normal interface
	Tile *getTile( int tileID ) const;
	Tile *getEmptyTile() const;
	size_t numberOfTiles() const;
	void clear();
	std::vector<Tile*> getAllTiles() const;
	std::vector<Tile*> getAllTilesOfType( TileClassificationType::TileClassificationType tileType );
	void getAllAdjacentTiles( Tile *searchTile, std::vector< std::vector<Tile*> > &matchingTiles, std::vector< std::vector<Point> > &matchOffsets ) const;
};

namespace EditorInterface
{
	TileSet *getTileSet();
}
#endif // TILESET_H
