#include "callindirection.h"

#include "CLuaFunctions.h"

LuaCallIndirection::LuaCallIndirection()
{
	luaText = "";
}

void LuaCallIndirection::call()
{
	if ( luaText != "" ) {
		LuaFunctions::executeLuaScript( luaText );
	}
}

void LuaCallIndirection::setExecuteText( std::string text )
{
	this->luaText = text;
}

namespace DawnInterface
{
	LuaCallIndirection* createEventHandler()
	{
		return new LuaCallIndirection();
	}

}

