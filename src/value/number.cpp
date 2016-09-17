#include "number.hpp"
//
#include <stdexcept>
//
#include <lua5.2/lua.hpp>
//
#include <luaState.hpp>

using namespace LW;

Number::Number( LuaState& luaState, const Index& index ) :
	StackElement( luaState, index )
{
	if( luaState.getType( index ) != LuaType::NUMBER )
	{
		throw std::runtime_error( "LW::Number::Number: tried to convert non-number lua type to number" );
	}
	mValue = luaState.getNumber( index );
}

Number::operator const NumberValue&() const noexcept
{
	return mValue;
}
