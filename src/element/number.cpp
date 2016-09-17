//2016-luaPP zukonake

#include <luaPP/element/number.hpp>
//
#include <stdexcept>
//
#include <luaPP/luaStack.hpp>

using namespace LW;

Number::Number( const LuaStack& luaStack, const Index& index ) :
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

const NumberValue& Number::get() const noexcept
{
	return mValue;
}
