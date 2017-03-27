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
	RawStack::operator=( static_cast< RawStack && >( that ));
	return *this;
}

}
