#include <luna/typedef.hpp>
#include <luna/element/element.hpp>
#include <luna/element/string.hpp>
#include <luna/rawStack.hpp>

namespace Luna
{

String &String::operator=( StringValue const &value )
{
	Element::mRawStack.pushString( value );
	Element::setValue();
	return *this;
}

String::operator StringValue() const noexcept
{
	StringValue returnValue;
	Element::getValue();
	returnValue = Element::mRawStack.toString();
	Element::mRawStack.pop();
	return returnValue;
}

}
