/* luna/value.hpp
 * Copyleft zukonake
 * Distributed under GNU General Public License Version 3
 */

#pragma once

#include <cstddef>
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

	virtual ~TableValue() = default;

	template< typename T = Element >
	const std::shared_ptr< const T > at( const std::size_t &index ) const
	{
		return std::dynamic_pointer_cast< const T >( mValue.first.at( index ));
	}

	template< typename T = Element >
	const std::shared_ptr< const T > at( const std::string &index ) const
	{
		return std::dynamic_pointer_cast< const T >( mValue.second.at( index ));
	}

	template< typename T = Element >
	std::shared_ptr< const T > at( const std::size_t &index )
	{
		return std::dynamic_pointer_cast< const T >( mValue.first.at( index ));
	}

	template< typename T = Element >
	std::shared_ptr< const T > at( const std::string &index )
	{
		return std::dynamic_pointer_cast< const T >( mValue.second.at( index ));
	}

	template< typename T = Element >
	std::shared_ptr< const T > operator[]( const std::size_t &index )
	{
		return std::dynamic_pointer_cast< const T >( mValue.first[ index ]);
	}

	template< typename T = Element >
	std::shared_ptr< const T > operator[]( const std::string &index )
	{
		return std::dynamic_pointer_cast< const T >( mValue.second[ index ]);
	}
private:
	Value mValue;
};

}
