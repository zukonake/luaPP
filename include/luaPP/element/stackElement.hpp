//2016-luaPP zukonake

#ifndef STACKELEMENT_HPP
#define STACKELEMENT_HPP

#include <luaPP/nonCopyable.hpp>
#include <luaPP/typedef.hpp>

namespace LPP
{

class LuaStack;

class StackElement : virtual NonCopyable
{
protected:
	StackElement() = delete;
	StackElement( const LuaStack& luaStack, const Index& index = -1 );
public:
	virtual ~StackElement();

	const Index& getIndex() const noexcept;
protected:
	const LuaStack& mLuaStack;
	Index mIndex;
};

}

#endif
