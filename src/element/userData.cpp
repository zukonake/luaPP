#include <luna/typedef.hpp>
#include <luna/element/element.hpp>
#include <luna/element/userData.hpp>
#include <luna/rawStack.hpp>

namespace Luna
{

UserData::UserData( UserData const &that ) :
	Element( static_cast< Element const & >( that))
{
	
}

UserData &UserData::operator=( UserData const &that )
{
	static_cast< Element & >( *this ) = static_cast< Element const & >( that );
	return *this;
}

UserData &UserData::operator=( UserDataValue const &value )
{
	Element::mRawStack.pushUserData( value );
	Element::setValue();
	return *this;
}

UserData::operator UserDataValue() const noexcept
{
	UserDataValue returnValue = nullptr;
	Element::getValue();
	returnValue = Element::mRawStack.toUserData();
	Element::mRawStack.pop();
	return returnValue;
}

}
