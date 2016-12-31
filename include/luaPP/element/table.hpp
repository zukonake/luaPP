//2016-luaPP zukonake

#ifndef LPP_TABLE_HPP
#define LPP_TABLE_HPP

#include <cstddef>
#include <unordered_map>
#include <string>
//
#include <nonCopyable.hpp>
//
#include <luaPP/typedef.hpp>
#include <luaPP/element/stackElement.hpp>

namespace LPP
{

class LuaStack;

class Table : public StackElement, virtual NonCopyable
{
public:
	typedef std::pair< std::unordered_map< std::size_t, const StackElement* >, std::unordered_map< std::string, const StackElement* > > Value;

	Table() = delete;
	Table( const LuaStack& luaStack, const Index& index = -1 );

	virtual ~Table();

	template< typename T = StackElement >
	const T* at( const std::string& key ) const;

	template< typename T = StackElement >
	const T* at( const std::size_t& key ) const;

	template< typename T = StackElement >
	const T* operator[]( const std::string& key ) const;

	template< typename T = StackElement >
	const T* operator[]( const std::size_t& key ) const;

	operator const Value&() const noexcept;

	const Value& get() const noexcept;
private:
	Value mValue;
};

template< typename T = StackElement >
const T* Table::at( const std::string& key ) const
{
	return dynamic_cast< const T* >( mValue.second.at( key ));
}

template< typename T = StackElement >
const T* Table::at( const std::size_t& key ) const
{
	return dynamic_cast< const T* >( mValue.first.at( key ));
}

template< typename T = StackElement >
const T* Table::operator[]( const std::string& key ) const
{
	return dynamic_cast< const T* >( mValue.second.at( key ));
}

template< typename T = StackElement >
const T* Table::operator[]( const std::size_t& key ) const
{
	return dynamic_cast< const T* >( mValue.first.at( key ));
}

}

#endif
