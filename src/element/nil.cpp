#include <luaPP/element/nil.hpp>
//
#include <stdexcept>
//
#include <lua5.2/lua.hpp>
//
#include <luaPP/luaStack.hpp>

using namespace LW;

Nil::Nil( LuaStack& luaStack, const Index& index ) :
	StackElement( luaStack, index )
{
	if( luaStack.getType( index ) != LuaType::NIL )
	{
		throw std::runtime_error( "LW::Nil::Nil: tried to convert a non-nil lua type to nil" );
	}
}
