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
		if( luaStack.getType( -2 ) == LuaType::NUMBER )
		{
			std::size_t key = luaStack.getNumber( -2 );
			luaStack.insert(( index + 1 ) + -3 );
			const StackElement* value = luaStack.get(( index + 1 ) + -3 );
			mValue.first[ key ] = value;
		}
		else if( luaStack.getType( -2 ) == LuaType::STRING )
		{
			std::string key = luaStack.getString( -2 );
			luaStack.insert(( index + 1 ) + -3 );
			const StackElement* value = luaStack.get(( index + 1 ) + -3 );
			mValue.second[ key ] = value;
		}
	}
	luaStack.pop();
}

Table::~Table()
{
	for( auto& iElement : mValue.first )
	{
		delete iElement.second;
	}
	for( auto& iElement : mValue.second )
	{
		delete iElement.second;
	}
}

Table::operator const Table::Value&() const noexcept
{
	return mValue;
}

const Table::Value& Table::get() const noexcept
{
	return mValue;
}
