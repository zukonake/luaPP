#include <luna/typedef.hpp>
#include <luna/element/element.hpp>
#include <luna/element/function.hpp>
#include <luna/rawStack.hpp>

namespace Luna
{

Function &Function::operator=( FunctionValue const &value )
{
	Element::mRawStack.pushFunction( value );
	Element::setValue();
	return *this;
}

Function::operator FunctionValue() const noexcept
{
	FunctionValue returnValue = nullptr;
	Element::getValue();
	returnValue = Element::mRawStack.toFunction();
	Element::mRawStack.pop();
	return returnValue;
}

}
