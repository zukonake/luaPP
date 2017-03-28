#include <stdexcept>
//
#include <luna/typedef.hpp>
#include <luna/rawStack.hpp>
#include <luna/element/element.hpp>

namespace Luna
{

Element::Element( RawStack &rawStack  ) :
	mRawStack( rawStack ),
	mReference( rawStack.newReference( LuaRegistryIndex, -1 ))
{
	
}

Element::Element( RawStack &rawStack, LuaReference const &reference ) :
	mRawStack( rawStack ),
	mReference( reference )
{
	
}

Element::Element( Element &&that ) :
	mRawStack( that.mRawStack ),
	mReference( that.mReference )
{
	that.mReference = noReference;
}

Element &Element::operator=( Element &&that )
{
	if( &mRawStack != &that.mRawStack )
	{
		throw std::logic_error( "Luna::Element::operator=: tried to move element within different stack" );
		return *this;
	}
	mReference = that.mReference;
	that.mReference = noReference;
	return *this;
}

LuaReference const &Element::getReference() const noexcept
{
	return mReference;
}

}
