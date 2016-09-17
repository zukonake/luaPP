#ifndef STRING_HPP
#define STRING_HPP

#include <string>
//
#include <typedef.hpp>
#include <value/stackElement.hpp>

namespace LW
{

class LuaState;

class String : public StackElement
{
public:
	String() = delete;
	String( LuaState& luaState, const Index& index = -1 );

	virtual ~String() = default;

	operator const StringValue&() const noexcept;
private:
	StringValue mValue;
};

}

#endif
