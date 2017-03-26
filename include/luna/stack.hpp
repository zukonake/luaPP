/* luna/stack.hpp
 * Copyleft zukonake
 * Distributed under GNU General Public License Version 3
 */

#pragma once

#include <stdexcept>
#include <memory>
#include <string>
//
#include <luna/rawStack.hpp>

namespace Luna
{
	
class Stack : public RawStack
{
public:
	Stack() = default;
	Stack( Stack &&that );

	virtual ~Stack() = default;

	Stack &operator=( Stack &&that );

	/* load the luna table into the stack
	 * and return it
	 */
	template< typename T = Element >
	T loadGlobal( const std::string &name );
};

template< typename T >
T Stack::loadGlobal( const std::string &name )
{
	RawStack::loadGlobal( name );
	return T( *this );
}

}
