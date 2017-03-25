/* luna/stack.hpp
 * Copyleft zukonake
 * Distributed under GNU General Public License Version 3
 */

#pragma once

#include <stdexcept>
#include <memory>
#include <string>
//
#include <luna/exception.hpp>
#include <luna/typedef.hpp>
#include <luna/tableValue.hpp>
#include <luna/rawStack.hpp>
#include <luna/element/element.hpp>
#include <luna/element/nil.hpp>
#include <luna/element/number.hpp>
#include <luna/element/string.hpp>
#include <luna/element/table.hpp>
#include <luna/element/function.hpp>
#include <luna/element/userdata.hpp>
#include <luna/element/lightUserdata.hpp>
#include <luna/element/thread.hpp>

namespace Luna
{
	
class Stack : public RawStack, public TableValue
{
public:
	Stack() = default;
	Stack( Stack &&that );

	virtual ~Stack() = default;

	Stack &operator=( Stack &&that );

	/* Binds a new element to lua stack value
	 */
	template< typename T = Element >
	std::shared_ptr< const T > bind( const Index &index = -1 ) const;

	/* load the luna table into the stack
	 * and return it
	 */
	virtual const TableValue &loadGlobals();
};

template< typename T >
std::shared_ptr< const T > Stack::bind( const Index &index ) const
{
	switch( RawStack::getType())
	{
		case NIL:
			return std::dynamic_pointer_cast< const T >( std::make_shared< const Nil >( *this, index ));

		case NUMBER:
			return std::dynamic_pointer_cast< const T >( std::make_shared< const Number >( *this, index ));

		case STRING:
			return std::dynamic_pointer_cast< const T >( std::make_shared< const String >( *this, index ));

		case TABLE:
			return std::dynamic_pointer_cast< const T >( std::make_shared< const Table >( *this, index ));

		case FUNCTION:
			return std::dynamic_pointer_cast< const T >( std::make_shared< const Function >( *this, index ));

		case USERDATA:
			return std::dynamic_pointer_cast< const T >( std::make_shared< const Userdata >( *this, index ));

		case LIGHT_USERDATA:
			return std::dynamic_pointer_cast< const T >( std::make_shared< const LightUserdata >( *this, index ));

		case THREAD:
			return std::dynamic_pointer_cast< const T >( std::make_shared< const Thread >( *this, index ));

		case INVALID:
		default:
			throw Exception::TypeError( "Luna::Stack::bind: invalid type given" );
			return nullptr;
	}
}

}
