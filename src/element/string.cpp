//2016-luaPP zukonake

#include <luaPP/element/string.hpp>
//
#include <stdexcept>
//
#include <luaPP/luaStack.hpp>

using namespace LW;

String::String( const LuaStack& luaStack, const Index& index ) :
	StackElement( luaStack, index )
{
	if( luaStack.getType( index ) != LuaType::STRING )
	{
		throw std::runtime_error( "LW::String::String: tried to convert a non-string lua type to string" );
	}
	mValue = luaStack.getString( index );
}

String::operator const StringValue&() const noexcept
{
	return mValue;
}

const StringValue& String::get() const noexcept
{
	return mValue;
}
