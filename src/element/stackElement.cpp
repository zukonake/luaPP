#include <luaPP/element/stackElement.hpp>
//
#include <cassert>
//
#include <lua5.2/lua.hpp>
//
#include <luaPP/luaStack.hpp>

using namespace LW;

StackElement::StackElement( LuaStack& luaStack, const Index& index ) :
	mLuaStack( luaStack )
{
	if( index < 0 )
	{
		mIndex = mLuaStack.getIndex() + ( index + 1 );
	}
	else if( index > 0 )
	{
		mIndex = index;
	}
	else
	{
		assert( false );
	}
}

StackElement::~StackElement()
{
	mLuaStack.pushNil();
	mLuaStack.copy( -1, mIndex );
}
