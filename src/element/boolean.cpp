#include <luna/typedef.hpp>
#include <luna/element/element.hpp>
#include <luna/element/boolean.hpp>
#include <luna/rawStack.hpp>

namespace Luna
{

Boolean::Boolean( RawStack &rawStack, Index const &index ) :
	Element( rawStack, index ),
	mValue( rawStack.toBoolean( index ))
{
	
}

Boolean::Boolean( Boolean &&that ) :
	Element( dynamic_cast< Element && >( that )),
	mValue( that.mValue )
{

}

Boolean &Boolean::operator=( Boolean &&that )
{
	static_cast< Element & >( *this ) = static_cast< Element && >( that );
	mValue = that.mValue;
	return *this;
}

Boolean::operator bool const &() const noexcept
{
	return mValue;
}

}
