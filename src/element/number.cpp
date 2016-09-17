#include <luaPP/element/number.hpp>
//
#include <stdexcept>
//
#include <lua5.2/lua.hpp>
//
#include <luaPP/luaStack.hpp>

using namespace LW;

Number::Number( LuaStack& luaStack, const Index& index ) :
	StackElement( luaStack, index )
{
	if( luaStack.getType( index ) != LuaType::NUMBER )
	{
		throw std::runtime_error( "LW::Number::Number: tried to convert a non-number lua type to number" );
	}
	mValue = luaStack.getNumber( index );
}

Number::operator const NumberValue&() const noexcept
{
	return mValue;
}
