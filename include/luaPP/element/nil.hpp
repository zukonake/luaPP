#ifndef NIL_HPP
#define NIL_HPP

#include <luaPP/typedef.hpp>
#include <luaPP/element/stackElement.hpp>

namespace LW
{

class LuaStack;

class Nil : public StackElement
{
public:
	Nil() = delete;
	Nil( LuaStack& luaStack, const Index& index = -1 );

	virtual ~Nil() = default;
};

}

#endif
