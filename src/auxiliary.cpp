#include <cstdlib>
#include <stdexcept>
//
#include <luna/typedef.hpp>
#include <luna/auxiliary.hpp>

namespace Luna::Auxiliary
{

std::string getTypeName( const Type &type ) noexcept
{
	switch( type )
	{
		case NIL:
			return "nil";
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

		case USERDATA:
			return "userdata";
			break;

		case LIGHTUSERDATA:
			return "light userdata";
			break;

		default:
			return "invalid";
			break;
	}
}

void *allocate( void *ud, void *ptr, std::size_t osize, std::size_t nsize )
{
	( void )ud;
	if( nsize == 0 )
	{
		if( osize > 0 )
		{
			::operator delete( ptr, osize );
		}
		return nullptr;
	}
	else
	{
		if( osize > 0 )
		{
			if( osize != nsize )
			{
				ptr = std::realloc( ptr, nsize );
			}
		}
		else
		{
			try
			{
				ptr = ::operator new( nsize );
			}
			catch( std::bad_alloc &e )
			{
				throw;
				return allocate( nullptr, ptr, nsize, 0 );
			}
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
