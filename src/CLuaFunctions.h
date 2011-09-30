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

#ifndef C_LUA_FUNCTIONS_H
#define C_LUA_FUNCTIONS_H

#include <string>

struct lua_State;

namespace LuaFunctions
{
	void init();

	/// \brief gets the lua_State object for scripting.
	///
	/// can be called after globalInit();
	lua_State *getGlobalLuaState();

	void executeLuaFile( std::string filename );
	void executeLuaScript( std::string scripttext );

	/// \brief gets the name of the entry of a certain value in a lua table
	///
	/// example: the magic-missile spell is stored in lua in the table spellDatabase
	///          as spellDatabase["magicmissile"]
	///          so if you call getIDFromLuaTable( "spellDatabase", <ptr to magic-missile spell> )
	///			 it will return "magicmissile"
	///
	/// caution: This works only with the original instances that were put in the lua table. Any copies (new instances)
	///          created from them will not work so this should only be used with objects that exist only exactly once.
	std::string getIDFromLuaTable(const std::string &tableName, const void *value );

	#ifdef TESTINTERFACE
	    lua_State* getGlobalLuaTestState();
	    void executeLuaTestFile( std::string filename );
	#endif

} // namespace LuaFunctions

#endif
