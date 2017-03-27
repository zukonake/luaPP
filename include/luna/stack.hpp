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
	Stack( Stack &&that );

	virtual ~Stack() = default;

	Stack &operator=( Stack &&that );

	/* load global into stack
	 * and return bound element
	 */
	template< typename T >
	T loadGlobal( const std::string &name );
};

template< typename T >
T Stack::loadGlobal( const std::string &name )
{
	RawStack::loadGlobal( name );
	return T( *this );
}

}
