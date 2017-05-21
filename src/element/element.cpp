#include <stdexcept>
//
#include <luna/typedef.hpp>
#include <luna/rawStack.hpp>
#include <luna/element/element.hpp>

namespace Luna
{

Element::Element( RawStack &rawStack ) :
	mRawStack( rawStack ),
	mReference( rawStack.newReference( -1, LuaRegistryIndex ))
{
	
}

Element::Element( RawStack &rawStack, LuaReference const &reference ) :
	mRawStack( rawStack ),
	mReference( reference )
{
	
}

Element::Element( Element const &that ) :
	mRawStack( that.mRawStack ),
	mReference( noReference )
{
	that.getValue();
	mReference = mRawStack.newReference( -1, LuaRegistryIndex );
}

Element::Element( Element &&that ) :
	mRawStack( that.mRawStack ),
	mReference( that.mReference )
{
	that.mReference = noReference;
}

Element::~Element()
{
	mRawStack.freeReference( mReference );
}

Element &Element::operator=( Element const &that )
{
	if( &mRawStack != &that.mRawStack )
	{
		throw std::logic_error( "Luna::Element::operator=: tried to copy element within a different stack" );
		return *this;
	}
	that.getValue();
	setValue();
	mRawStack.pop();
	return *this;
}

Element &Element::operator=( Element &&that )
{
	if( &mRawStack != &that.mRawStack )
	{
		throw std::logic_error( "Luna::Element::operator=: tried to move element within a different stack" );
		return *this;
	}
	mReference = that.mReference;
	that.mReference = noReference;
	return *this;
}

void Element::getValue() const
{
	mRawStack.getRawTableField( LuaRegistryIndex, mReference );
}

void Element::setValue() //TODO index maybe?
{
	mRawStack.setRawTableField( LuaRegistryIndex, mReference, -1 );
}

LuaReference const &Element::getReference() const noexcept
{
	return mReference;
}

}
