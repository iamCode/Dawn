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

#ifndef CALLINDIRECTION_H
#define CALLINDIRECTION_H

#include <string>

class CallIndirection
{
public:
	virtual void call() = 0;
	virtual std::string getLuaSaveText() const = 0;
};

class LuaCallIndirection : public CallIndirection
{
public:
	LuaCallIndirection();

	virtual void call();
	virtual std::string getLuaSaveText() const;

	void setExecuteText( std::string text );

private:
	std::string luaText;
};

#endif

