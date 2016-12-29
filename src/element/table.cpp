//2016-luaPP zukonake

#include <luaPP/element/table.hpp>
//
#include <stdexcept>
//
#include <luaPP/luaStack.hpp>

using namespace LPP;

Table::Table( const LuaStack& luaStack, const Index& index ) :
	StackElement( luaStack, index )
{
	if( luaStack.getType( index ) != LuaType::TABLE )
	{
		throw std::runtime_error( "LW::Table::Table: tried to convert a non-table lua type to table" );
	}
	luaStack.push( index );
	luaStack.pushNil();
	while( luaStack.iterate())
	{
		std::string key = luaStack.getString( -2 );
		luaStack.insert(( index + 1 ) + -3 );
		const StackElement* value = luaStack.get(( index + 1 ) + -3 );
		mValue[ key ] = value;
	}
	luaStack.pop();
}

Table::~Table()
{
	for( auto& iElement : mValue )
	{
		delete iElement.second;
	}
}

const Table::Value& Table::get() const noexcept
{
	return mValue;
}
