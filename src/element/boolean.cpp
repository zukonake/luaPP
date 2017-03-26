#include <luna/typedef.hpp>
#include <luna/element/element.hpp>
#include <luna/element/boolean.hpp>
#include <luna/rawStack.hpp>

namespace Luna
{

Boolean::Boolean( const RawStack &rawStack, const Index &index ) :
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

Boolean::operator const bool &() const noexcept
{
	return mValue;
}

}
