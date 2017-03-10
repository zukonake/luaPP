#include <luna/rawStack.hpp>
#include <luna/element/element.hpp>

namespace Luna
{

Element::Element( const RawStack &rawStack, const Index &index ) :
	mRawStack( rawStack ),
	mIndex( rawStack.getAbsoluteIndex( index ))
{
	
}

Element::~Element()
{
	if( mIndex != 0 )
	{
		mRawStack.erase( mIndex );
	}
}

const Index &Element::getIndex() const noexcept
{
	return mIndex;
}


}
