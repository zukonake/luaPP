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

RawStack::RawStack() :
	mState()
{
	
}

RawStack::RawStack( RawStack &&that ) :
	mState( std::move( that.mState ))
{

}

RawStack &RawStack::operator=( RawStack &&that )
{
	mState = std::move( that.mState );
	return *this;
}

void RawStack::loadFile( const std::string &path ) const
{
	try
	{
		allocate();
	}
	catch( std::exception &e )
	{
		throw;
		return;
	}
	checkForError( luaL_loadfile( mState, path.c_str()), path );
}

void RawStack::loadString( const std::string &value ) const
{
	try
	{
		allocate();
	}
	catch( std::exception &e )
	{
		throw;
		return;
	}
	checkForError( luaL_loadstring( mState, value.c_str()), value );
}

void RawStack::loadGlobals() const
{
	try
	{
		allocate( 2 );
	}
	catch( std::exception &e )
	{
		throw;
		return;
	}
	loadGlobal( "luna" );
	pushNil();
	while( iterate())
	{
		try
		{
			insert( -3 );
		}
		catch( std::exception &e )
		{
			throw;
			return;
		}
		pop();
	}
	pop();
}

void RawStack::loadGlobal( const std::string &name ) const
{
	try
	{
		allocate();
	}
	catch( std::exception &e )
	{
		return;
	}
	lua_getglobal( mState, name.c_str());
	if( getType() == NIL )
	{
		throw Exception::StackError( "Luna::RawStack::loadGlobal: type nil loaded" );
	}
}

NumberValue RawStack::toNumber( const Index &index ) const
{
	try
	{
		validate( index );
		validateType( index, NUMBER );
	}
	catch( std::exception &e )
	{
		throw;
		return 0;
	}
	return lua_tonumber( mState, index );
}

StringValue RawStack::toString( const Index &index ) const
{
	try
	{
		validate( index );
		validateType( index, STRING );
	}
	catch( std::exception &e )
	{
		throw;
		return "";
	}
	return lua_tostring( mState, index );
}

Size RawStack::doFile( const std::string &path ) const
{
	try
	{
		loadFile( path );
	}
	catch( std::exception &e )
	{
		throw;
		return 0;
	}
	return call();
}

Size RawStack::doString( const std::string &path ) const
{
	try
	{
		loadString( path );
	}
	catch( std::exception &e )
	{
		throw;
		return 0;
	}
	return call();
}

Size RawStack::call( const Index &index ) const
{
	try
	{
		validateType( index, FUNCTION );
		validate( index );
		copy();
	}
	catch( std::exception &e )
	{
		throw;
		return 0;
	}
	Size before = getSize();
	checkForError( lua_pcall( mState, 0, LUA_MULTRET, 0 ) != LUA_OK, std::to_string( index ));
	Size after = getSize();
	return after - before;
}

void RawStack::pushNil() const
{
	try
	{
		allocate();
	}
	catch( std::exception &e )
	{
		return;
	}
	lua_pushnil( mState );
}

void RawStack::pushNumber( const NumberValue &value ) const
{
	try
	{
		allocate();
	}
	catch( std::exception &e )
	{
		return;
	}
	lua_pushnumber( mState, value );
}

void RawStack::pushString( const StringValue &value ) const
{
	try
	{
		allocate();
	}
	catch( std::exception &e )
	{
		return;
	}
	lua_pushstring( mState, value.c_str());
}

void RawStack::replace( const Index &from, const Index &to ) const
{
	AbsoluteIndex realTo;
	AbsoluteIndex realFrom;
	try
	{
		realTo = getAbsoluteIndex( to );
		realFrom = getAbsoluteIndex( from );
		if( realFrom ==realTo )
		{
			return;
		}
		copy( from );
	}
	catch( std::exception &e )
	{
		throw;
		return;
	}
	lua_replace( mState, realTo );
}

void RawStack::move( const Index &from, const Index &to ) const
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
		lua_replace( mState, realTo );
		if( from != -1 )
		{
			remove( realFrom );
		}
	}
	catch( std::exception &e )
	{
		throw;
		return;
	}
}

void RawStack::swap( const Index &one, const Index &two ) const
{
	if( one == two )
	{
		return;
	}
	AbsoluteIndex realOne = getAbsoluteIndex( one );
	AbsoluteIndex realTwo = getAbsoluteIndex( two );
	copy( realTwo );
	replace( realOne, realTwo );
	move( -1, realOne );
}

void RawStack::copy( const Index &from ) const
{
	try
	{
		allocate();
		validate( from );
	}	
	catch( std::exception &e )
	{
		throw;
		return;
	}
	lua_pushvalue( mState, from );
}

void RawStack::insert( const Index &index ) const
{
	try
	{
		allocate();
		validate( index );
	}
	catch( std::exception &e )
	{
		throw;
		return;
	}
	lua_insert( mState, getAbsoluteIndex( index ));
}

void RawStack::remove( const Index &index ) const
{
	try
	{
		validate( index );
	}
	catch( std::exception &e )
	{
		throw;
		return;
	}
	lua_remove( mState, getAbsoluteIndex( index ));
}

void RawStack::erase( const Index &index ) const
{
	AbsoluteIndex realIndex;
	try
	{
		realIndex = getAbsoluteIndex( index );
	}
	catch( std::exception &e )
	{
		throw;
		return;
	}
	pushNil();
	move( -1, realIndex );
}

bool RawStack::iterate( const Index &index ) const
{
	try
	{
		validateType( index, TABLE );
		allocate();
	}
	catch( std::exception &e )
	{
		throw;
		return false;
	}
	return lua_next( mState, index );
}

void RawStack::pop( const Size &space ) const
{
	if( getSize() < space )
	{
		throw Exception::StackError( "Luna::RawStack::pop: tried to pop " + std::to_string( space ) + " elements while the stack has only " + std::to_string( getSize()));
		return;
	}
	lua_pop( mState, space );
}

void RawStack::clear() const noexcept
{
	lua_settop( mState, 0 );
}

bool RawStack::isValid( const Index & index ) const noexcept
{
	return index != 0 && index >= -getSize() && index <= getSize();
}

Type RawStack::getType( const Index &index ) const
{
	try
	{
		validate( index );
	}
	catch( std::exception &e )
	{
		throw;
		return INVALID;
	}
	switch( lua_type( mState, index ))
	{
		case LUA_TNIL:
			return NIL;
			break;

		case LUA_TNUMBER:
			return NUMBER;
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

		case LUA_TUSERDATA:
			return USERDATA;
			break;

		case LUA_TLIGHTUSERDATA:
			return LIGHT_USERDATA;
			break;

		case LUA_TTHREAD:
			return THREAD;
			break;

		default:
			return INVALID;
			break;
	}
}

Size RawStack::getSize() const noexcept
{
	return ( Size )lua_gettop( mState );
}

const State &RawStack::getState() const noexcept
{
	return mState;
}

Index RawStack::getRelativeIndex( const AbsoluteIndex &index ) const
{
	Index returnValue = index - ( getSize() + 1 );
	try
	{
		validate( index );
	}
	catch( std::exception &e )
	{
		throw;
		return 0;
	}
	return returnValue;
}

AbsoluteIndex RawStack::getAbsoluteIndex( const Index &index ) const
{
	AbsoluteIndex returnValue = getSize() + ( index + 1 );
	try
	{
		validate( index );
	}
	catch( std::exception &e )
	{
		throw;
		return 0;
	}
	if( index > 0 )
	{
		return index;
	}
	return returnValue;
}

void RawStack::checkForError( const int &code, const std::string &message ) const
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

void RawStack::allocate( const Size &space ) const
{
	if( !lua_checkstack( mState, space ))
	{
		throw Exception::AllocationError( "Luna::RawStack::allocate: couldn't allocate: " + std::to_string( space ) + " space" );
	}
}

void RawStack::validate( const Index &index ) const
{
	if( !isValid( index ))
	{
		throw Exception::IndexError( "Luna::RawStack::validate: couldn't validate index: " + std::to_string( index ));
	}
}

void RawStack::validateType( const Index &index, const Type &type ) const
{
	Type check = getType( index );
	if( check != type )
	{
		throw Exception::TypeError( "Luna::RawStack::validateType: type " + Auxiliary::getTypeName( check ) + " instead of " + Auxiliary::getTypeName( type ) + " type" );
	}
}

}
