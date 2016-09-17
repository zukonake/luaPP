//2016-luaPP zukonake

#ifndef LPP_NUMBER_HPP
#define LPP_NUMBER_HPP

#include <nonCopyable.hpp>
//
#include <luaPP/typedef.hpp>
#include <luaPP/element/stackElement.hpp>

namespace LPP
{

class LuaStack;

class Number : public StackElement, virtual NonCopyable
{
public:
	typedef double NumberValue;

	Number() = delete;
	Number( const LuaStack& luaStack, const Index& index = -1 );

	virtual ~Number() = default;

	operator const NumberValue&() const noexcept;

	const NumberValue& get() const noexcept;
private:
	NumberValue mValue;
};

}

#endif
