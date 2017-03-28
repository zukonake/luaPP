/**
 * @file luna/typedef.hpp
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

/**
 * Used to represent a relative or absolute RawStack index.
 */

typedef int32_t Index;

/**
 * Used to represent an absolute RawStack index.
 */

typedef uint32_t AbsoluteIndex;

/**
 * Used to represent number of values on RawStack.
 */

typedef uint32_t Size;

/**
 * Used to represent a lua_State pointer.
 */

typedef lua_State *LuaState;

/**
 * Used to represent error code returned by Lua C API functions.
 */

typedef int16_t LuaErrorCode;

/**
 * Used to represent Lua types defined by Lua C API.
 */

typedef uint8_t LuaType;

/**
 * Used to represent Lua references to values on RawStack.
 */

typedef Index LuaReference;

/**
 * Used to represent Lua library entry defined by Lua C API.
 *
 * It consists of const char *name which defines the name the function
 * is registered as and lua_CFunction which points to the target function.
 */

typedef luaL_Reg LibraryEntry;

/**
 * Used to represent Lua library defined by Lua C API.
 *
 * It's supposed to be used as a pointer to array of LibraryEntry.
 */

typedef const LibraryEntry *Library;


/**
 * Used to represent Lua boolean value.
 */

typedef bool BooleanValue;

/**
 * Used to represent Lua number value.
 */

typedef double NumberValue;

/**
 * Used to represent Lua string value.
 */

typedef std::string StringValue;

/**
 * Used to represent Lua table value.
 *
 * It's consists of two std::unordered_map first one uses std::size_t keys,
 * while the second one uses std::string keys, just like Lua tables do.
 */

typedef std::pair<
		std::unordered_map< std::size_t, Index >,
		std::unordered_map< std::string, Index > >
		TableValue;

/**
 * Used to represent Lua Function value.
 */

typedef lua_CFunction FunctionValue;

/**
 * Used to represent Lua User Data value.
 */

typedef void *UserDataValue;

/**
 * Used to represent Lua Light User Data value.
 */

typedef void *LightUserdataValue;

/**
 * Used to represent Lua thread value.
 */

typedef LuaState ThreadValue;

/**
 * Used to represent a Lua value type.
 */

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

/**
 * Value of LuaReference which is guaranteed to be empty.
 */

constexpr LuaReference noReference = LUA_NOREF;

/**
 * Value of Index which points to Lua registry table.
 */

constexpr Index LuaRegistryIndex = LUA_REGISTRYINDEX;

}
