#include <cstddef>
#include <string>
#include <utility>
//
#include <luna/tableValue.hpp>

namespace Luna
{

class Element;

TableValue::TableValue( TableValue &&that ) :
	mValue( std::move( that.mValue ))
{

}

TableValue &TableValue::operator=( TableValue &&that )
{
	mValue = std::move( that.mValue );
	return *this;
}

std::shared_ptr< const Element > &TableValue::operator[]( const std::size_t &index )
{	
	return mValue.first[ index ];
}

std::shared_ptr< const Element > &TableValue::operator[]( const std::string &index )
{
	return mValue.second[ index ];
}

}
