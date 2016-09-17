#include <element/table.hpp>
//
#include <stdexcept>
#include <utility>
//
#include <lua5.2/lua.hpp>
//
#include <luaState.hpp>

using namespace LW;

Table::Table( LuaState& luaState, const Index& index ) :
	StackElement( luaState, index )
{
	if( luaState.getType( index ) != LuaType::TABLE )
	{
		throw std::runtime_error( "LW::Table::Table: tried to convert non-table lua type to table" );
	}
	luaState.push( index );
	luaState.pushNil();
	while( luaState.iterate( -2 ))
	{
		std::string key = luaState.getString( -2 );
		luaState.insert(( index + 1 ) + -3 );
		StackElement* value = luaState.evaluateType(( index + 1 ) + -3 );
		mValue[ key ] = value;
	}
	luaState.pop( 1 );
}

Table::~Table()
{
	for( auto& iElement : mValue )
	{
		delete iElement.second;
	}
}

StackElement* Table::operator[]( const std::string& key )
{
	return mValue.at( key );
}
