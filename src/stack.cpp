#include <luna/typedef.hpp>
#include <luna/stack.hpp>

namespace Luna
{

Stack::Stack( LuaState const &luaState ) :
	RawStack( luaState )
{

}

}
