#include <luna/typedef.hpp>
#include <luna/element/element.hpp>
#include <luna/element/thread.hpp>
#include <luna/rawStack.hpp>

namespace Luna
{

Thread::Thread( Thread const &that ) :
	Element( static_cast< Element const & >( that))
{
	
}

Thread &Thread::operator=( Thread const &that )
{
	static_cast< Element & >( *this ) = static_cast< Element const & >( that );
	return *this;
}

Thread &Thread::operator=( ThreadValue const &value )
{
	Element::mRawStack.pushThread( value );
	Element::setValue();
	return *this;
}

Thread::operator ThreadValue() const noexcept
{
	ThreadValue returnValue = nullptr;
	Element::getValue();
	returnValue = Element::mRawStack.toThread();
	Element::mRawStack.pop();
	return returnValue;
}

}
