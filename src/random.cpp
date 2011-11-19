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

#include "random.h"

#include <cstdlib>
#include <cmath>

namespace RNG
{
void initRNG( unsigned int seed )
{
	srand( seed );
}

size_t randomSizeT( size_t min, size_t max )
{
	return min + ( static_cast<size_t>((max - min + 1) * static_cast<double>(rand())/static_cast<double>(RAND_MAX + 1.0)) );
}

int randomInt( int min, int max )
{
	return randomSizeT( 0, max - min ) + min;
}

double randomDouble( double min, double max )
{
	return min + ( (max - min) * static_cast<double>(rand())/static_cast<double>(RAND_MAX) );
}

}
