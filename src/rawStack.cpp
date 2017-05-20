#include <iostream>
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
		validateReturnCode( static_cast< ReturnCode >( luaL_loadfile( mLuaState, path.c_str())));
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
		validateReturnCode( static_cast< ReturnCode >( luaL_loadstring( mLuaState, value.c_str())));
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


//TODO change arg and return sequence
Size RawStack::call( Index const &index, Size const &returnNumber, Size const &arguments )
{
	Size before = getSize() - arguments;
	try
	{
		validate( index, FUNCTION );
		validateIndex( arguments + 1 ); //TODO
		copy( index ); //We copy because pcall pops the function later
		insert(getSize() - arguments); //The function needs to be before arguments
	}
	catch( ... )
	{
		throw;
	}
	validateReturnCode( static_cast< ReturnCode >( lua_pcall( mLuaState, arguments, LuaMultiReturn, 0 )));
	Size returned = getSize() - before;
	if( returned != returnNumber && ( Index )returnNumber != LuaMultiReturn )
	{
		throw Exception::UnexpectedReturnError( "Luna::RawStack::call: returned " +
			std::to_string( returned ) + " values instead of " +
			std::to_string( returnNumber ));
	}
	return returned;
}

void RawStack::callMetaMethod( Index const &index, std::string const &name )
{
	try
	{
		validate( index, TABLE );
	}
	catch( ... )
	{
		throw;
	}
	if( !luaL_callmeta( mLuaState, index, name.c_str()))
	{
		throw Exception::StackError( "Luna::RawStack::callMetaMethod: table at index: " +
			std::to_string( index ) + " has no meta table or the meta table has no method: " + name );
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
		validateIndex( capture + 1 ); //TODO not sure
		allocate();
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
		pop();
		throw Exception::ReservedNameError( "Luna::RawStack::newMetaTable: meta table: " +
			name + " already exists in the registry" );
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
		validateIndex( value ); //TODO will crash if the value is set to LuaRegistryIndex
		validate( table, TABLE );
	}
	catch( ... )
	{
		throw;
	}
	Index realTable = getAbsoluteIndex( table );
	Index realValue = getAbsoluteIndex( value );
	if( realValue != ( Index )getSize()) //The value needs to be at the top of the stack
	{
		copy( value );
		remove( value ); // We remove the original value
	}
	LuaReference returnValue = luaL_ref( mLuaState, realTable );
	return returnValue;
}

void RawStack::freeReference( LuaReference const &reference, Index const &table )
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
	if( reference == noReference || reference == nilReference )
	{
		return;
	}
	//TODO check whether the reference exists
	//TODO change element table from stack from registry to some custom one?
	//TODO set/get table field should pop the value?
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
		validateIndex( index );
	}
	catch( ... )
	{
		throw;
	}
	//TODO luaL_len can result in an error, see manual
	return luaL_len( mLuaState, index );
}

Type RawStack::getType( Index const &index ) const
{
	if( index == LuaRegistryIndex )
	{
		return TABLE;
	}
	return static_cast< Type >( lua_type( mLuaState, index ));
}



Type RawStack::getTableField( Index const &table )
{
	try
	{
		validate( table, TABLE );
		validateIndex( -1 );
		allocate();
	}
	catch( ... )
	{
		throw;
	}
	if( getType() != STRING && getType() != NUMBER )
	{
		throw Exception::TypeError( "Luna::RawStack::getTableField: type " +
			Auxiliary::getTypeName( getType()) + " can't be used as a table index/key" );
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
} //TODO check getters and setters types (test)



Type RawStack::getRawTableField( Index const &table )
{
	try
	{
		validate( table, TABLE );
		validateIndex( -1 );
		allocate();
	}
	catch( ... )
	{
		throw;
	}
	if( getType() != STRING && getType() != NUMBER )
	{
		throw Exception::TypeError( "Luna::RawStack::getRawTableField: type " +
			Auxiliary::getTypeName( getType()) + " can't be used as a table index/key" );
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
	Index realTable = getAbsoluteIndex( table );
	try
	{
		validate( table, TABLE );
		pushString( key ); // Key at top of the stack used by lua_rawget
						   // unfortunately strings can't be used directly
		allocate();
	}
	catch( ... )
	{
		throw;
	} //TODO try catch might not be needed everywhere
	return static_cast< Type >( lua_rawget( mLuaState, realTable ));
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
		validateIndex( -1 );
		validateIndex( -2 );
	}
	catch( ... )
	{
		throw;
	}
	if( getType( -2 ) != STRING && getType( -2 ) != NUMBER )
	{
		throw Exception::TypeError( "Luna::RawStack::setTableField: type " +
			Auxiliary::getTypeName( getType()) + " can't be used as a table index/key" );
	}
	lua_settable( mLuaState, table );
}

void RawStack::setTableField( Index const &table, Index const &index, Index const &value )
{
	Index realTable = getAbsoluteIndex( table );
	try
	{
		validate( table, TABLE );
		copy( value );
	}
	catch( ... )
	{
		throw;
	}
	lua_seti( mLuaState, realTable, index );
}

void RawStack::setTableField( Index const &table, std::string const &key, Index const &value )
{
	Index realTable = getAbsoluteIndex( table );
	try
	{
		validate( table, TABLE );
		copy( value );
	}
	catch( ... )
	{
		throw;
	}
	lua_setfield( mLuaState, realTable, key.c_str());
}



void RawStack::setRawTableField( Index const &table )
{
	try
	{
		validate( table, TABLE );
		validateIndex( -1 );
		validateIndex( -2 );
	}
	catch( ... )
	{
		throw;
	}
	if( getType( -2 ) != STRING && getType( -2 ) != NUMBER )
	{
		throw Exception::TypeError( "Luna::RawStack::setRawTableField: type " + 
			Auxiliary::getTypeName( getType()) + " can't be used as a table index/key" );
	}
	lua_rawset( mLuaState, table );
}

void RawStack::setRawTableField( Index const &table, Index const &index, Index const &value )
{
	Index realTable = getAbsoluteIndex( table );
	try
	{
		validate( table, TABLE );
		copy( value );
	}
	catch( ... )
	{
		throw;
	}
	lua_rawseti( mLuaState, realTable, index );
}

void RawStack::setRawTableField( Index const &table, std::string const &key, Index const &value )
{
	Index realTable = getAbsoluteIndex( table );
	Index realValue = getAbsoluteIndex( value );
	try
	{
		validate( table, TABLE );
		validateIndex( value );
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
	Index realTarget = getAbsoluteIndex( target );
	try
	{
		validate( target, TABLE );
		validate( metaTable, TABLE ); 
		copy( metaTable );
	}
	catch( ... )
	{
		throw;
	}
	lua_setmetatable( mLuaState, realTarget );
}



void RawStack::setUserValue( Index const &userData, Index const &value )
{
	Index realUserData = getAbsoluteIndex( userData );
	try
	{
		validate( userData, USER_DATA );
		copy( value );
	}
	catch( ... )
	{
		throw;
	}
	lua_setuservalue( mLuaState, realUserData );
}



void RawStack::copy( Index const &from )
{
	try
	{
		validateIndex( from );
		allocate();
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
		validateIndex( index );
		allocate();
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
		validateIndex( index );
	}
	catch( ... )
	{
		throw;
	}
	lua_remove( mLuaState, getAbsoluteIndex( index ));
}

void RawStack::erase( Index const &index )
{
	validateIndex( index );
	Index realIndex = getAbsoluteIndex( index );
	pushNil();
	move( -1, realIndex );
}

void RawStack::pop( Size const &space )
{
	if( getSize() < space )
	{
		throw Exception::StackError( "Luna::RawStack::pop: tried to pop " + 
			std::to_string( space ) + " elements while the stack has only " + std::to_string( getSize()));
	}
	lua_pop( mLuaState, space );
}

void RawStack::clear() noexcept
{
	lua_settop( mLuaState, 0 );
}



void RawStack::replace( Index const &from, Index const &to )
{
	Index realTo = getAbsoluteIndex( to );
	Index realFrom = getAbsoluteIndex( from );
	try
	{
		validateIndex( to );
		validateIndex( from );
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
	Index realTo = getAbsoluteIndex( to );
	Index realFrom = getAbsoluteIndex( from );
	try
	{
		validateIndex( to );
		validateIndex( from );
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
	validateIndex( one );
	validateIndex( two );
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
	return ( index != 0 &&
		index >= -(( Index )getSize()) &&
		index <= ( Index )getSize()) ||
		index == LuaRegistryIndex;
}



Index RawStack::getRelativeIndex( Index const &index ) const noexcept
{
	if( index == LuaRegistryIndex )
	{
		return index;
	}
	return index - (( Index )getSize() + 1);
}

Index RawStack::getAbsoluteIndex( Index const &index ) const noexcept
{
	if( index == LuaRegistryIndex )
	{
		return index;
	}
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
		throw Exception::AllocationError( "Luna::RawStack::allocate: couldn't allocate: " +
			std::to_string( space ) + " space" );
	}
}

//TODO this function might actually be an overkill
void RawStack::validate( Index const &index, Type const &type ) const
{
	validateIndex( index );
	validateType( index, type ); 
}

void RawStack::validateIndex( Index const &index ) const
{
	if( !isValid( index ))
	{
		throw Exception::IndexError( "Luna::RawStack::validateIndex: couldn't validate index: " +
			std::to_string( index ));
	}
}

void RawStack::validateType( Index const &index, Type const &type ) const
{
	Type check = getType( index );
	if( check != type )
	{
		throw Exception::TypeError( "Luna::RawStack::validateType: type " +
			Auxiliary::getTypeName( check ) + " instead of " +
			Auxiliary::getTypeName( type ) + " type" );
	}
}

void RawStack::validateReturnCode( ReturnCode const &code )
{
	switch( code )
	{
		case OK:
		case YIELD:
			return;
		
		case RUNTIME_ERROR:
			throw Exception::LuaError( "Luna::Auxiliary::validateReturnCode: " + toString());
		
		case SYNTAX_ERROR:
			throw Exception::SyntaxError( "Luna::Auxiliary::validateReturnCode: " + toString());
		
		case MEMORY_ERROR:
			throw Exception::AllocationError( "Luna::Auxiliary::validateReturnCode: " + toString());
		
		case GARBAGE_COLLECTOR_ERROR:
			throw Exception::LuaError( "Luna::Auxiliary::validateReturnCode: " + toString());
		
		case FILE_ERROR:
			throw Exception::FileError( "Luna::Auxiliary::validateReturnCode: " + toString());
		
		case UNKNOWN_ERROR:
		default:
			throw Exception::LuaError( "Luna::Auxiliary::validateReturnCode: " + toString());
	}
}

}
