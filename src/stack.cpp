#include <utility>
#include <memory>
//
#include <luna/stack.hpp>
#include <luna/element/table.hpp>

namespace Luna
{

Stack::Stack( Stack &&that ) :
	RawStack( static_cast< RawStack && >( that ))
{

}

Stack &Stack::operator=( Stack &&that )
{
	static_cast< RawStack & >( *this ) = static_cast< RawStack && >( that );
	return *this;
}

const TableValue &Stack::loadGlobals()
{
	RawStack::loadGlobal( "luna" );
	std::shared_ptr< const Table > globalTable = bind< Table >();
	static_cast< TableValue & >( *this ) = static_cast< const TableValue & >( *globalTable );
	return dynamic_cast< const TableValue & >( *this );
}

}
