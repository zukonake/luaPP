//2016-luaPP zukonake

#ifndef TABLE_HPP
#define TABLE_HPP

#include <unordered_map>
#include <string>
//
#include <luaPP/nonCopyable.hpp>
#include <luaPP/typedef.hpp>
#include <luaPP/element/stackElement.hpp>

namespace LPP
{

class LuaStack;

class Table : public StackElement, virtual NonCopyable
{
public:
	typedef std::unordered_map< std::string, const StackElement* > Value;

	Table() = delete;
	Table( const LuaStack& luaStack, const Index& index = -1 );

	virtual ~Table();

	template< typename T = StackElement >
	const T* at( const std::string& key ) const;

	template< typename T = StackElement >
	const T* operator[]( const std::string& key ) const;
private:
	Value mValue;
};

template< typename T = StackElement >
const T* Table::at( const std::string& key ) const
{
	return dynamic_cast< const T* >( mValue.at( key ));
}

template< typename T = StackElement >
const T* Table::operator[]( const std::string& key ) const
{
	return dynamic_cast< const T* >( mValue.at( key ));
}

}

#endif
