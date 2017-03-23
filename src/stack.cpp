#include <luna/stack.hpp>

namespace Luna
{

Stack::Stack( Stack &&that )
{
	static_cast< RawStack & >( *this ) = std::move( static_cast< RawStack & >( that ));
}

Stack &Stack::operator=( Stack &&that )
{
	static_cast< RawStack & >( *this ) = std::move( static_cast< RawStack & >( that ));
	return *this;
}

const TableValue &Stack::loadGlobals()
{
	std::shared_ptr< const Table > globalTable = loadGlobal< Table >( "luna" );
	static_cast< TableValue >( *this ) = globalTable->get();
	return dynamic_cast< const TableValue & >( *this );
}

}
