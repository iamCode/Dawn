#ifndef A_STAR_H
#define A_STAR_H

#include <vector>

#include "tileset.h" // for struct Point

std::vector<Point> aStar( const Point &start, const Point &end, int width, int height );

#endif // A_STAR_H
