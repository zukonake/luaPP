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

typedef int32_t Index;
typedef uint32_t AbsoluteIndex;
typedef uint32_t Size;
typedef lua_State *LuaState;
typedef int16_t LuaErrorCode;
typedef uint8_t LuaType;
typedef Index LuaReference;
typedef luaL_Reg LibraryEntry;
typedef const luaL_Reg *Library;

typedef bool BooleanValue;
typedef double NumberValue;
typedef std::string StringValue;
typedef std::pair<
		std::unordered_map< std::size_t, Index >,
		std::unordered_map< std::string, Index > >
		TableValue;
typedef lua_CFunction FunctionValue;
typedef void *UserDataValue;
typedef void *LightUserdataValue;
typedef LuaState ThreadValue;

enum Type
{
	NIL,
	BOOLEAN,
	NUMBER,
	STRING,
	TABLE,
	LIGHT_USER_DATA,
	USER_DATA,
	FUNCTION,
	THREAD,
	INVALID
};

constexpr LuaReference noReference = LUA_NOREF;
constexpr Index LuaRegistryIndex = LUA_REGISTRYINDEX;

}
