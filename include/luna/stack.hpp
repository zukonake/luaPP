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
	
class Stack : public RawStack
{
public:
	Stack( LuaState const &luaState );

	virtual ~Stack() = default;

	template< typename T >
	T at( Index const &index = -1 );

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
