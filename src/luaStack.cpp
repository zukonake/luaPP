#include <luaPP/luaStack.hpp>
//
#include <cassert>
//
#include <luaPP/element/stackElement.hpp>
#include <luaPP/element/nil.hpp>
#include <luaPP/element/number.hpp>
#include <luaPP/element/string.hpp>
#include <luaPP/element/table.hpp>
#include <luaPP/element/function.hpp>

using namespace LW;

LuaStack::LuaStack()
{
	mL = luaL_newstate();
	luaL_openlibs( mL );
}

LuaStack::~LuaStack()
{
	clear();
	lua_close( mL );
}

Function* LuaStack::loadFile( const std::string& path )
{
	if( luaL_loadfile( mL, path.c_str()) != LUA_OK )
	{
		throw std::runtime_error( "LuaStack::loadFile: " + getString( -1 ));
	}
	return new Function( *this, -1 );
}

LuaType LuaStack::getType( const Index& index )
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

std::string LuaStack::getTypeName( const LuaType& type )
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

NumberValue LuaStack::getNumber( const Index& index )
{
	return ( NumberValue )lua_tonumber( mL, index );
}

StringValue LuaStack::getString( const Index& index )
{
	return ( StringValue )lua_tostring( mL, index );
}

void LuaStack::loadGlobals()
{
	lua_getglobal( mL, "luaPP" );
	mStack = new Table( *this, -1 );
}

Index LuaStack::getIndex()
{
	return ( Index )lua_gettop( mL );
}

void LuaStack::pushNil()
{
	lua_pushnil( mL );
}

void LuaStack::clear()
{
	if( mStack != nullptr )
	{
		delete mStack;
	}
}

void LuaStack::insert( const Index& index )
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

void LuaStack::push( const Index& index )
{
	lua_pushvalue( mL, index );
}

void LuaStack::copy( const Index& from, const Index& to )
{
	lua_copy( mL, from, to );
}

void LuaStack::remove( const Index& index )
{
	lua_remove( mL, index );
}

void LuaStack::pop( const Index& amount )
{
	lua_pop( mL, amount );
}

bool LuaStack::iterate( const Index& index )
{
	return ( bool )lua_next( mL, index );
}

Index LuaStack::call()
{
	Index before = getIndex();
	if( lua_pcall( mL, 0, LUA_MULTRET, 0 ) != LUA_OK )
	{
		throw std::runtime_error( "LuaStack::call: " + getString( -1 ));
	}
	Index after = getIndex();
	return after - before;
}
