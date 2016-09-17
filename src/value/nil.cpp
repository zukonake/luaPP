#include "nil.hpp"
//
#include <stdexcept>
//
#include <lua5.2/lua.hpp>
//
#include <luaState.hpp>

using namespace LW;

Nil::Nil( LuaState& luaState, const Index& index ) :
	StackElement( luaState, index )
{
	if( luaState.getType( index ) != LuaType::NIL )
	{
		throw std::runtime_error( "LW::Nil::Nil: tried to convert non-nil lua type to nil" );
	}
}
