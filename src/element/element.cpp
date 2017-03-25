#include <stdexcept>
//
#include <luna/typedef.hpp>
#include <luna/rawStack.hpp>
#include <luna/element/element.hpp>

namespace Luna
{

Element::Element( const RawStack &rawStack, const Index &index ) :
	mRawStack( rawStack ),
	mIndex( rawStack.getAbsoluteIndex( index ))
{
	
}

Element::Element( Element &&that ) :
	mRawStack( that.mRawStack )
{
	mIndex = that.mIndex;
	that.mIndex = 0;
}

Element &Element::operator=( Element &&that )
{
	if( &mRawStack != &that.mRawStack )
	{
		throw std::logic_error( "Luna::Element::operator=: tried to move element within different stack" );
		return *this;
	}
	mIndex = that.mIndex;
	that.mIndex = 0;
	return *this;
}

const Index &Element::getIndex() const noexcept
{
	return mIndex;
}

}
