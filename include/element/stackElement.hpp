#ifndef STACKELEMENT_HPP
#define STACKELEMENT_HPP

#include <typedef.hpp>

namespace LW
{

class LuaState;

class StackElement
{
protected:
	StackElement() = delete;
	StackElement( LuaState& luaState, const Index& index = -1 );
public:
	virtual ~StackElement();
protected:
	LuaState& mLuaState;
	Index mIndex;
};

}

#endif
