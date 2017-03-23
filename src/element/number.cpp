#include <luna/typedef.hpp>
#include <luna/value.hpp>
#include <luna/element/element.hpp>
#include <luna/element/number.hpp>
#include <luna/rawStack.hpp>

namespace Luna
{

Number::Number( const RawStack &rawStack, const Index &index ) :
	Element( rawStack, index ),
	mValue( rawStack.toNumber( index ))
{
	
}

Number::Number( Number &&that ) :
	Element( dynamic_cast< Element && >( that )),
	mValue( that.mValue )
{

}

Number &Number::operator=( Number &&that )
{
	static_cast< Element & >( *this ) = static_cast< Element && >( that );
	mValue = that.mValue;
	return *this;
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
