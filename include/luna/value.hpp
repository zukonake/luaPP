/* luna/value.hpp
 * Copyleft zukonake
 * Distributed under GNU General Public License Version 3
 */

#pragma once

#include <cstddef>
#include <stdexcept>
#include <memory>
#include <string>
#include <utility>
#include <unordered_map>

namespace Luna
{

class Element;

typedef float NumberValue;
typedef std::string StringValue;
class TableValue
{
public:
	typedef	std::pair<
			std::unordered_map< std::size_t, std::shared_ptr< const Element > >,
			std::unordered_map< std::string, std::shared_ptr< const Element > > > Value;

	TableValue() = default;
	TableValue( const TableValue &that ) = default;
	TableValue( TableValue &&that );

	virtual ~TableValue() = default;

	TableValue &operator=( const TableValue &that ) = default;
	TableValue &operator=( TableValue &&that );
	template< typename T = Element >
	std::shared_ptr< const T > operator[]( const std::size_t &index );
	template< typename T = Element >
	std::shared_ptr< const T > operator[]( const std::string &index );

	template< typename T = Element >
	const std::shared_ptr< const T > at( const std::size_t &index ) const;
	template< typename T = Element >
	const std::shared_ptr< const T > at( const std::string &index ) const;
private:
	Value mValue;
};

template< typename T >
std::shared_ptr< const T > TableValue::operator[]( const std::size_t &index )
{
	std::shared_ptr< const T > returnValue = std::dynamic_pointer_cast< const T >( mValue.first[ index ]);
	if( returnValue == nullptr )
	{
		throw std::logic_error( "Luna::TableValue::operator[]: invalid type given" );
	}
	return returnValue;
}

template< typename T >
std::shared_ptr< const T > TableValue::operator[]( const std::string &index )
{
	std::shared_ptr< const T > returnValue = std::dynamic_pointer_cast< const T >( mValue.second[ index ]);
	if( returnValue == nullptr )
	{
		throw std::logic_error( "Luna::TableValue::operator[]: invalid type given" );
	}
	return returnValue;
}
template< typename T >
const std::shared_ptr< const T > TableValue::at( const std::size_t &index ) const
{
	std::shared_ptr< const T > returnValue = std::dynamic_pointer_cast< const T >( mValue.first.at( index ));
	if( returnValue == nullptr )
	{
		throw std::logic_error( "Luna::TableValue::at: invalid type given" );
	}
	return returnValue;
}

template< typename T >
const std::shared_ptr< const T > TableValue::at( const std::string &index ) const
{
	std::shared_ptr< const T > returnValue = std::dynamic_pointer_cast< const T >( mValue.second.at( index ));
	if( returnValue == nullptr )
	{
		throw std::logic_error( "Luna::TableValue::at: invalid type given" );
	}
	return returnValue;
}


}
