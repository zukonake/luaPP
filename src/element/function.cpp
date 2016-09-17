#include <element/function.hpp>
//
#include <stdexcept>
//
#include <lua5.2/lua.hpp>
//
#include <luaState.hpp>

using namespace LW;

Function::Function( LuaState& luaState, const Index& index ) :
	StackElement( luaState, index )
{
	if( luaState.getType( index ) != LuaType::FUNCTION )
	{
		throw std::runtime_error( "LW::Function::Function: tried to call non-function lua type" );
	}
}

Index Function::call()
{
	return StackElement::mLuaState.call();
}
