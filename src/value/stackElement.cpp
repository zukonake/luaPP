#include "stackElement.hpp"
//
#include <cassert>
//
#include <lua5.2/lua.hpp>
//
#include <luaState.hpp>

using namespace LW;

StackElement::StackElement( LuaState& luaState, const Index& index ) :
	mLuaState( luaState )
{
	if( index < 0 )
	{
		mIndex = mLuaState.getIndex() + ( index + 1 );
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
	mLuaState.pushNil();
	mLuaState.copy( -1, mIndex );
}
