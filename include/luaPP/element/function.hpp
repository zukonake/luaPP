//2016-luaPP zukonake

#ifndef LPP_FUNCTION_HPP
#define LPP_FUNCTION_HPP

#include <nonCopyable.hpp>
//
#include <luaPP/typedef.hpp>
#include <luaPP/element/stackElement.hpp>

namespace LPP
{

class LuaStack;
class Table;

class Function : public StackElement, virtual NonCopyable
{
public:
	Function() = delete;
	Function( const LuaStack& luaStack, const Index& index = -1 );

	virtual ~Function() = default;
};

}

#endif
