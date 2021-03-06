#include "a_star.h"

#include "direction.h"

#include <list>
#include <limits>
#include <algorithm>
#include <iostream>
#include <cassert>
#include <cstdlib>
#include <cmath>

struct SearchListStruct
{
  Point p;
  int value;
  int estimatedF;
  Direction predDir;

  SearchListStruct( const Point &p_, int value_, int estimatedF_, Direction predDir_ )
    :  p( p_ ),
     value( value_ ),
     estimatedF( estimatedF_ ),
       predDir( predDir_ )
    {
    }

  bool operator == ( const SearchListStruct &other ) const
  {
    return (p.x == other.p.x && p.y == other.p.y);
  }

  bool operator == ( const Point &point ) const
  {
    return (p.x == point.x && p.y == point.y );
  }
};

std::list< SearchListStruct > openList;
std::list< SearchListStruct > closedList;
int offsetX[] = {  0,  0,  1,  1,  1,  0, -1, -1, -1 };
int offsetY[] = {  0,  1,  1,  0, -1, -1, -1,  0,  1 };
int movePoints[] = { 0, 10, 14, 10, 14, 10, 14, 10, 14 };
Direction dirToPredecessor[] = { STOP, S, SW, W, NW, N, NE, E, SE };
int counter = 0;
int maxValue = 0;

/* this is the step-width for neighbours in pixels.
   a bigger value makes the value slightly suboptimal
   (and no path may be found through very narrow passages)
   but the heuristics gets *much* faster. */
int distanceSkip = 10;

SearchListStruct popMinimumElement( std::list<SearchListStruct> & list )
{
  assert( list.size() > 0 );
  // note: This can be drastically improved if the list is kept sorted
  // inserting will not be very expensive in that case either
  int minEstimate = std::numeric_limits<int>::max();
  std::list<SearchListStruct>::iterator minIt = list.begin();
  for( std::list<SearchListStruct>::iterator it=list.begin();
       it!=list.end();
       ++it )
  {
    if( it->estimatedF < minEstimate )
    {
      minIt = it;
      minEstimate = it->estimatedF;
    }
  }

  SearchListStruct minPoint = *minIt;
  list.erase( minIt );
  return minPoint;
}

bool isFree( int px, int py, int w, int h );

SearchListStruct closestNodeFound( Point(0,0), 0, 0, STOP );
int numIterations;

void expandNode( SearchListStruct& currentNode,
                 const Point& end,
                 int width,
                 int height )
{
  ++numIterations;
  /* std::cout << "expanding node ( (" << currentNode.p.x<< ","
     << currentNode.p.y << "), v: " << currentNode.value  << ",
     f: " << currentNode.estimatedF << ", dir: " << currentNode.
     predDir << ")" << std::endl; */

  for( int dir=1; dir<=8; ++dir )
  {
    SearchListStruct successor(Point(currentNode.p.x+offsetX[dir]*distanceSkip,
                                     currentNode.p.y+offsetY[dir]*distanceSkip),
                               0, 0, STOP );

    if( !isFree( successor.p.x, successor.p.y, width, height ) )
    {
      continue;
    }

    if( std::find( closedList.begin(),
                   closedList.end(),
                   successor ) != closedList.end() )
    {
      continue;
    }

    int tentative_g = currentNode.value + movePoints[ dir ]*distanceSkip;

    std::list<SearchListStruct>::iterator sucOpenIt=std::find( openList.begin(),
                                                               openList.end(),
                                                               successor );
    if ( sucOpenIt != openList.end() && tentative_g >= sucOpenIt->value ) {
      continue;
    }
    successor.predDir = dirToPredecessor[ dir ];
    successor.value = tentative_g;

    int oddMoves = std::min(abs(end.x-currentNode.p.x),
                            abs(end.y-currentNode.p.y));
    int evenMoves = std::abs(end.x-currentNode.p.x) +
                    std::abs(end.y-currentNode.p.y) -
                    2*oddMoves;
    int f = tentative_g + 10*evenMoves + 14*oddMoves;

    if( sucOpenIt != openList.end() )
    {
      sucOpenIt->predDir = successor.predDir;
      sucOpenIt->value = successor.value;
      sucOpenIt->estimatedF = f;
      if( std::pow(closestNodeFound.p.x-end.x,2) +
          std::pow(closestNodeFound.p.x-end.x,2) >
          std::pow(sucOpenIt->p.x-end.x,2) +
          std::pow(sucOpenIt->p.y-end.y,2))
      {
        closestNodeFound = *sucOpenIt;
      }
    }
    else
    {
      successor.estimatedF = f;
      openList.push_front( successor );
    }
  }
}

std::vector<Point> aStar( const Point& start,
                          const Point& end,
                          int width,
                          int height,
                          int granularity,
                          int maxIterations )
{
  openList.clear();
  closedList.clear();
  openList.push_back( SearchListStruct( start,
                                        0,
                                        std::numeric_limits<int>::max(),
                                        STOP ) );
  counter = 0;
  closestNodeFound = SearchListStruct( start,
                                       0,
                                       std::numeric_limits<int>::max(),
                                       STOP );
  numIterations = 0;
  distanceSkip = granularity;

  while( openList.size() > 0 )
  {
    SearchListStruct currentNode = popMinimumElement( openList );

    if( numIterations >= maxIterations ||
        std::pow(currentNode.p.x-end.x,2) +
        std::pow(currentNode.p.y-end.y,2) <
        distanceSkip*14 )
    {
      if( numIterations >= maxIterations )
      {
        currentNode = closestNodeFound;
      }

      // Return NodeList
      std::vector<Point> nodeList;
      nodeList.push_back(currentNode.p);
      while( !(currentNode == start) )
      {
        Point predNode( currentNode.p.x+offsetX[currentNode.predDir]*distanceSkip,
                        currentNode.p.y+offsetY[currentNode.predDir]*distanceSkip );
        nodeList.push_back( predNode );
        std::list<SearchListStruct>::iterator it =
          std::find( closedList.begin(),
                     closedList.end(),
                     SearchListStruct( predNode, 0, 0, STOP ) );
        assert( it != closedList.end() );
        currentNode = *it;
      }
      nodeList.push_back(start);

      return nodeList;
    }

    expandNode( currentNode, end, width, height );
    closedList.push_back( currentNode );
  }

  // Return NoPathFound
  return std::vector<Point>();
}


/*
// überprüft alle Nachfolgeknoten und fügt sie der Open List hinzu, wenn entweder
// - der Nachfolgeknoten zum ersten Mal gefunden wird oder
// - ein besserer Weg zu diesem Knoten gefunden wird
function expandNode(currentNode)
    foreach successor of currentNode
        // wenn der Nachfolgeknoten bereits auf der Closed List ist - tue nichts
        if closedlist.contains(successor) then
            continue
        // g Wert für den neuen Weg berechnen: g Wert des Vorgängers plus
        // die Kosten der gerade benutzten Kante
        tentative_g = g(currentNode) + c(currentNode, successor)
        // wenn der Nachfolgeknoten bereits auf der Open List ist,
        // aber der neue Weg nicht besser ist als der alte - tue nichts
        if openlist.contains(successor) and tentative_g >= g[successor] then
            continue
        // Vorgängerzeiger setzen und g Wert merken
        successor.predecessor := currentNode
        g[successor] = tentative_g
        // f Wert des Knotens in der Open List aktualisieren
        // bzw. Knoten mit f Wert in die Open List einfügen
        f := tentative_g + h(successor)
        if openlist.contains(successor) then
            openlist.decreaseKey(successor, f)
        else
            openlist.enqueue(successor, f)
    end
end


program a-star
    // Initialisierung der Open List, die Closed List ist noch leer
    // (die Priorität bzw. der f Wert des Startknotens ist unerheblich)
    openlist.enqueue(startknoten, 0)
    // diese Schleife wird durchlaufen bis entweder
    // - die optimale Lösung gefunden wurde oder
    // - feststeht, dass keine Lösung existiert
    repeat
        // Knoten mit dem geringsten f Wert aus der Open List entfernen
        currentNode := openlist.removeMin()
        // Wurde das Ziel gefunden?
        if currentNode == zielknoten then
            return PathFound
        // Wenn das Ziel noch nicht gefunden wurde: Nachfolgeknoten
        // des aktuellen Knotens auf die Open List setzen
        expandNode(currentNode)
        // der aktuelle Knoten ist nun abschließend untersucht
        closedlist.add(currentNode)
    until openlist.isEmpty()
    // die Open List ist leer, es existiert kein Pfad zum Ziel
    return NoPathFound
end
*/
