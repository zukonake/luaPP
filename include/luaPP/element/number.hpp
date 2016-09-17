#ifndef NUMBER_HPP
#define NUMBER_HPP

#include <luaPP/typedef.hpp>
#include <luaPP/element/stackElement.hpp>

namespace LW
{

class LuaStack;

class Number : public StackElement
{
public:
	typedef double NumberValue;

	Number() = delete;
	Number( LuaStack& luaStack, const Index& index = -1 );

	virtual ~Number() = default;

	operator const NumberValue&() const noexcept;
private:
	NumberValue mValue;
};

}

#endif
