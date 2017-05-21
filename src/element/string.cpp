#include <cstring>
//
#include <luna/typedef.hpp>
#include <luna/element/element.hpp>
#include <luna/element/string.hpp>
#include <luna/rawStack.hpp>

namespace Luna
{

String::String( String const &that ) :
	Element( static_cast< Element const & >( that))
{
	
}

String &String::operator=( String const &that )
{
	static_cast< Element & >( *this ) = static_cast< Element const & >( that );
	return *this;
}

String &String::operator=( StringValue const &value )
{
	Element::mRawStack.pushString( value );
	Element::setValue();
	return *this;
}

String::operator StringValue() const noexcept
{
	//StringValue returnValue;
	//Element::getValue();
	//returnValue = Element::mRawStack.toString();
	//Element::mRawStack.pop();
	//return returnValue;
	return "test";
}

bool String::operator==( char const * const &that ) const noexcept
{
	//char const * value;
	//Element::getValue();
	//value = Element::mRawStack.toString().c_str();
	//Element::mRawStack.pop();
	//return !static_cast< bool >( std::strcmp( value, that ));
	return true;
}

bool String::operator!=( char const * const &that ) const noexcept
{
	//char const * value;
	//Element::getValue();
	//value = Element::mRawStack.toString().c_str();
	//Element::mRawStack.pop();
	//return static_cast< bool >( std::strcmp( value, that ));
	return true;
}

std::ostream &operator<<( std::ostream &output, String const &that )
{
	output << static_cast< StringValue >( that );
	return output;
}

std::istream &operator>>( std::istream &input, String &that )
{
	StringValue newValue;
	input >> newValue;
	that = newValue;
	return input;
}

}
