#include <utility>
#include <string>
//
#include <lua.hpp>
//
#include <luna/exception.hpp>
#include <luna/auxiliary.hpp>
#include <luna/rawStack.hpp>

namespace Luna
{

RawStack::RawStack() :
	mState()
{
	
}

RawStack::RawStack( RawStack &&that )
{	
	mState = std::move( that.mState );
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
	if( luaL_loadfile( mState, path.c_str()) != LUA_OK )
	{
		throw std::runtime_error( "Luna::RawStack::loadFile: " + toString());
	}
}

void RawStack::loadString( const std::string &path ) const
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
	if( luaL_loadstring( mState, path.c_str()) != LUA_OK )
	{
		throw std::runtime_error( "Luna::RawStack::loadString: " + toString());
	}
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
		throw std::runtime_error( "Luna::RawStack::loadGlobal: loaded a global nil value" );
	}
}

Number::Value RawStack::toNumber( const Index &index ) const
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

String::Value RawStack::toString( const Index &index ) const
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
	}
	catch( std::exception &e )
	{
		throw;
		return 0;
	}
	Size before = getSize();
	if( lua_pcall( mState, 0, LUA_MULTRET, 0 ) != LUA_OK )
	{
		throw std::runtime_error( "Luna::RawStack::call: pcall error: " + toString());
	}
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

void RawStack::pushNumber( const Number::Value &value ) const
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

void RawStack::pushString( const String::Value &value ) const
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
		throw std::runtime_error( "Luna::RawStack::pop: tried to pop " + std::to_string( space ) + " elements while the stack has only " + std::to_string( getSize()));
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

void RawStack::allocate( const Size &space ) const
{
	if( !lua_checkstack( mState, space ))
	{
		throw std::bad_alloc();
	}
}

void RawStack::validate( const Index &index ) const
{
	if( !isValid( index ))
	{
		throw std::out_of_range( "Luna::RawStack::validate: couldn't validate index: " + std::to_string( index ));
	}
}

void RawStack::validateType( const Index &index, const Type &type ) const
{
	Type check = getType( index );
	if( check != type )
	{
		throw Exception::InvalidType( "Luna::RawStack::validateType: type " + Auxiliary::getTypeName( check ) + " instead of " + Auxiliary::getTypeName( type ) + " type" );
	}
}

}
