#include <luna/typedef.hpp>
#include <luna/element/element.hpp>
#include <luna/element/thread.hpp>
#include <luna/rawStack.hpp>

namespace Luna
{

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
