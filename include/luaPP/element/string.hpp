#ifndef STRING_HPP
#define STRING_HPP

#include <string>
//
#include <luaPP/typedef.hpp>
#include <luaPP/element/stackElement.hpp>

namespace LW
{

class LuaStack;

class String : public StackElement
{
public:
	String() = delete;
	String( LuaStack& luaStack, const Index& index = -1 );

	virtual ~String() = default;

	operator const StringValue&() const noexcept;
private:
	StringValue mValue;
};

}

#endif
