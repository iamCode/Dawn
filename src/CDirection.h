/**
    Copyright (C) 2009,2010,2011  Dawn - 2D roleplaying game

    This file is a part of the dawn-rpg project <http://sourceforge.net/projects/dawn-rpg/>.

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

#ifndef __C_DIRECTION_H
#define __C_DIRECTION_H

/** directions:
  8-1-2
  7-0-3
  6-5-4 **/
enum Direction {
	STOP = 0,
	N    = 1,
	NE   = 2,
	E    = 3,
	SE   = 4,
	S    = 5,
	SW   = 6,
	W    = 7,
	NW   = 8
};

#endif // __C_DIRECTION_H

