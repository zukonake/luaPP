//2016-luaPP zukonake

#ifndef LPP_STRING_HPP
#define LPP_STRING_HPP

#include <nonCopyable.hpp>
//
#include <luaPP/typedef.hpp>
#include <luaPP/element/stackElement.hpp>

namespace LPP
{

class LuaStack;

class String : public StackElement, virtual NonCopyable
{
public:
	String() = delete;
	String( const LuaStack& luaStack, const Index& index = -1 );

	virtual ~String() = default;

	operator const StringValue&() const noexcept;

	const StringValue& get() const noexcept;
private:
	StringValue mValue;
};

}

#endif
