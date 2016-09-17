#include <element/string.hpp>
//
#include <stdexcept>
//
#include <lua5.2/lua.hpp>
//
#include <luaState.hpp>

using namespace LW;

String::String( LuaState& luaState, const Index& index ) :
	StackElement( luaState, index )
{
	if( luaState.getType( index ) != LuaType::STRING )
	{
		throw std::runtime_error( "LW::String::String: tried to convert non-string lua type to string" );
	}
	mValue = luaState.getString( index );
}

String::operator const StringValue&() const noexcept
{
	return mValue;
}
