#include <luna/typedef.hpp>
#include <luna/element/string.hpp>
#include <luna/rawStack.hpp>

namespace Luna
{

String::String( const RawStack &rawStack, const Index &index ) :
	Element( rawStack, index ),
	mValue( rawStack.toString( index ))
{
	
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
