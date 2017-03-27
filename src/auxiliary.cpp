#include <cstdlib>
#include <stdexcept>
#include <string>
//
#include <lua.hpp>
//
#include <luna/typedef.hpp>
#include <luna/auxiliary.hpp>

namespace Luna::Auxiliary
{

Type convertType( const LuaType &luaType ) noexcept
{	
	switch( luaType )
	{
		case LUA_TNIL:
			return NIL;
			break;

		case LUA_TNUMBER:
			return NUMBER;
			break;

		case LUA_TBOOLEAN:
			return BOOLEAN;
			break;

		case LUA_TSTRING:
			return STRING;
			break;

		case LUA_TTABLE:
			return TABLE;
			break;

		case LUA_TFUNCTION:
			return FUNCTION;
			break;

		case LUA_TTHREAD:
			return THREAD;
			break;

		case LUA_TUSERDATA:
			return USER_DATA;
			break;

		case LUA_TLIGHTUSERDATA:
			return LIGHT_USER_DATA;
			break;

		default:
			return INVALID;
			break;
	}
}

std::string getTypeName( Type const &type ) noexcept
{
	switch( type )
	{
		case NIL:
			return "nil";
			break;

		case BOOLEAN:
			return "boolean";
			break;

		case NUMBER:
			return "number";
			break;

		case STRING:
			return "string";
			break;

		case TABLE:
			return "table";
			break;

		case FUNCTION:
			return "function";
			break;

		case THREAD:
			return "thread";
			break;

		case USER_DATA:
			return "userdata";
			break;

		case LIGHT_USER_DATA:
			return "light userdata";
			break;

		default:
			return "invalid";
			break;
	}
}

void *allocate( void *ud, void *ptr, std::size_t osize, std::size_t nsize )
{
	( void )ud,( void )osize;
	if( nsize == 0 )
	{
		std::free( ptr );
		return nullptr;
	}
	else
	{
		ptr = std::realloc( ptr, nsize );
		if( ptr == nullptr )
		{
			throw std::bad_alloc();
		}
		return ptr;
	}
}

int panic( lua_State *L )
{
	if( lua_gettop( L ) == 0 )
	{
		throw std::runtime_error( "Luna::Auxiliary::Panic: invalid error message given" );
		return 1;
	}

	if( !lua_isstring( L, -1 ))
	{
		throw std::runtime_error( "Luna::Auxiliary::Panic: invalid error message given" );
		return 1;
	}
	throw std::runtime_error( "Luna::Auxiliary::Panic: " + ( std::string )lua_tostring( L, -1 ));
	return 0;
}

}
