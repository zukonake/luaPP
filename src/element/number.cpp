#include <luna/typedef.hpp>
#include <luna/element/element.hpp>
#include <luna/element/number.hpp>
#include <luna/rawStack.hpp>

namespace Luna
{

Number::Number( Number const &that ) :
	Element( static_cast< Element const & >( that))
{
	
}

Number &Number::operator=( Number const &that )
{
	static_cast< Element & >( *this ) = static_cast< Element const & >( that );
	return *this;
}

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
