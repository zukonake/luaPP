#include <utility>
//
#include <luna/value.hpp>

namespace Luna
{

TableValue::TableValue( TableValue &&that ) :
	mValue( std::move( that.mValue ))
{

}

TableValue &TableValue::operator=( TableValue &&that )
{
	mValue = std::move( that.mValue );
	return *this;
}

}
