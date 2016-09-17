//2016-luaPP zukonake

#ifndef STRING_HPP
#define STRING_HPP

#include <luaPP/nonCopyable.hpp>
#include <luaPP/typedef.hpp>
#include <luaPP/element/stackElement.hpp>

namespace LW
{

class LuaStack;

class String : public StackElement, virtual NonCopyable
{
public:
	String() = delete;
	String( const LuaStack& luaStack, const Index& index = -1 );

	virtual ~String() = default;

	operator const StringValue&() const noexcept;
private:
	StringValue mValue;
};

}

#endif
