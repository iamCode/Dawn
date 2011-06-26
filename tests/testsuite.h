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

#include <iostream>
#include <string>

bool logWithJUnit = false;

class TestCase
{
	public:
		TestCase( std::string name, std::string description, std::string LUAfile );

		std::string getName() const;
		std::string getDescription() const;
		std::string getLUAfile() const;

		int getResult() const;
		void setResult( int result );

	private:
		std::string name;
		std::string description;
		std::string LUAfile;
		int result;
};
