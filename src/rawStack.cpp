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
	catch( ... )
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
	catch( ... )
	{
		throw;
		return;
	}
	checkForError( luaL_loadstring( mLuaState, value.c_str()), value );
}



Size RawStack::doFile( std::string const &path, Size const &returnNumber, Size const &arguments )
{
	loadFile( path );
	return call( -1, returnNumber, arguments );
}

Size RawStack::doString( std::string const &value, Size const &returnNumber, Size const &arguments )
{
	loadString( value );
	return call( -1, returnNumber, arguments );
}



Size RawStack::call( Index const &index, Size const &returnNumber, Size const &arguments )
{
	try
	{
		validateType( index, FUNCTION );
		copy();
		if( returnNumber != LuaMultiReturn )
		{
			allocate( returnNumber );
		}
	}
	catch( ... )
	{
		throw;
		return 0;
	}
	Size before = getSize();
	checkForError( lua_pcall( mLuaState, arguments, returnNumber, 0 ), std::to_string( index ));
	return getSize() - before;
}

void RawStack::callMetaMethod( Index const &index, std::string const &name )
{
	try
	{
		validate( index );
	}
	catch( ... )
	{
		throw;
		return;
	}
	if( !luaL_callmeta( mLuaState, index, name.c_str()))
	{
		throw Exception::StackError( "Luna::RawStack::callMetaMethod: table at index: " + std::to_string( index ) + " has no meta table or the meta table has no method: " + name );
	}
}



void RawStack::pushNil()
{
	try
	{
		allocate();
	}
	catch( ... )
	{
		throw;
		return;
	}
	lua_pushnil( mLuaState );
}

void RawStack::pushBoolean( BooleanValue const &value )
{
	try
	{
		allocate();
	}
	catch( ... )
	{
		throw;
		return;
	}
	lua_pushboolean( mLuaState, value );
}

void RawStack::pushNumber( NumberValue const &value )
{
	try
	{
		allocate();
	}
	catch( ... )
	{
		throw;
		return;
	}
	lua_pushnumber( mLuaState, value );
}

void RawStack::pushString( StringValue const &value )
{
	try
	{
		allocate();
	}
	catch( ... )
	{
		throw;
		return;
	}
	lua_pushstring( mLuaState, value.c_str());
}

void RawStack::pushTable( TableValue const &value )
{
	try
	{
		allocate();
	}
	catch( ... )
	{
		throw;
		return;
	}
	//TODO
}

void RawStack::pushLightUserData( LightUserDataValue const &value )
{
	try
	{
		allocate();
	}
	catch( ... )
	{
		throw;
		return;
	}
	lua_pushlightuserdata( mLuaState, value );
}

void RawStack::pushUserData( UserDataValue const &value )
{
	try
	{
		allocate();
	}
	catch( ... )
	{
		throw;
		return;
	}
	//TODO
}

void RawStack::pushFunction( FunctionValue const &value )
{
	try
	{
		allocate();
	}
	catch( ... )
	{
		throw;
		return;
	}
	lua_pushcfunction( mLuaState, value );
}

void RawStack::pushClosure( FunctionValue const &closure, CaptureSize const &capture )
{
	try
	{
		allocate();
		for( CaptureSize iElement = 0; iElement < capture; iElement )
		{
			validate( getSize() - ( Size )( capture - iElement ));
		}
	}
	catch( ... )
	{
		throw;
		return;
	}
	lua_pushcclosure( mLuaState, closure, capture );
}

void RawStack::pushThread( ThreadValue const &value )
{
	try
	{
		allocate();
	}
	catch( ... )
	{
		throw;
		return;
	}
	lua_pushthread( mLuaState, value );
}

void RawStack::pushLibrary( Library const &library )
{
	try
	{
		allocate();
	}
	catch( ... )
	{
		throw;
		return;
	}
	lua_newlib( mLuaState, library );
}



void RawStack::loadGlobal( std::string const &name )
{
	try
	{
		allocate();
	}
	catch( ... )
	{
		return;
	}
	if( lua_getglobal( mLuaState, name.c_str()) == NIL )
	{
		throw Exception::StackError( "Luna::RawStack::loadGlobal: couldn't load global:" + name );
	}
}

void RawStack::loadGlobalTable()
{
	try
	{
		allocate();
	}
	catch( ... )
	{
		throw;
		return;
	}
	//TODO check for any crashes
	lua_getglobaltable( mLuaState );
}



void RawStack::newMetaTable( std::string const &name )
{
	try
	{
		allocate();
	}
	catch( ... )
	{
		throw;
		return;
	}
	if( !luaL_newmetatable( mLuaState, name.c_str()))
	{
		throw Exception::StackError( "Luna::RawStack::newMetaTable: meta table: " + name + " already exists in the registry" );
	}
}

void RawStack::newTable( Size const &arrayLength = 0, Size const &mapLength = 0 )
{

	try
	{
		allocate();
	}
	catch( ... )
	{
		throw;
		return;
	}
	lua_createtable( mLuaState, arrayLength, mapLength );
}

UserDataValue RawStack::newUserData( const std::size_t &size )
{
	try
	{
		allocate();
	}
	catch( ... )
	{
		throw;
		return nullptr;
	}
	return lua_newuserdata( mLuaState, size );
}

ThreadValue RawStack::newThread()
{
	try
	{
		allocate();
	}
	catch( ... )
	{
		throw;
		return nullptr;
	}
	return lua_newthread( mLuaState );
}

LuaReference newReference( const Index &value, const Index &table )
{
	try
	{
		validate( value );
		validate( table );
	}
	catch( ... )
	{
		throw;
		return noReference;
	}
	if( getAbsoluteIndex( value ) != getSize())
	{
		copy( value );
		remove( value );
	}
	return luaL_ref( mLuaState, table );
}

void deReference( const LuaReference &reference, const Index &table )
{
	try
	{
		validate( table );
		allocate();
	}
	catch( ... )
	{
		throw;
		return;
	}
	if( reference == noReference || reference == nilReference )
	{
		return;
	}
	//TODO check whether the reference exists
	return luaL_unref( mLuaState, table, reference );
}



void registerValue( Index const &index, std::string const &name )
{
	try
	{
		copy( index );
	}
	catch( ... )
	{
		throw;
		return;
	}
	lua_setglobal( mLuaState, name.c_str());
}



NumberValue RawStack::toNumber( Index const &index ) const
{
	try
	{
		validateType( index, NUMBER );
	}
	catch( ... )
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
	catch( ... )
	{
		throw;
		return false;
	}
	return lua_toboolean( mLuaState, index );
}

StringValue RawStack::toString( Index const &index ) const
{
	try
	{
		validateType( index, STRING );
	}
	catch( ... )
	{
		throw;
		return "";
	}
	return lua_tostring( mLuaState, index );
}

/* TODO
TableValue RawStack::toTable( Index const &index ) const
{
	TableValue returnValue;
	try
	{
		validateType( index, TABLE );
	}
	catch( ... )
	{
		throw;
		return "";
	}
	pushNil();
	while( iterate( index ));
	{
		if( getType() == NUMBER )
		{
			returnValue.operator[]( toNumber()) =
	}
}
*/

LightUserDataValue RawStack::toLightUserData( Index const &index ) const
{
	try
	{
		validateType( index, LIGHT_USER_DATA );
	}
	catch( ... )
	{
		throw;
		return nullptr;
	}
	return lua_touserdata( mLuaState, index );
}

UserDataValue RawStack::toUserData( Index const &index ) const
{
	try
	{
		validateType( index, USER_DATA );
	}
	catch( ... )
	{
		throw;
		return nullptr;
	}
	return lua_touserdata( mLuaState, index );
}

FunctionValue RawStack::toFunction( Index const &index ) const
{
	try
	{
		validateType( index, FUNCTION );
	}
	catch( ... )
	{
		throw;
		return nullptr;
	}
	return lua_tocfunction( mLuaState, index );
}

ThreadValue RawStack::toThread( Index const &index ) const
{
	try
	{
		validateType( index, THREAD );
	}
	catch( ... )
	{
		throw;
		return nullptr;
	}
	return lua_tothread( mLuaState, index );
}


Size getLength( Index const &index ) const;
{
	try
	{
		validate( index );
	}
	catch( ... )
	{
		throw;
		return 0;
	}
	return luaL_len( mLuaState, index );
}

Type RawStack::getType( Index const &index ) const
{
	try
	{
		validate( index );
	}
	catch( ... )
	{
		throw;
		return INVALID;
	}
	return lua_type( mLuaState, index );
}



void RawStack::copy( Index const &from )
{
	try
	{
		allocate();
		validate( from );
	}	
	catch( ... )
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
	catch( ... )
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
	catch( ... )
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
	catch( ... )
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
	catch( ... )
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
	catch( ... )
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
