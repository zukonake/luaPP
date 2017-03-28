/* luna/element/table.hpp
 * Copyleft zukonake
 * Distributed under GNU General Public License Version 3
 */

#pragma once

#include <cstddef>
#include <string>
//
#include <luna/typedef.hpp>
#include <luna/element/element.hpp>

namespace Luna
{

class RawStack;

class Table : public Element, TableValue
{
public:
	explicit Table( RawStack &rawStack, Index const &index = -1 );
	Table( Table const &that ) = default;
	Table( Table &&that );

	virtual ~Table() = default;

	Table &operator=( Table const &that ) = default;
	Table &operator=( Table &&that );
	Index &operator[]( const std::size_t &index ); //TODO insert values in stack
	Index &operator[]( const std::string &key );

	template< typename T >
	T at( const std::size_t &index ) const;
	template< typename T >
	T at( const std::string &key ) const;
};

template< typename T >
T Table::at( const std::size_t &index ) const
{
	return T( Element::mRawStack, TableValue::first.at( index ));
}

template< typename T >
T Table::at( const std::string &key ) const
{
	return T( Element::mRawStack, TableValue::second.at( key ));
}

}
