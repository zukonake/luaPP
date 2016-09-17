//2016-luaPP zukonake

#ifndef LPP_NIL_HPP
#define LPP_NIL_HPP

#include <nonCopyable.hpp>
//
#include <luaPP/typedef.hpp>
#include <luaPP/element/stackElement.hpp>

namespace LPP
{

class LuaStack;

class Nil : public StackElement, virtual NonCopyable
{
public:
	Nil() = delete;
	Nil( const LuaStack& luaStack, const Index& index = -1 );

	virtual ~Nil() = default;
};

}

#endif
