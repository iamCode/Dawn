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

#include "elements.h"

#include "debug.h"

namespace ElementType
{
	std::string getElementName( ElementType::ElementType elementType )
	{
		switch( elementType ) {
			case Fire:
				return "Fire";
			break;
			case Water:
				return "Water";
			break;
			case Air:
				return "Air";
			break;
			case Earth:
				return "Earth";
			break;
			case Light:
				return "Light";
			break;
			case Dark:
				return "Dark";
			break;
			default:
				dawn_debug_warn( "unsupported element type in getElementName: %d. Aborting", static_cast<size_t>(elementType) );
				abort();
			break;
		}
	}

	std::string getElementNameLowercase( ElementType::ElementType elementType )
	{
		switch( elementType ) {
			case Fire:
				return "fire";
			break;
			case Water:
				return "water";
			break;
			case Air:
				return "air";
			break;
			case Earth:
				return "earth";
			break;
			case Light:
				return "light";
			break;
			case Dark:
				return "dark";
			break;
			default:
				dawn_debug_warn( "unsupported element type in getElementNameLowercase: %d. Aborting", static_cast<size_t>(elementType) );
				abort();
			break;
		}
	}
}

