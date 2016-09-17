#ifndef STACKELEMENT_HPP
#define STACKELEMENT_HPP

#include <luaPP/typedef.hpp>

namespace LW
{

class LuaStack;

class StackElement
{
protected:
	StackElement() = delete;
	StackElement( LuaStack& luaStack, const Index& index = -1 );
public:
	virtual ~StackElement();
protected:
	LuaStack& mLuaStack;
	Index mIndex;
};

}

#endif
