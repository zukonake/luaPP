/* luna/stack.hpp
 * Copyleft zukonake
 * Distributed under GNU General Public License Version 3
 */

#pragma once

#include <stdexcept>
#include <string>
//
#include <luna/typedef.hpp>
#include <luna/rawStack.hpp>

namespace Luna
{

/**
 * Wraps the Luna::RawStack class into Luna::Element handling.
 */

class Stack : public RawStack
{
public:

	/**
	 * Constructs the stack.
	 * @param luaState State to be used.
	 */

	Stack( LuaState const &luaState );

	virtual ~Stack() = default;

	/**
	 * Accesses a value on Luna::RawStack and wraps it in Luna::Element object.
	 * @param index Index of the value.
	 * @return Value of the Luna::Element.
	 */

	template< typename T >
	T at( Index const &index = -1 );

	/**Accesses a global value and wraps it in Luna::Element object.
	 * @param name Name of the global.
	 * @return Value of the Luna::Element.
	 */	

	template< typename T >
	T loadGlobal( std::string const &name );
};

template< typename T >
T Stack::at( Index const &index )
{
	return T( *this, index );
}

template< typename T >
T Stack::loadGlobal( std::string const &name )
{
	RawStack::loadGlobal( name );
	return at< T >();
}

}
