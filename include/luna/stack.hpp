/* luna/stack.hpp
 * Copyleft zukonake
 * Distributed under GNU General Public License Version 3
 */

#pragma once

#include <luna/rawStack.hpp>
#include <luna/element/table.hpp>

namespace Luna
{
	
class Stack : RawStack
{
public:
	typedef Table::Value Value;

	Stack( Stack &&that );

	virtual ~Stack();

	Stack &operator( Stack &&that );

	using RawStack::doFile;
	using RawStack::doString;

	/* Accesses the mStack value
	 */
	template< typename T = Element >
	std::shared_ptr< const T > at( const std::size_t &index = -1 ) const;
	template< typename T = Element >
	std::shared_ptr< const T > at( const std::string &index = -1 ) const;
	template< typename T = Element >
	std::shared_ptr< const T > operator[]( const std::size_t &index = -1 ) const;
	template< typename T = Element >
	std::shared_ptr< const T > operator[]( const std::string &index = -1 ) const;

	/* Binds a new element to lua stack value
	 */
	std::shared_ptr< const Element > bind( const Index &index = -1 ) const;

	/* Loads a global variable and returns
	 * its bound element
	 */
	template< typename T >
    std::shared_ptr< const T > loadGlobal( const std::string &name ) const;

	/* Loads globals from a given function into
	 * stack and returns the loaded part
	 */
	Value loadGlobals( const Index &index = -1 );
private:
	Value mStack;
};

}
