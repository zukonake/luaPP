/* luna/typedef.hpp
 * Copyleft zukonake
 * Distributed under GNU General Public License Version 3
 */

#pragma once

#include <cstdint>
#include <string>
//
#include <lua.hpp>

namespace Luna
{

class Element;

typedef int16_t Index;
typedef uint16_t AbsoluteIndex;
typedef uint16_t Size;
typedef lua_State LuaState;

typedef float NumberValue;
typedef std::string StringValue;

enum Type
{
	NIL,
	NUMBER,
	STRING,
	TABLE,
	FUNCTION,
	USERDATA,
	LIGHT_USERDATA,
	THREAD,
	INVALID
};

}
