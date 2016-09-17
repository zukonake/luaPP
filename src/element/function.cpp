#include <luaPP/element/function.hpp>
//
#include <stdexcept>
//
#include <lua5.2/lua.hpp>
//
#include <luaPP/luaStack.hpp>
#include <luaPP/element/table.hpp>

using namespace LW;

Function::Function( LuaStack& luaStack, const Index& index ) :
	StackElement( luaStack, index )
{
	if( luaStack.getType( index ) != LuaType::FUNCTION )
	{
		throw std::runtime_error( "LW::Function::Function: tried to call a non-function lua type" );
	}
}

Index Function::call()
{
	return StackElement::mLuaStack.call();
}

void Function::loadGlobals()
{
	return StackElement::mLuaStack.loadGlobals();
}
