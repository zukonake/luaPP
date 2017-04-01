#include <luna/typedef.hpp>
#include <luna/element/element.hpp>
#include <luna/element/lightUserData.hpp>
#include <luna/rawStack.hpp>

namespace Luna
{

LightUserData::LightUserData( LightUserData const &that ) :
	Element( static_cast< Element const & >( that))
{
	
}

LightUserData &LightUserData::operator=( LightUserData const &that )
{
	static_cast< Element & >( *this ) = static_cast< Element const & >( that );
	return *this;
}

LightUserData &LightUserData::operator=( LightUserDataValue const &value )
{
	Element::mRawStack.pushLightUserData( value );
	Element::setValue();
	return *this;
}

LightUserData::operator LightUserDataValue() const noexcept
{
	LightUserDataValue returnValue = nullptr;
	Element::getValue();
	returnValue = Element::mRawStack.toLightUserData();
	Element::mRawStack.pop();
	return returnValue;
}

}
