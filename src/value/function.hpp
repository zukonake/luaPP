#ifndef FUNCTION_HPP
#define FUNCTION_HPP

#include <typedef.hpp>
#include <value/stackElement.hpp>

namespace LW
{

class LuaState;

class Function : public StackElement
{
public:
	Function() = delete;
	Function( LuaState& luaState, const Index& index = -1 );

	virtual ~Function() = default;

	Index call();
};

}

#endif
