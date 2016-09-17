//2016-luaPP zukonake

#include <luaPP/element/stackElement.hpp>
//
#include <cassert>
//
#include <luaPP/luaStack.hpp>

using namespace LW;

StackElement::StackElement( const LuaStack& luaStack, const Index& index ) :
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

const Index& StackElement::getIndex() const noexcept
{
	return mIndex;
}
