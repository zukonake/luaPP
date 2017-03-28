#include <luna/typedef.hpp>
#include <luna/element/element.hpp>
#include <luna/element/string.hpp>
#include <luna/rawStack.hpp>

namespace Luna
{

String::String( RawStack &rawStack, Index const &index ) :
	Element( rawStack, index ),
	StringValue( rawStack.toString( index ))
{
	
}

String::String( String &&that ) :
	Element( dynamic_cast< Element && >( that )),
	StringValue( dynamic_cast< StringValue && >( that ))
{

}

String &String::operator=( String &&that )
{
	static_cast< Element & >( *this ) = static_cast< Element && >( that );
	static_cast< StringValue & >( *this ) = static_cast< StringValue && >( that );
	return *this;
}

}
