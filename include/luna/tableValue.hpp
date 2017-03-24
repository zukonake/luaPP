/* luna/tableValue.hpp
 * Copyleft zukonake
 * Distributed under GNU General Public License Version 3
 */

#pragma once

#include <cstddef>
#include <stdexcept>
#include <memory>
#include <utility>
#include <string>
#include <unordered_map>

namespace Luna
{

class Element;

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

	/* operator[] is write-only
	 */
	std::shared_ptr< const Element > &operator[]( const std::size_t &index );
	std::shared_ptr< const Element > &operator[]( const std::string &index );

	/* at is read-only
	 */
	template< typename U = Element >
	const std::shared_ptr< const U > at( const std::size_t &index ) const;
	template< typename U = Element >
	const std::shared_ptr< const U > at( const std::string &index ) const;
private:
	Value mValue;
};

template< typename U >
const std::shared_ptr< const U > TableValue::at( const std::size_t &index ) const
{
	std::shared_ptr< const U > returnValue = std::dynamic_pointer_cast< const U >( mValue.first.at( index ));
	if( returnValue == nullptr )
	{
		throw std::bad_cast();
	}
	return returnValue;
}

template< typename U >
const std::shared_ptr< const U > TableValue::at( const std::string &index ) const
{
	std::shared_ptr< const U > returnValue = std::dynamic_pointer_cast< const U >( mValue.second.at( index ));
	if( returnValue == nullptr )
	{
		throw std::bad_cast();
	}
	return returnValue;
}

}
