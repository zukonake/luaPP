//2016-luaPP zukonake

#include <luaPP/element/function.hpp>
//
#include <stdexcept>
//
#include <luaPP/luaStack.hpp>

using namespace LW;

Function::Function( const LuaStack& luaStack, const Index& index ) :
	StackElement( luaStack, index )
{
	if( luaStack.getType( index ) != LuaType::FUNCTION )
	{
		throw std::runtime_error( "LW::Function::Function: tried to call a non-function lua type" );
	}
}
