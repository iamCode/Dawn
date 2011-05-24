#include "a_star.h"

#include <iostream>
#include <cassert>
#include <cmath>
#include <limits>
#include <list>

#include <SDL/SDL.h> // just for ticks...

class Region
{
  public:
	int x;
	int y;
	int w;
	int h;

	Region( int x_, int y_, int w_, int h_ )
		: x(x_), y(y_), w(w_), h(h_)
	{
	}
	
	
};

class GraphNode;
class RegionChangeNode;

class RegionChange
{
  public:
	bool horizontal;
	int start;
	int size;
	int otherCoordinate;
	GraphNode *regionOne;
	GraphNode *regionTwo;
	
	RegionChangeNode *changeNode;
	
	std::vector<RegionChange*> adjacentChanges;
	
	RegionChange( bool horizontal_, int start_, int size_, int otherCoordinate_, GraphNode *regionOne_, GraphNode *regionTwo_ )
		: horizontal( horizontal_ ),
	      start( start_ ),
	      size( size_ ),
	      otherCoordinate( otherCoordinate_ ),
	      regionOne( regionOne_ ),
	      regionTwo( regionTwo_ ),
	      changeNode( NULL )
	{
	}
};

class GraphNode
{
  public:
	Region *region;
	std::vector<RegionChange*> openings;
	size_t label;
	
	GraphNode( Region *region_)
		: region( region_ )
	{
	}
	
	void addOpening( RegionChange *newOpening )
	{
		openings.push_back( newOpening );
	}
};

void connectNodes( GraphNode *first, GraphNode*second, bool horizontal, int start, int size, int otherCoordinate )
{
	RegionChange *firstToSecond = new RegionChange( horizontal, start, size, otherCoordinate, first, second );
	first->addOpening( firstToSecond );
	second->addOpening( firstToSecond );
}

std::vector<GraphNode*> createConnectionGraph( std::vector<Region*> &regionDecomposition )
{
	std::vector<GraphNode*> connectionGraph( regionDecomposition.size() );
	for ( size_t curRegionNr=0; curRegionNr<regionDecomposition.size(); ++curRegionNr ) {
		connectionGraph[ curRegionNr ] = new GraphNode( regionDecomposition[ curRegionNr ] );
	}
	
	for ( size_t firstRegionNr=0; firstRegionNr<regionDecomposition.size(); ++firstRegionNr ) {
		for ( size_t secondRegionNr=firstRegionNr+1; secondRegionNr<regionDecomposition.size(); ++secondRegionNr ) {
			Region *firstRegion = regionDecomposition[ firstRegionNr ];
			Region *secondRegion = regionDecomposition[ secondRegionNr ];
			if ( firstRegion->x == secondRegion->x+secondRegion->w || firstRegion->x+firstRegion->w == secondRegion->x ) {
				int minUpper = std::min( firstRegion->y+firstRegion->h, secondRegion->y+secondRegion->h );
				int maxLower = std::max( firstRegion->y, secondRegion->y );
				int otherCoordinate = firstRegion->x;
				if ( firstRegion->x != secondRegion->x+secondRegion->w ) {
					otherCoordinate = secondRegion->x;
				}
				if ( maxLower <= minUpper ) {
					connectNodes( connectionGraph[ firstRegionNr ], connectionGraph[ secondRegionNr ], false, maxLower, minUpper-maxLower+1, otherCoordinate );
				}
			}
			else if ( firstRegion->y == secondRegion->y+secondRegion->h || firstRegion->y+firstRegion->h == secondRegion->y ) {
				int minRight = std::min( firstRegion->x+firstRegion->w, secondRegion->x+secondRegion->w );
				int maxLeft = std::max( firstRegion->x, secondRegion->x );
				int otherCoordinate = firstRegion->y;
				if ( firstRegion->y != secondRegion->y+secondRegion->h ) {
					otherCoordinate = secondRegion->y;
				}
				if ( maxLeft <= minRight ) {
					connectNodes( connectionGraph[ firstRegionNr ], connectionGraph[ secondRegionNr ], true, maxLeft, minRight-maxLeft+1, otherCoordinate );
				}
			}
		}
	}
	
	return connectionGraph;
}

class RegionChangeEdge;

class RegionChangeNode
{
  public:
	RegionChange *change;
	std::vector<RegionChangeEdge*> neighbourChanges;
	bool visited;
	size_t distance;
	
	RegionChangeNode( RegionChange *change_ )
		: change( change_ ),
	      neighbourChanges(),
	      visited( false )
	{
	}
	
	void addNeighbour( RegionChangeEdge *neighbour )
	{
		neighbourChanges.push_back( neighbour );
	}
	
	void addAllNeighboursViaRegion( GraphNode *region );
	
	void addAllNeighbours()
	{
		addAllNeighboursViaRegion( change->regionOne );
		addAllNeighboursViaRegion( change->regionTwo );
	}
};

std::ostream& operator << ( std::ostream &input, const RegionChangeNode &output )
{
	Point p;
	RegionChange *change = output.change;
	if ( change->horizontal ) {
		p.x = change->start + change->size/2;
		p.y = change->otherCoordinate;
	} else {
		p.x = change->otherCoordinate;
		p.y = change->start + change->size/2;
	}
	input << "(" << p.x << ", " << p.y << ")";
	return input;
}

class RegionChangeEdge
{
  public:
	RegionChangeNode *one;
	RegionChangeNode *two;
	size_t distance;
	
	RegionChangeEdge( RegionChangeNode *one_, RegionChangeNode *two_ )
		: one( one_ ), two( two_ )
	{
		size_t x1, x2, y1, y2;
		if ( one->change->horizontal )
		{
			x1 = one->change->start + one->change->size / 2;
			y1 = one->change->otherCoordinate;
		}
		else
		{
			x1 = one->change->otherCoordinate;
			y1 = one->change->start + one->change->size / 2;
		}
		if ( two->change->horizontal )
		{
			x2 = two->change->start + two->change->size / 2;
			y2 = two->change->otherCoordinate;
		}
		else
		{
			x2 = two->change->otherCoordinate;
			y2 = two->change->start + two->change->size / 2;
		}
		distance = std::sqrt( ((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2)) );
		if ( distance == 0 ) {
			distance = 1;
		}
	}
	
	RegionChangeNode *otherEnd( RegionChangeNode *oneEnd )
	{
		// note: no check that this really is an end...
		if ( oneEnd == one ) {
			return two;
		} else {
			return one;
		}
	}
};

void RegionChangeNode::addAllNeighboursViaRegion( GraphNode *region )
{
	for ( size_t curAdjacencyNr=0; curAdjacencyNr<region->openings.size(); ++curAdjacencyNr ) {
		RegionChangeNode *other = region->openings[ curAdjacencyNr ]->changeNode;
		if ( ! other->visited ) {
			RegionChangeEdge *edge = new RegionChangeEdge( this, other );
			addNeighbour( edge );
			other->addNeighbour( edge );
		}
	}
}


std::vector<RegionChangeNode*> createRegionChangeGraph( std::vector<GraphNode*> &connectionGraph )
{
	std::vector<RegionChangeNode*> allOpenings;
	
	for ( size_t curRegionNr=0; curRegionNr<connectionGraph.size(); ++curRegionNr ) {
		GraphNode *curNode = connectionGraph[ curRegionNr ];
		for ( size_t curConnectionNr=0; curConnectionNr<curNode->openings.size(); ++curConnectionNr ) {
			RegionChange *curOpening = curNode->openings[ curConnectionNr ];
			if ( curOpening->changeNode == NULL ) {
				curOpening->changeNode = new RegionChangeNode( curOpening );
				allOpenings.push_back( curOpening->changeNode );
			}
		}
	}
	
	for ( size_t curOpeningNr=0; curOpeningNr<allOpenings.size(); ++curOpeningNr ) {
		RegionChangeNode *curOpening = allOpenings[ curOpeningNr ];
		// add all adjacent connections via regionOne
		curOpening->visited = true;
		curOpening->addAllNeighbours();
	}
	
	return allOpenings;
}

std::vector<Region*> addObstacles()
{
	std::vector<Region*> resultVector;
#define EditorInterface resultVector
#define addCollisionRect(x,y,w,h) push_back( new Region( x, y, w, h ) );
	#include "../data/zone1.collision.lua"
#undef EditorInterface
#undef addCollisionRect
	return resultVector;
}

std::vector<Region*> simpleObstacles()
{
	std::vector<Region*> simpleObs;
	simpleObs.push_back( new Region( -10, -10, 40, 20 ) );
	simpleObs.push_back( new Region( -11, -100, 10, 200 ) );
	simpleObs.push_back( new Region( 80, -100, 10, 200 ) );
	return simpleObs; 
}

std::vector<Region*> allObstacles;

bool hasIntersection( int r1_l, int r1_r, int r1_b, int r1_t, int r2_l, int r2_r, int r2_b, int r2_t )
{
	return ( ! ( (r1_t < r2_b) || (r1_b > r2_t ) || (r1_l > r2_r) || (r1_r < r2_l) ) );
}

bool hasTrueIntersection( int r1_l, int r1_r, int r1_b, int r1_t, int r2_l, int r2_r, int r2_b, int r2_t )
{
	return ( ! ( (r1_t <= r2_b) || (r1_b >= r2_t ) || (r1_l >= r2_r) || (r1_r <= r2_l) ) );
}

bool isFree( int px, int py, int w, int h )
{
	for (unsigned int t=0;t<allObstacles.size();t++) {
		int other_l = allObstacles[t]->x, other_r = allObstacles[t]->x+allObstacles[t]->w;
		int other_b = allObstacles[t]->y, other_t = allObstacles[t]->y+allObstacles[t]->h;
		if ( hasIntersection( other_l, other_r, other_b, other_t,
			              px, px+w, py, py+h )) {
			return false;
		}
	}

	return true;
}

// note: each obstacle is made larger on the bottom-left corner by addWidth and addHeight
std::vector<Region*> createArrayOfFreeRegions( std::vector<Region*> obstacles, int addWidth, int addHeight )
{
	std::vector<Region*> createdRegions;
	// create an initial region
	createdRegions.push_back( new Region(-10000, -10000, 20000, 20000 ) );
	
	unsigned long totalObstacleSize = 0;
	unsigned long totalRegionSize = 0;
	
	for ( size_t curObstacleNr=0; curObstacleNr<obstacles.size(); ++curObstacleNr ) {
		Region *curObstacle = obstacles[curObstacleNr];
		
		totalObstacleSize += (static_cast<unsigned long>(curObstacle->w+addWidth))*(static_cast<unsigned long>(curObstacle->h+addHeight));
		
		size_t numRegions = createdRegions.size();
		std::vector<size_t> deleteRegions;
		for ( size_t curRegionNr=0; curRegionNr<numRegions; ++curRegionNr ) {
			Region *curRegion = createdRegions[curRegionNr];
			if ( hasTrueIntersection( curRegion->x, curRegion->x+curRegion->w, curRegion->y, curRegion->y+curRegion->h,
			                      curObstacle->x-addWidth, curObstacle->x+curObstacle->w, curObstacle->y-addHeight, curObstacle->y+curObstacle->h)) {
				// find position of obstacle within region
				bool needLeft = ( curRegion->x < curObstacle->x-addWidth );
				bool needRight = ( curRegion->x+curRegion->w > curObstacle->x+curObstacle->w );
				bool needBottom = ( curRegion->y < curObstacle->y-addHeight );
				bool needTop = ( curRegion->y+curRegion->h > curObstacle->y + curObstacle->h );
				
				deleteRegions.push_back( curRegionNr );
				if ( needLeft ) {
					createdRegions.push_back( new Region( curRegion->x, curRegion->y, curObstacle->x-addWidth-curRegion->x, curRegion->h ) );
				}
				if ( needRight ) {
					createdRegions.push_back( new Region( curObstacle->x + curObstacle->w, curRegion->y, curRegion->x+curRegion->w-curObstacle->x-curObstacle->w, curRegion->h) );
				}
				if ( needBottom ) {
					createdRegions.push_back( new Region( std::max(curRegion->x, curObstacle->x-addWidth), curRegion->y,
														   std::min(curRegion->x+curRegion->w, curObstacle->x+curObstacle->w)-std::max(curRegion->x, curObstacle->x-addWidth), curObstacle->y-addHeight-curRegion->y ) );
				}
				if ( needTop ) {
					createdRegions.push_back( new Region( std::max(curRegion->x, curObstacle->x-addWidth), curObstacle->y+curObstacle->h,
					                                     std::min(curRegion->x+curRegion->w, curObstacle->x+curObstacle->w)-std::max(curRegion->x, curObstacle->x-addWidth), curRegion->y+curRegion->h-curObstacle->y-curObstacle->h ) );
				}
			}
		}
		for ( size_t curIndex=0; curIndex<deleteRegions.size(); ++curIndex ) {
			size_t deleteIndex = deleteRegions[ deleteRegions.size()-curIndex-1 ];
			
			delete createdRegions[ deleteIndex ];
			createdRegions[ deleteIndex ] = createdRegions[ createdRegions.size()-1 ];
			createdRegions.resize( createdRegions.size()-1 );
		}
		
	}
	
	return createdRegions;
}

void init_dijkstra( std::vector<RegionChangeNode*> &regionChangeGraph, RegionChangeNode *start, std::list<RegionChangeNode*> &distanceQueue )
{
	distanceQueue.push_back( start );
	for ( size_t curNodeNr=0; curNodeNr<regionChangeGraph.size(); ++curNodeNr ) {
		regionChangeGraph[curNodeNr]->distance = std::numeric_limits<size_t>::max();
		regionChangeGraph[curNodeNr]->visited = false;
		if ( regionChangeGraph[curNodeNr] != start ) {
			distanceQueue.push_back( regionChangeGraph[curNodeNr] );
		}
	}	
	start->distance = 0;
}

void distance_update( std::list<RegionChangeNode*> &distanceQueue, RegionChangeNode *curVisited, RegionChangeNode *curChecked, RegionChangeEdge *curEdge )
{
	size_t distanceOverCurrent = curVisited->distance + curEdge->distance;
	if ( distanceOverCurrent < curChecked->distance ) {
		curChecked->distance = distanceOverCurrent;
	}
	// re-sort current node to a position where it belongs in the node-array
	RegionChangeNode* tmp = NULL;
	bool foundPos = false;
	for ( std::list<RegionChangeNode*>::iterator it=distanceQueue.begin(); it!=distanceQueue.end(); ++it ) {
		RegionChangeNode *curNode = *it;
		if ( (! foundPos) && curNode->distance > curChecked->distance ) {
			tmp = curChecked;
			foundPos = true;
		}
		
		if ( foundPos ) {
			*it = tmp;
			tmp = curNode;
		}
		
		if ( curNode == curChecked ) {
			break;
		}
	}
}
  
void pathfind_dijkstra( std::vector<RegionChangeNode*> &regionChangeGraph, RegionChangeNode *start, RegionChangeNode *end )
{
	std::list<RegionChangeNode*> distanceQueue;
	init_dijkstra( regionChangeGraph, start,  distanceQueue);
	while ( distanceQueue.size() > 0 ) {
		RegionChangeNode* curNode = distanceQueue.front();
		if ( curNode == end ) {
			std::cout << "end found, distance: " << curNode->distance << std::endl;
			break;
		}
		distanceQueue.pop_front();
		curNode->visited = true;
		
		for ( size_t curEdgeNr=0; curEdgeNr<curNode->neighbourChanges.size(); ++curEdgeNr ) {
			RegionChangeEdge *curEdge = curNode->neighbourChanges[curEdgeNr];
			RegionChangeNode *otherEnd = curEdge->otherEnd( curNode );
			if ( ! otherEnd->visited ) {
				distance_update( distanceQueue, curNode, otherEnd, curEdge );
			}
		}
	}
	RegionChangeNode* curNode = end;
	std::cout << *curNode << std::endl;
	while ( curNode != start )
	{
		for ( std::vector<RegionChangeEdge*>::iterator it = curNode->neighbourChanges.begin(); it != curNode->neighbourChanges.end(); ++it ) {
			RegionChangeEdge *curEdge = *it;
			RegionChangeNode *otherEnd = curEdge->otherEnd( curNode );
			if ( otherEnd->distance + curEdge->distance == curNode->distance ) {
				curNode = otherEnd;
				break;
			}
		}
		std::cout << *curNode << std::endl;
	}
}

void dijkstra( std::vector<RegionChangeNode*> &regionChangeGraph, std::vector<GraphNode*> &connectionGraph, Point &start, Point &end )
{
	// find region containing start and end
	GraphNode *startRegion = NULL;
	GraphNode *endRegion = NULL;
	for ( size_t curRegionNr=0; curRegionNr<connectionGraph.size(); ++curRegionNr ) {
		GraphNode *curNode = connectionGraph[ curRegionNr ];
		Region *curRegion = connectionGraph[ curRegionNr ]->region;
		if ( curRegion->x <= start.x && curRegion->x+curRegion->w >= start.x 
		     && curRegion->y <= start.y && curRegion->y+curRegion->h >= start.y ) {
			startRegion = curNode;
			break;
		}
	}
	for ( size_t curRegionNr=0; curRegionNr<connectionGraph.size(); ++curRegionNr ) {
		GraphNode *curNode = connectionGraph[ curRegionNr ];
		Region *curRegion = connectionGraph[ curRegionNr ]->region;
		if ( curRegion->x <= end.x && curRegion->x+curRegion->w >= end.x 
		     && curRegion->y <= end.y && curRegion->y+curRegion->h >= end.y ) {
			endRegion = curNode;
			break;
		}
	}
	
	if ( startRegion == NULL ) {
		std::cout << "start point not valid" << std::endl;
		return;
	}
	if ( endRegion == NULL ) {
		std::cout << "end point not valid" << std::endl;
		return;
	}
	if ( startRegion == endRegion ) {
		std::cout << "startRegion == endRegion. Nothing to do, direct path is free" << std::endl;
		return;
	}
	
	// TODO: Check here whether the two regions are in the same connection part of the graph...
	
	// determine any exit as start node for pathfinding (this should be improved by adding start point to graph)
	RegionChangeNode *startNode = NULL;
	RegionChangeNode *endNode = NULL;
	if ( startRegion->openings.size() > 0 ) {
		startNode = startRegion->openings[0]->changeNode;
	}
	if ( endRegion->openings.size() > 0 ) {
		endNode = endRegion->openings[0]->changeNode;
	}
	
	if ( startNode == NULL ) {
		std::cout << "start region is not connected" << std::endl;
		return;
	}
	if ( endNode == NULL ) {
		std::cout << "end region is not connected" << std::endl;
		return;
	}
	
	std::cout << "start node is in region (" << startRegion->region->x << ", " << startRegion->region->y << ") - ("
			  << startRegion->region->x+startRegion->region->w << ", " << startRegion->region->y+startRegion->region->w << ")" << std::endl;
	std::cout << "end node is in region (" << endRegion->region->x << ", " << endRegion->region->y << ") - ("
			  << endRegion->region->x+endRegion->region->w << ", " << endRegion->region->y+endRegion->region->w << ")" << std::endl;
	
	pathfind_dijkstra( regionChangeGraph, startNode, endNode );
}

int main()
{
	allObstacles = addObstacles();
	//allObstacles = simpleObstacles();

	uint32_t initStart = SDL_GetTicks();
	std::vector<Region*> regionDecomposition = createArrayOfFreeRegions( allObstacles, 64, 64 );
	std::vector<GraphNode*> connectionGraph = createConnectionGraph( regionDecomposition );
	// label regions (for debug output mainly)
	for ( size_t curConnectionNr=0; curConnectionNr<connectionGraph.size(); ++curConnectionNr ) {
		connectionGraph[ curConnectionNr ]->label = curConnectionNr;
	}
	std::vector<RegionChangeNode*> regionChangeGraph = createRegionChangeGraph( connectionGraph );
	// TODO: Connect adjacent regions. This might strongly reduce the number of nodes
	uint32_t initEnd = SDL_GetTicks();
	
	//NEXT: * Generate graph structure
	//      * Generate arrays of connected regions (to reduce pathfinding overhead for non-connected regions)
	//	  * Do pathfinding from every exit in this region to every exit of target region + offsets for reaching targets
	//        (OR: add start and end as nodes and do complete pathfinding node to node, needs copy / modification of graph structure)
	//      * for the start just from nearest exit to nearest exit and if the way goes along different exits of start/target region end the path there
	
	/*
	for ( size_t curRegionNr=0; curRegionNr<regionDecomposition.size(); ++curRegionNr ) {
		Region *curRegion = regionDecomposition[ curRegionNr ];
		std::cout << "free region " << curRegionNr << ": (" << curRegion->x << ", " << curRegion->y << ") - ("
		          << curRegion->x+curRegion->w << ", " << curRegion->y + curRegion->h << ")" << std::endl;
	}
	*/
	/*for ( size_t curNodeNr=0; curNodeNr<connectionGraph.size(); ++curNodeNr ) {
		GraphNode *curNode = connectionGraph[ curNodeNr ];
		for ( size_t curConnectionNr=0; curConnectionNr<curNode->openings.size(); ++curConnectionNr ) {
			RegionChange *curConnection = curNode->openings[ curConnectionNr ];
			std::cout << "connection between regions " << curConnection->regionOne->label << " and " << curConnection->regionTwo->label << std::endl; 			
		}
	}*/
	
	/*
	size_t equalSize = 0;
	for ( size_t curOpeningNr=0; curOpeningNr<regionChangeGraph.size(); ++curOpeningNr ) {
		RegionChangeNode* curOpening = regionChangeGraph[ curOpeningNr ];
		if ( curOpening->change->horizontal && curOpening->change->regionOne->region->x == curOpening->change->regionTwo->region->x
											&& curOpening->change->regionOne->region->w == curOpening->change->regionTwo->region->w ) {
			equalSize++;
		}
		else if ( (!curOpening->change->horizontal) && curOpening->change->regionOne->region->y == curOpening->change->regionTwo->region->y
													&& curOpening->change->regionOne->region->h == curOpening->change->regionTwo->region->h ) {
			equalSize++;
		}
		for ( size_t curRegionConnectionNr=0; curRegionConnectionNr<curOpening->neighbourChanges.size(); ++curRegionConnectionNr ) {
			RegionChangeEdge *curRegionConnection = curOpening->neighbourChanges[ curRegionConnectionNr ];
			RegionChangeNode *other = curRegionConnection->two;
			if ( other == curOpening ) {
				other = curRegionConnection->one;
			}
			std::cout << "(" << curOpening->change->regionOne->label << "->" << curOpening->change->regionTwo->label << ") -> "
			          << "(" << other->change->regionOne->label << "->" << other->change->regionTwo->label << ") : "
			          << curRegionConnection->distance << std::endl;
		}
	}
	*/

	//Point start( 0, 300 );
	//Point end( 350, 500 );
	Point start( 100, 1400 );
	Point end( 300, 1500 );
	
	// NOTE: dijkstra is used for the testing since it is easier to implement than A*, even though not much
	uint32_t startTicksD, endTicksD;
	startTicksD = SDL_GetTicks();
	dijkstra( regionChangeGraph, connectionGraph, start, end );
	endTicksD = SDL_GetTicks();
	
	uint32_t startTicksA, endTicksA;
	startTicksA = SDL_GetTicks();
	std::vector<Point> path = aStar( start, end, 64, 64, 10, 4000 );
	endTicksA = SDL_GetTicks();
	
	std::cout << "dijkstra init " << (initEnd-initStart) << "ms" << std::endl;
	std::cout << "dijkstra took " << (endTicksD-startTicksD) << "ms" << std::endl;
	std::cout << "old A*   took " << (endTicksA-startTicksA) << "ms" << std::endl;
	
	/*
	for ( size_t curWPNr=0; curWPNr<path.size(); ++curWPNr ) {
		std::cout << "WP " << curWPNr+1 << ": (" << path[curWPNr].x << "," << path[curWPNr].y << ")" << std::endl;
	}*/
	
	/*
	for ( size_t curRegionNr=0; curRegionNr<regionDecomposition.size(); ++curRegionNr ) {
		Region *curRegion = regionDecomposition[ curRegionNr ];
		std::cout << "freeRegions.push_back( sCollisionMap( " << curRegion->x << ", " << curRegion->y << ", "
		          << curRegion->h << ", " << curRegion->w << ") );" << std::endl;
	}
	std::cout << "total regions generated: " << regionDecomposition.size() << std::endl;

	// look for regions that could be put together
	std::cout << equalSize << " regions might be combined (at most)" << std::endl;
	*/
	
	return 0;
}

