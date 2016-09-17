//2016-luaPP zukonake

#include <luaPP/element/stackElement.hpp>
//
#include <stdexcept>
//
#include <luaPP/luaStack.hpp>

using namespace LPP;

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
		throw std::logic_error( "LuaStack::insert: index 0 given" );
	}
}

StackElement::~StackElement()
{
	mLuaStack.pushNil();
	mLuaStack.replace( mIndex );
}

const Index& StackElement::getIndex() const noexcept
{
	return mIndex;
}
