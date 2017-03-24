#include <luna/typedef.hpp>
#include <luna/element/element.hpp>
#include <luna/element/string.hpp>
#include <luna/rawStack.hpp>

namespace Luna
{

String::String( const RawStack &rawStack, const Index &index ) :
	Element( rawStack, index ),
	mValue( rawStack.toString( index ))
{
	
}

String::String( String &&that ) :
	Element( dynamic_cast< Element && >( that )),
	mValue( that.mValue )
{

}

String &String::operator=( String &&that )
{
	static_cast< Element & >( *this ) = static_cast< Element && >( that );
	mValue = that.mValue;
	return *this;
}

const StringValue &String::operator*() const noexcept
{
	return mValue;
}

Type String::getType() const noexcept
{
	return STRING;
}

const StringValue &String::get() const noexcept
{
	return mValue;
}

}
