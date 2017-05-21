/**
 * @file luna/stack.hpp
 * @copyright Copyleft zukonake
 * @license Distributed under GNU General Public License Version 3
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
 * Wraps the RawStack with Element handling.
 */
class Stack : public RawStack
{
public:
	/**
	 * Constructs a new Stack, from an existing LuaState.
	 */
	Stack( LuaState const &luaState );
	
	virtual ~Stack() = default;
	
	/**
	 * Accesses a value on RawStack and wraps it in Element object.
	 *
	 * @param index Index of the value.
	 * @return Value of the Element.
	 */
	template< typename T >
	T at( Index const &index = -1 );
	
	/**
	 * Accesses a global value and wraps it in Element object.
	 *
	 * @param name Name of the global.
	 * @return Value of the Element.
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
	RawStack::getGlobal( name );
	return at< T >();
}

}
