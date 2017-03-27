#include <luna/typedef.hpp>
#include <luna/element/element.hpp>
#include <luna/element/number.hpp>
#include <luna/rawStack.hpp>

namespace Luna
{

Number::Number( RawStack const &rawStack, Index const &index ) :
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

Number::operator NumberValue const &() const noexcept
{
	return mValue;
}

}
