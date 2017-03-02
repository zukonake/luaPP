/* luna/element/table.hpp
 * Copyleft zukonake
 * Distributed under GNU General Public License Version 3
 */

#pragma once

#include <luna/typedef.hpp>
#include <luna/element/element.hpp>

namespace Luna
{
	
class Table : public Element
{
public:
	typedef std::pair<
		std::unordered_map< Index, std::shared_ptr< const Element > >,
		std::unordered_map< std::string, std::shared_ptr< const Element > > > Value;

	explicit Table( const Stack &stack, const Index &index = -1 );
	Table( Table &&that );

	virtual ~Table() = default;

	Table &operator( Table &&that );

	template< typename T = Element >
	std::shared_ptr< const T > at( const std::size_t &index = -1 ) const;
	template< typename T = Element >
	std::shared_ptr< const T > at( const std::string &index = -1 ) const;
	template< typename T = Element >
	std::shared_ptr< const T > operator[]( const std::size_t &index = -1 ) const;
	template< typename T = Element >
	std::shared_ptr< const T > operator[]( const std::string &index = -1 ) const;

	virtual Type getType() const noexcept override;

	Value get() const noexcept;
private:
	Value mValue;
};

}
