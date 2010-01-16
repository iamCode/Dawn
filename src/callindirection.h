#ifndef CALLINDIRECTION_H
#define CALLINDIRECTION_H

#include <string>

class CallIndirection
{
	public:
		virtual void call() = 0;
};

class LuaCallIndirection
{
	public:
		LuaCallIndirection();
		
		virtual void call();
		
		void setExecuteText( std::string text );
		
	private:
		std::string luaText;
};

#endif // CALLINDIRECTION_H

