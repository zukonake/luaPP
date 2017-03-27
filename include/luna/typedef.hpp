/* luna/typedef.hpp
 * Copyleft zukonake
 * Distributed under GNU General Public License Version 3
 */

#pragma once

#include <cstdint>
#include <cstddef>
#include <utility>
#include <string>
#include <unordered_map>
//
#include <lua.hpp>

namespace Luna
{

class Element;

typedef int32_t Index;
typedef uint32_t AbsoluteIndex;
typedef uint32_t Size;
typedef lua_State LuaState;

typedef double NumberValue;
typedef std::string StringValue;
typedef std::pair<
		std::unordered_map< std::size_t, Index >,
		std::unordered_map< std::string, Index > >
		TableValue;

enum Type
{
	NIL,
	BOOLEAN,
	LIGHT_USERDATA,
	NUMBER,
	STRING,
	TABLE,
	FUNCTION,
	USERDATA,
	THREAD,
	INVALID
};

}
