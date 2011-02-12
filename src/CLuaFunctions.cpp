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

#include "CLuaFunctions.h"

#include "lua.hpp"

#include <cstdlib>
#include <iostream>

#include <tolua++.h>
#include "CLuaInterfaceGenerated.h"
#include "debug.h"

namespace LuaFunctions
{

	/* Declare the Lua libraries we wish to use. */
	/* Note: If you are opening and running a file containing Lua code */
	/* using 'luaL_dofile(l, "myfile.lua") - you must delcare all the libraries */
	/* used in that file here also. */
	static const luaL_reg lualibs[] = {
		{ "",     luaopen_base },
		{ "io",   luaopen_io },
		{ "DawnInterface", tolua_CLuaInterface_open },
		{ NULL,         NULL }
	};

	static lua_State *globalLuaState = NULL;

	static void cleanupLuaState()
	{
		if ( globalLuaState != NULL ) {
			lua_close( globalLuaState );
			globalLuaState = NULL;
		}
	}

	lua_State* createAndInitNewLuaState()
	{
		// initialize lua script interpreter
		lua_State *luaState = lua_open();

		// open lua libs
		for ( const luaL_reg *lib = lualibs; lib->func != NULL; lib++ ) {
			lua_pushcfunction(luaState, lib->func);
			lua_pushstring(luaState, lib->name);
			lua_call(luaState, 1, 0);
		}

		return luaState;
	}

	lua_State* getGlobalLuaState()
	{
		if ( globalLuaState == NULL ) {
			globalLuaState = createAndInitNewLuaState();
			atexit( cleanupLuaState );
		}
		return globalLuaState;
	}

	void executeLuaFile( std::string filename )
	{
		lua_State *lState = getGlobalLuaState();
		int retcode = luaL_dofile( lState, filename.c_str() );
		if ( retcode != 0 ) {
			// there is some error in the lua code
			std::cout << "error in lua file: " << lua_tostring(lState, -1) << std::endl;
			abort();
		}
	}

	void executeLuaScript( std::string scripttext )
	{
		lua_State *lState = getGlobalLuaState();
		int retcode = luaL_dostring( lState, scripttext.c_str() );
		if ( retcode != 0 ) {
			// there is some error in the lua code
			std::cout << "error in lua script: " << lua_tostring(lState, -1) << std::endl;
			abort();
		}
	}

	std::string getIDFromLuaTable( const std::string &tableName, const void *value )
	{
		lua_State *lState = getGlobalLuaState();
		lua_getglobal(lState, tableName.c_str());
		if ( lua_isnil( lState, -1 ) || ! lua_istable( lState, -1 ) )
		{
			dawn_debug_fatal(std::string("table ").append(tableName).append(" does not exist in lua as global table"));
		}
		lua_pushnil(lState);

		// lua-stack layout now:
		// -1 nil
		// -2 table

		bool found = false;
		std::string foundKey = "";

		while( ! found && lua_next(lState, -2) )
		{
			// lua-stack layout now:
			// -1 value
			// -2 key
			// -3 table
			if(lua_isuserdata (lState, -1) )
			{
				// tolua stores userdata in a strange way so we need to retrieve it as *(void**)
				const void *curUserData = *(void**) lua_touserdata(lState, -1);

				if ( curUserData == value )
				{
					// we have found the value
					// normally we should not convert the key directly to string since afterwards it might not
					// be usable for lua_next anymore if it was no string. But since we don't need lua_next afterwards
					// anymore it does not matter
					// still it should be a string in our case so we check that
					if ( ! lua_isstring( lState, -2 ) )
					{
						dawn_debug_fatal( std::string("lua table ").append(tableName).append(" had a non-string key"));
					}
					found = true;
					foundKey = lua_tostring( lState, -2 );
				}
			}
			// pop the value from the stack
			lua_pop(lState, 1);
		}
		// pop the last key from the stack
		lua_pop(lState, 1);

		// pop the table from the stack
		lua_pop(lState, 1);

		if ( ! found )
		{
			dawn_debug_fatal( std::string("could not find searched value in table ").append(tableName) );
		}

		return foundKey;
	}

} // namespace LuaFunctions

