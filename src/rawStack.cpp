#include <stdexcept>
#include <utility>
#include <string>
//
#include <lua.hpp>
//
#include <luna/typedef.hpp>
#include <luna/exception.hpp>
#include <luna/auxiliary.hpp>
#include <luna/rawStack.hpp>

namespace Luna
{

RawStack::RawStack( LuaState const &luaState ) noexcept :
	mLuaState( luaState )
{
	
}

void RawStack::loadFile( std::string const &path )
{
	try
	{
		allocate();
	}
	catch( std::exception const &e )
	{
		throw;
		return;
	}
	checkForError( luaL_loadfile( mLuaState, path.c_str()), path );
}

void RawStack::loadString( std::string const &value )
{
	try
	{
		allocate();
	}
	catch( std::exception const &e )
	{
		throw;
		return;
	}
	checkForError( luaL_loadstring( mLuaState, value.c_str()), value );
}

Size RawStack::doFile( std::string const &path, Size const &arguments )
{
	loadFile( path );
	return call( -1, arguments );
}

Size RawStack::doString( std::string const &path, Size const &arguments )
{
	loadString( path );
	return call( -1, arguments );
}

Size RawStack::call( Index const &index, Size const &arguments )
{
	try
	{
		validateType( index, FUNCTION );
		copy();
	}
	catch( std::exception const &e )
	{
		throw;
		return 0;
	}
	Size before = getSize();
	checkForError( lua_pcall( mLuaState, arguments, LUA_MULTRET, 0 ) != LUA_OK, std::to_string( index ));
	return getSize() - before;
}

void RawStack::pushNil()
{
	try
	{
		allocate();
	}
	catch( std::exception const &e )
	{
		return;
	}
	lua_pushnil( mLuaState );
}

void RawStack::pushNumber( NumberValue const &value )
{
	try
	{
		allocate();
	}
	catch( std::exception const &e )
	{
		return;
	}
	lua_pushnumber( mLuaState, value );
}

void RawStack::pushBoolean( BooleanValue const &value )
{
	try
	{
		allocate();
	}
	catch( std::exception const &e )
	{
		return;
	}
	lua_pushboolean( mLuaState, value );
}

void RawStack::pushString( StringValue const &value )
{
	try
	{
		allocate();
	}
	catch( std::exception const &e )
	{
		return;
	}
	lua_pushstring( mLuaState, value.c_str());
}

void RawStack::loadGlobal( std::string const &name )
{
	try
	{
		allocate();
	}
	catch( std::exception const &e )
	{
		return;
	}
	if( Auxiliary::convertType( lua_getglobal( mLuaState, name.c_str())) == NIL )
	{
		throw Exception::StackError( "Luna::RawStack::loadGlobal: couldn't load global:" + name );
	}
}

NumberValue RawStack::toNumber( Index const &index ) const
{
	try
	{
		validateType( index, NUMBER );
	}
	catch( std::exception const &e )
	{
		throw;
		return 0;
	}
	return lua_tonumber( mLuaState, index );
}

BooleanValue RawStack::toBoolean( Index const &index ) const
{
	try
	{
		validateType( index, BOOLEAN );
	}
	catch( std::exception const &e )
	{
		throw;
		return 0;
	}
	return lua_toboolean( mLuaState, index );
}

StringValue RawStack::toString( Index const &index ) const
{
	try
	{
		validateType( index, STRING );
	}
	catch( std::exception const &e )
	{
		throw;
		return "";
	}
	return lua_tostring( mLuaState, index );
}

Type RawStack::getType( Index const &index ) const
{
	try
	{
		validate( index );
	}
	catch( std::exception const &e )
	{
		throw;
		return INVALID;
	}
	return Auxiliary::convertType( lua_type( mLuaState, index ));
}

void RawStack::copy( Index const &from )
{
	try
	{
		allocate();
		validate( from );
	}	
	catch( std::exception const &e )
	{
		throw;
		return;
	}
	lua_pushvalue( mLuaState, from );
}

void RawStack::insert( Index const &index )
{
	try
	{
		allocate();
		validate( index );
	}
	catch( std::exception const &e )
	{
		throw;
		return;
	}
	lua_insert( mLuaState, getAbsoluteIndex( index ));
}

void RawStack::replace( Index const &from, Index const &to )
{
	AbsoluteIndex realTo;
	AbsoluteIndex realFrom;
	try
	{
		realTo = getAbsoluteIndex( to );
		realFrom = getAbsoluteIndex( from );
		if( realFrom == realTo )
		{
			return;
		}
	}
	catch( std::exception const &e )
	{
		throw;
		return;
	}
	lua_copy( mLuaState, realFrom, realTo );
}

void RawStack::move( Index const &from, Index const &to )
{
	AbsoluteIndex realFrom;
	AbsoluteIndex realTo;
	try
	{
		realFrom = getAbsoluteIndex( from );
		realTo = getAbsoluteIndex( to );
		if( realFrom == realTo )
		{
			return;
		}
		if( from != -1 )
		{
			copy( realFrom );
		}
		lua_replace( mLuaState, realTo );
		if( from != -1 )
		{
			remove( realFrom );
		}
	}
	catch( std::exception const &e )
	{
		throw;
		return;
	}
}

void RawStack::swap( Index const &one, Index const &two )
{
	AbsoluteIndex realOne = getAbsoluteIndex( one );
	AbsoluteIndex realTwo = getAbsoluteIndex( two );
	if( realOne == realTwo )
	{
		return;
	}
	copy( realTwo );
	replace( realOne, realTwo );
	move( -1, realOne );
}

bool RawStack::iterate( Index const &index )
{
	try
	{
		validateType( index, TABLE );
		allocate();
	}
	catch( std::exception const &e )
	{
		throw;
		return false;
	}
	return lua_next( mLuaState, index );
}

void RawStack::remove( Index const &index )
{
	try
	{
		validate( index );
	}
	catch( std::exception const &e )
	{
		throw;
		return;
	}
	lua_remove( mLuaState, getAbsoluteIndex( index ));
}

void RawStack::erase( Index const &index )
{
	AbsoluteIndex realIndex = getAbsoluteIndex( index );
	pushNil();
	move( -1, realIndex );
}

void RawStack::pop( Size const &space )
{
	if( getSize() < space )
	{
		throw Exception::StackError( "Luna::RawStack::pop: tried to pop " + std::to_string( space ) + " elements while the stack has only " + std::to_string( getSize()));
		return;
	}
	lua_pop( mLuaState, space );
}

void RawStack::clear() noexcept
{
	lua_settop( mLuaState, 0 );
}

bool RawStack::isValid( Index const & index ) const noexcept
{
	return index != 0 && index >= -(( Index )getSize()) && index <= ( Index )getSize();
}

Index RawStack::getRelativeIndex( AbsoluteIndex const &index ) const
{
	validate( index );
	Index returnValue = index - ((( Index )getSize()) + 1 );
	return returnValue;
}

AbsoluteIndex RawStack::getAbsoluteIndex( Index const &index ) const
{
	validate( index );
	if( index > 0 )
	{
		return ( AbsoluteIndex )index;
	}
	AbsoluteIndex returnValue = (( AbsoluteIndex )getSize()) + ((( AbsoluteIndex )index ) + 1u );
	return returnValue;
}

Size RawStack::getSize() const noexcept
{
	return ( Size )lua_gettop( mLuaState );
}

LuaState const &RawStack::getLuaState() const noexcept
{
	return mLuaState;
}

void RawStack::allocate( Size const &space )
{
	if( !lua_checkstack( mLuaState, space ))
	{
		throw Exception::AllocationError( "Luna::RawStack::allocate: couldn't allocate: " + std::to_string( space ) + " space" );
	}
}

void RawStack::validate( Index const &index ) const
{
	if( !isValid( index ))
	{
		throw Exception::IndexError( "Luna::RawStack::validate: couldn't validate index: " + std::to_string( index ));
	}
}

void RawStack::validateType( Index const &index, Type const &type ) const
{
	Type check = getType( index );
	if( check != type )
	{
		throw Exception::TypeError( "Luna::RawStack::validateType: type " + Auxiliary::getTypeName( check ) + " instead of " + Auxiliary::getTypeName( type ) + " type" );
	}
}

void RawStack::checkForError( LuaErrorCode const &code, std::string const &message ) const
{
	switch( code )
	{
		case LUA_OK:
			break;

		case LUA_ERRRUN:
			throw Exception::LuaError( "Luna::Auxiliary::checkForError: runtime error: " + message );
			break;

		case LUA_ERRMEM:
			throw Exception::AllocationError( "Luna::Auxiliary::checkForError: couldn't allocate memory: " + message );
			break;

		case LUA_ERRERR:
			throw Exception::LuaError( "Luna::Auxiliary::checkForError: message handler error: " + message );
			break;

		case LUA_ERRGCMM:
			throw Exception::LuaError( "Luna::Auxiliary::checkForError: garbage collector error: " + message );
			break;

		case LUA_ERRFILE:
			throw Exception::FileError( "Luna::Auxiliary::checkForError: couldn't open file: " + message );
			break;

		case LUA_ERRSYNTAX:
			throw Exception::SyntaxError( "Luna::Auxiliary::checkForError: syntax error: " + toString());
			break;

		default:
			throw Exception::LuaError( "Luna::Auxiliary::checkForError: unknown rror: " + message );
			break;
	}
}

}
