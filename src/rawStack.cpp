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
	}
	try
	{
		checkForError( static_cast< ReturnCode >( luaL_loadfile( mLuaState, path.c_str())));
	}
	catch( ... )
	{
		pop();
		throw;
	}
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
	}
	try
	{
		checkForError( static_cast< ReturnCode >( luaL_loadstring( mLuaState, value.c_str())));
	}
	catch( ... )
	{
		pop();
		throw;
	}
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
		validate( index, FUNCTION );
		copy(); //We copy because pcall pops the function later
		if( returnNumber != LuaMultiReturn )
		{
			allocate( returnNumber );
		}
	}
	catch( ... )
	{
		throw;
	}
	Size before = getSize();
	checkForError( static_cast< ReturnCode >( lua_pcall( mLuaState, arguments, returnNumber, 0 )));
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
	}
	throw Exception::NotImplementedError( "Luna::RawStack::pushTable" );
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
	}
	throw Exception::NotImplementedError( "Luna::RawStack::pushUserData" );
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
	}
	lua_pushcfunction( mLuaState, value );
}

void RawStack::pushClosure( FunctionValue const &closure, CaptureSize const &capture )
{
	try
	{
		allocate();
		for( CaptureSize iElement = 0; iElement < capture; iElement++ )
		{
			validate( getSize() - ( Size )( capture - iElement ));
		}
	}
	catch( ... )
	{
		throw;
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
	}
	lua_pushthread( value );
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
	}
	luaL_newlib( mLuaState, library ); //TODO overflow warning
}



void RawStack::pushGlobalTable()
{
	try
	{
		allocate();
	}
	catch( ... )
	{
		throw;
	}
	//TODO check for any crashes
	lua_pushglobaltable( mLuaState );
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
	}
	if( !luaL_newmetatable( mLuaState, name.c_str()))
	{
		throw Exception::StackError( "Luna::RawStack::newMetaTable: meta table: " + name + " already exists in the registry" );
	}
}

void RawStack::newTable( Size const &arrayLength, Size const &mapLength )
{

	try
	{
		allocate();
	}
	catch( ... )
	{
		throw;
	}
	lua_createtable( mLuaState, arrayLength, mapLength );
}

UserDataValue RawStack::newUserData( std::size_t const &size )
{
	try
	{
		allocate();
	}
	catch( ... )
	{
		throw;
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
	}
	return lua_newthread( mLuaState );
}

LuaReference RawStack::newReference( Index const &value, Index const &table )
{
	try
	{
		validate( value ); //TODO will crash if the value is set to LuaRegistryIndex
		validate( table );
	}
	catch( ... )
	{
		throw;
	}
	if( getAbsoluteIndex( value ) != ( Index )getSize()) //The value needs to be at the top of the stack, so we ensure it
	{
		copy( value );
		remove( value );
	}
	return luaL_ref( mLuaState, table );
}

void RawStack::dereference( LuaReference const &reference, Index const &table )
{
	try
	{
		validate( table );
		allocate();
	}
	catch( ... )
	{
		throw;
	}
	if( reference == noReference || reference == nilReference )
	{
		return;
	}
	//TODO check whether the reference exists
	return luaL_unref( mLuaState, table, reference );
}



void RawStack::registerValue( Index const &index, std::string const &name )
{
	try
	{
		copy( index );
	}
	catch( ... )
	{
		throw;
	}
	lua_setglobal( mLuaState, name.c_str());
}



NumberValue RawStack::toNumber( Index const &index ) const
{
	try
	{
		validate( index, NUMBER );
	}
	catch( ... )
	{
		throw;
	}
	return lua_tonumber( mLuaState, index );
}

BooleanValue RawStack::toBoolean( Index const &index ) const
{
	try
	{
		validate( index, BOOLEAN );
	}
	catch( ... )
	{
		throw;
	}
	return lua_toboolean( mLuaState, index );
}

StringValue RawStack::toString( Index const &index ) const
{
	try
	{
		validate( index, STRING );
	}
	catch( ... )
	{
		throw;
	}
	return lua_tostring( mLuaState, index );
}

TableValue RawStack::toTable( Index const &index ) const
{
	throw Exception::NotImplementedError( "Luna::RawStack::toTable" );/*
	TableValue returnValue;
	try
	{
		validate( index, TABLE );
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
	}*/
}

LightUserDataValue RawStack::toLightUserData( Index const &index ) const
{
	try
	{
		validate( index, LIGHT_USER_DATA );
	}
	catch( ... )
	{
		throw;
	}
	return lua_touserdata( mLuaState, index );
}

UserDataValue RawStack::toUserData( Index const &index ) const
{
	try
	{
		validate( index, USER_DATA );
	}
	catch( ... )
	{
		throw;
	}
	return lua_touserdata( mLuaState, index );
}

FunctionValue RawStack::toFunction( Index const &index ) const
{
	try
	{
		validate( index, FUNCTION );
	}
	catch( ... )
	{
		throw;
	}
	return lua_tocfunction( mLuaState, index );
}

ThreadValue RawStack::toThread( Index const &index ) const
{
	try
	{
		validate( index, THREAD );
	}
	catch( ... )
	{
		throw;
	}
	return lua_tothread( mLuaState, index );
}


Size RawStack::getLength( Index const &index ) const
{
	try
	{
		validate( index );
	}
	catch( ... )
	{
		throw;
	}
	return luaL_len( mLuaState, index );
}

Type RawStack::getType( Index const &index ) const
{
	if( index == LuaRegistryIndex )
	{
		return TABLE;
	}
	try
	{
		validate( index );
	}
	catch( ... )
	{
		throw;
	}
	return static_cast< Type >( lua_type( mLuaState, index ));
}



Type RawStack::getTableField( Index const &table )
{
	try
	{
		validate( table, TABLE );
		allocate();
	}
	catch( ... )
	{
		throw;
	}
	if( getType() != STRING && getType() != NUMBER )
	{
		throw Exception::TypeError( "Luna::RawStack::getTableField: type " + Auxiliary::getTypeName( getType()) + " can't be used as a table index/key" );
	}
	return static_cast< Type >( lua_gettable( mLuaState, table ));
}

Type RawStack::getTableField( Index const &table, Index const &index )
{
	try
	{
		validate( table, TABLE );
		allocate();
	}
	catch( ... )
	{
		throw;
	}
	pushNil();
	return NIL;
	return static_cast< Type >( lua_geti( mLuaState, table, index ));
}

Type RawStack::getTableField( Index const &table, std::string const &key )
{
	try
	{
		validate( table, TABLE );
		allocate();
	}
	catch( ... )
	{
		throw;
	}
	return static_cast< Type >( lua_getfield( mLuaState, table, key.c_str()));
}



Type RawStack::getRawTableField( Index const &table )
{
	try
	{
		validate( table, TABLE );
		allocate();
	}
	catch( ... )
	{
		throw;
	}
	if( getType() != STRING && getType() != NUMBER )
	{
		throw Exception::TypeError( "Luna::RawStack::getRawTableField: type " + Auxiliary::getTypeName( getType()) + " can't be used as a table index/key" );
	}
	return static_cast< Type >( lua_rawget( mLuaState, table ));
}

Type RawStack::getRawTableField( Index const &table, Index const &index )
{
	try
	{
		validate( table, TABLE );
		allocate();
	}
	catch( ... )
	{
		throw;
	}
	return static_cast< Type >( lua_rawgeti( mLuaState, table, index ));
}

Type RawStack::getRawTableField( Index const &table, std::string const &key )
{
	Index realTable;
	if( table != LuaRegistryIndex )
	{
		realTable = getAbsoluteIndex( table );
	}
	try
	{
		validate( table == LuaRegistryIndex ? table : realTable, TABLE );
		pushString( key ); //Key at top of the stack used by lua_rawget, unfortunately strings can't be used directly
		allocate();
	}
	catch( ... )
	{
		throw;
	}
	return static_cast< Type >( lua_rawget( mLuaState, realTable));
}



Type RawStack::getMetaField( Index const &index, std::string const &name )
{
	try
	{
		validate( index, TABLE );
		allocate();
	}
	catch( ... )
	{
		throw;
	}
	return static_cast< Type >( luaL_getmetafield( mLuaState, index, name.c_str()));
}

Type RawStack::getMetaTable( std::string const &name )
{
	try
	{
		allocate();
	}
	catch( ... )
	{
		throw;
	}
	return static_cast< Type >( luaL_getmetatable( mLuaState, name.c_str()));
}



Type RawStack::getUserValue( Index const &userData )
{
	try
	{
		validate( userData, USER_DATA );
		allocate();
	}
	catch( ... )
	{
		throw;
	}
	return static_cast< Type >( lua_getuservalue( mLuaState, userData ));
}

Type RawStack::getGlobal( std::string const &name )
{
	try
	{
		allocate();
	}
	catch( ... )
	{
		throw;
	}
	return static_cast< Type >( lua_getglobal( mLuaState, name.c_str()));
}



void RawStack::setTableField( Index const &table )
{
	try
	{
		validate( table, TABLE );
		validate( -1 );
	}
	catch( ... )
	{
		throw;
	}
	if( getType( -2 ) != STRING && getType( -2 ) != NUMBER )
	{
		throw Exception::TypeError( "Luna::RawStack::setTableField: type " + Auxiliary::getTypeName( getType()) + " can't be used as a table index/key" );
	}
	lua_settable( mLuaState, table );
}

void RawStack::setTableField( Index const &table, Index const &index, Index const &value )
{
	try
	{
		validate( table, TABLE );
		copy( value );
	}
	catch( ... )
	{
		throw;
	}
	lua_seti( mLuaState, table, index );
}

void RawStack::setTableField( Index const &table, std::string const &key, Index const &value )
{
	try
	{
		validate( table, TABLE );
		copy( value );
	}
	catch( ... )
	{
		throw;
	}
	lua_setfield( mLuaState, table, key.c_str());
}



void RawStack::setRawTableField( Index const &table )
{
	try
	{
		validate( table, TABLE );
		validate( -1 );
	}
	catch( ... )
	{
		throw;
	}
	if( getType( -2 ) != STRING && getType( -2 ) != NUMBER )
	{
		throw Exception::TypeError( "Luna::RawStack::setRawTableField: type " + Auxiliary::getTypeName( getType()) + " can't be used as a table index/key" );
	}
	lua_rawset( mLuaState, table );
}

void RawStack::setRawTableField( Index const &table, Index const &index, Index const &value )
{
	try
	{
		validate( table, TABLE );
		copy( value );
	}
	catch( ... )
	{
		throw;
	}
	lua_rawseti( mLuaState, table, index );
}

void RawStack::setRawTableField( Index const &table, std::string const &key, Index const &value )
{
	Index realTable = table == LuaRegistryIndex ? table : getAbsoluteIndex( realTable );
	Index realValue = getAbsoluteIndex( value );
	try
	{
		validate( table );
		pushString( key ); //Key at top of the stack used by lua_rawset, unfortunately strings can't be used directly
		copy( realValue );
	}
	catch( ... )
	{
		throw;
	}
	lua_rawset( mLuaState, realTable );
}



void RawStack::setMetaTable( Index const &target, std::string const &metaTable )
{
	try
	{
		validate( target );
		copy( target ); //target needs to be at the top of the stack
	}
	catch( ... )
	{
		throw;
	}
	luaL_setmetatable( mLuaState, metaTable.c_str());
	move( -1, target ); //we replace old target with the new one
}

void RawStack::setMetaTable( Index const &target, Index const &metaTable )
{
	try
	{
		validate( metaTable, TABLE ); 
		validate( target );
		copy( metaTable );
	}
	catch( ... )
	{
		throw;
	}
	lua_setmetatable( mLuaState, target );
}



void RawStack::setUserValue( Index const &userData, Index const &value )
{
	try
	{
		validate( userData, USER_DATA ); 
		validate( value );
		copy( value );
	}
	catch( ... )
	{
		throw;
	}
	lua_setuservalue( mLuaState, userData );
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
	}
	lua_insert( mLuaState, getAbsoluteIndex( index ));
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
	}
	lua_remove( mLuaState, getAbsoluteIndex( index ));
}

void RawStack::erase( Index const &index )
{
	Index realIndex = getAbsoluteIndex( index );
	pushNil();
	move( -1, realIndex );
}

void RawStack::pop( Size const &space )
{
	if( getSize() < space )
	{
		throw Exception::StackError( "Luna::RawStack::pop: tried to pop " + std::to_string( space ) + " elements while the stack has only " + std::to_string( getSize()));
	}
	lua_pop( mLuaState, space );
}

void RawStack::clear() noexcept
{
	lua_settop( mLuaState, 0 );
}



void RawStack::replace( Index const &from, Index const &to )
{
	Index realTo;
	Index realFrom;
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
	}
	lua_copy( mLuaState, realFrom, realTo );
}

void RawStack::move( Index const &from, Index const &to )
{
	Index realFrom;
	Index realTo;
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
			copy( realFrom ); //from needs to be at the top of the stack
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
	}
}

void RawStack::swap( Index const &one, Index const &two )
{
	Index realOne = getAbsoluteIndex( one );
	Index realTwo = getAbsoluteIndex( two );
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
		validate( index, TABLE );
		allocate();
	}
	catch( ... )
	{
		throw;
	}
	return lua_next( mLuaState, index );
}



bool RawStack::isValid( Index const & index ) const noexcept
{
	return ( index != 0 && index >= -(( Index )getSize()) && index <= ( Index )getSize()) || index == LuaRegistryIndex;
}



Index RawStack::getRelativeIndex( Index const &index ) const
{
	if( index == LuaRegistryIndex )
	{
		return index;
	}
	validate( index );
	return index - (( Index )getSize() + 1);
}

Index RawStack::getAbsoluteIndex( Index const &index ) const
{
	if( index == LuaRegistryIndex )
	{
		return index;
	}
	validate( index );
	if( index > 0 )
	{
		return index;
	}
	return ( Index )getSize() + index + 1;
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

void RawStack::validate( Index const &index, Type const &type ) const
{
	Type check = getType( index );
	if( check != type )
	{
		throw Exception::TypeError( "Luna::RawStack::validate: type " + Auxiliary::getTypeName( check ) + " instead of " + Auxiliary::getTypeName( type ) + " type" );
	}
}

void RawStack::checkForError( ReturnCode const &code )
{
	switch( code )
	{
		case OK:
		case YIELD:
			return;
		
		case RUNTIME_ERROR:
			throw Exception::LuaError( "Luna::Auxiliary::checkForError: " + toString());
		
		case SYNTAX_ERROR:
			throw Exception::SyntaxError( "Luna::Auxiliary::checkForError: " + toString());
		
		case MEMORY_ERROR:
			throw Exception::AllocationError( "Luna::Auxiliary::checkForError: " + toString());
		
		case GARBAGE_COLLECTOR_ERROR:
			throw Exception::LuaError( "Luna::Auxiliary::checkForError: " + toString());
		
		case FILE_ERROR:
			throw Exception::FileError( "Luna::Auxiliary::checkForError: " + toString());
		
		case UNKNOWN_ERROR:
		default:
			throw Exception::LuaError( "Luna::Auxiliary::checkForError: " + toString());
	}
}

}
