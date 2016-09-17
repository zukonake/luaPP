#ifndef NUMBER_HPP
#define NUMBER_HPP

#include <typedef.hpp>
#include <element/stackElement.hpp>

namespace LW
{

class LuaState;

class Number : public StackElement
{
public:
	typedef double NumberValue;

	Number() = delete;
	Number( LuaState& luaState, const Index& index = -1 );

	virtual ~Number() = default;

	operator const NumberValue&() const noexcept;
private:
	NumberValue mValue;
};

}

#endif
