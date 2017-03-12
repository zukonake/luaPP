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

const Number::Value &Number::operator*() const noexcept
{
	return mValue;
}

Type Number::getType() const noexcept
{
	return NUMBER;
}

const Number::Value &Number::get() const noexcept
{
	return mValue;
}

}
