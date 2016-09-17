#ifndef TABLE_HPP
#define TABLE_HPP

#include <unordered_map>
#include <string>
//
#include <luaPP/typedef.hpp>
#include <luaPP/element/stackElement.hpp>

namespace LW
{

class LuaStack;

class Table : public StackElement
{
public:
	typedef std::unordered_map< std::string, StackElement* > Value;

	Table() = delete;
	Table( LuaStack& luaStack, const Index& index = -1 );

	virtual ~Table();

	template< typename T = StackElement >
	T* at( const std::string& key );

	template< typename T = StackElement >
	T* operator[]( const std::string& key );
private:
	Value mValue;
};

template< typename T = StackElement >
T* Table::at( const std::string& key )
{
	return dynamic_cast< T* >( mValue.at( key ));
}

template< typename T = StackElement >
T* Table::operator[]( const std::string& key )
{
	return dynamic_cast< T* >( mValue.at( key ));
}

}

#endif
