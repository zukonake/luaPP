#include <luna/typedef.hpp>
#include <luna/element/element.hpp>
#include <luna/element/number.hpp>
#include <luna/rawStack.hpp>

namespace Luna
{

Number &Number::operator=( NumberValue const &value )
{
	Element::mRawStack.pushNumber( value );
	Element::setValue();
	return *this;
}

Number::operator NumberValue() const noexcept
{
	NumberValue returnValue;
	Element::getValue();
	returnValue = Element::mRawStack.toNumber();
	Element::mRawStack.pop();
	return returnValue;
}

}
