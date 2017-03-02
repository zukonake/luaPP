/* luna/typedef.hpp
 * Copyleft zukonake
 * Distributed under GNU General Public License Version 3
 */

#pragma once

#include <cstdint>
//
#include <lua.hpp>

namespace Luna
{

typedef int16_t Index;
typedef uint16_t AbsoluteIndex;
typedef uint16_t Size;
typedef lua_State LuaState;

enum Type
{
	NIL,
	NUMBER,
	STRING,
	TABLE,
	FUNCTION,
	USERDATA,
	LIGHTUSERDATA,
	THREAD,
	INVALID
};

}
