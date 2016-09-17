#ifndef FUNCTION_HPP
#define FUNCTION_HPP

#include <luaPP/typedef.hpp>
#include <luaPP/element/stackElement.hpp>

namespace LW
{

class LuaStack;
class Table;

class Function : public StackElement
{
public:
	Function() = delete;
	Function( LuaStack& luaStack, const Index& index = -1 );

	virtual ~Function() = default;

	Index call();       ///Only works when function is on top of the stack
	void loadGlobals(); ///
};

}

#endif
