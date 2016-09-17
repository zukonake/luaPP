#include <luaState.hpp>
//
#include <cassert>
//
#include <element/stackElement.hpp>
#include <element/nil.hpp>
#include <element/number.hpp>
#include <element/string.hpp>
#include <element/table.hpp>
#include <element/function.hpp>

using namespace LW;

LuaState::LuaState()
{
	mL = luaL_newstate();
	luaL_openlibs( mL );
}

LuaState::~LuaState()
{
	lua_close( mL );
}

LuaState::operator lua_State*()
{
	return mL;
}

void LuaState::loadFile( const std::string& path )
{
	luaL_loadfile( mL, path.c_str());
}

LuaType LuaState::getType( const Index& index )
{
	switch( lua_type( mL, index ) )
	{
		case LUA_TNUMBER:
		return LuaType::NUMBER;
		break;

		case LUA_TSTRING:
		return LuaType::STRING;
		break;

		case LUA_TTABLE:
		return LuaType::TABLE;
		break;

		case LUA_TFUNCTION:
		return LuaType::FUNCTION;
		break;

		default:
		return LuaType::NIL;
		break;
	}
}

std::string LuaState::getTypeName( const LuaType& type )
{
	switch( type )
	{
		case LuaType::NUMBER:
		return "number";
		break;

		case LuaType::STRING:
		return "string";
		break;

		case LuaType::TABLE:
		return "table";
		break;

		case LuaType::FUNCTION:
		return "function";
		break;

		default:
		return "nil";
		break;
	}
}

StackElement* LuaState::evaluateType( const Index& index )
{
	switch( getType( index ) )
	{
		case LuaType::NUMBER:
		return new Number( *this, index );
		break;

		case LuaType::STRING:
		return new String( *this, index );
		break;

		case LuaType::TABLE:
		return new Table( *this, index );
		break;

		case LuaType::FUNCTION:
		return new Function( *this, index );
		break;

		default:
		return new Nil( *this, index );
		break;
	}
}

NumberValue LuaState::getNumber( const Index& index )
{
	return ( NumberValue )lua_tonumber( mL, index );
}

StringValue LuaState::getString( const Index& index )
{
	return ( StringValue )lua_tostring( mL, index );
}

void LuaState::getVariable( const std::string& name )
{
	lua_getglobal( mL, name.c_str() );
}

Index LuaState::getIndex()
{
	return ( Index )lua_gettop( mL );
}

void LuaState::pushNil()
{
	lua_pushnil( mL );
}

void LuaState::insert( const Index& index )
{
	if( index > 0 )
	{
		lua_insert( mL, index );
	}
	else if( index < 0 )
	{
		lua_insert( mL, getIndex() + ( index + 1 ));
	}
	else
	{
		assert( false );
	}
}

void LuaState::push( const Index& index )
{
	lua_pushvalue( mL, index );
}

void LuaState::copy( const Index& from, const Index& to )
{
	lua_copy( mL, from, to );
}

void LuaState::remove( const Index& index )
{
	lua_remove( mL, index );
}

void LuaState::pop( const Index& amount )
{
	lua_pop( mL, amount );
}

bool LuaState::iterate( const Index& index )
{
	return ( bool )lua_next( mL, index );
}

Index LuaState::call()
{
	Index before = getIndex();
	if( lua_pcall( mL, 0, LUA_MULTRET, 0 ) != LUA_OK )
	{
		throw std::runtime_error( getString( -1 ));
	}
	Index after = getIndex();
	return before - after;
}
