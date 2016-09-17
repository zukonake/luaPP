#ifndef NIL_HPP
#define NIL_HPP

#include <typedef.hpp>
#include <value/stackElement.hpp>

namespace LW
{

class LuaState;

class Nil : public StackElement
{
public:
	Nil() = delete;
	Nil( LuaState& luaState, const Index& index = -1 );

	virtual ~Nil() = default;
};

}

#endif
