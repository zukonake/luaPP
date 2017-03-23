#include <luna/typedef.hpp>
#include <luna/element/number.hpp>
#include <luna/rawStack.hpp>

namespace Luna
{

Number::Number( const RawStack &rawStack, const Index &index ) :
	Element( rawStack, index ),
	mValue( rawStack.toNumber( index ))
{
	
}

const NumberValue &Number::operator*() const noexcept
{
	return mValue;
}

Type Number::getType() const noexcept
{
	return NUMBER;
}

const NumberValue &Number::get() const noexcept
{
	return mValue;
}

}
