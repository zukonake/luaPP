#include <luna/typedef.hpp>
#include <luna/element/element.hpp>
#include <luna/element/boolean.hpp>
#include <luna/rawStack.hpp>

namespace Luna
{

Boolean &Boolean::operator=( BooleanValue const &value )
{
	Element::mRawStack.pushBoolean( value );
	Element::setValue();
	return *this;
}

Boolean::operator BooleanValue() const noexcept
{
	BooleanValue returnValue;
	Element::getValue();
	returnValue = Element::mRawStack.toBoolean();
	Element::mRawStack.pop();
	return returnValue;
}

}
