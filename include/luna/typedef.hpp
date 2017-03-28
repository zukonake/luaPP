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

/**
 * Type used to represent a relative or absolute Luna::RawStack index.
 */

typedef int32_t Index;

/**
 * Type used to represent an absolute Luna::RawStack index.
 */

typedef uint32_t AbsoluteIndex;

/**
 * Type used to represent number of values on Luna::RawStack.
 */

typedef uint32_t Size;

/**
 * Type used to represent a lua_State pointer.
 */

typedef lua_State *LuaState;

/**
 * Type used to represent error code returned by Lua C API functions.
 */

typedef int16_t LuaErrorCode;

/**
 * Type used to represent Lua types defined by Lua C API.
 */

typedef uint8_t LuaType;

/**
 * Type used to represent Lua references to values on Luna::RawStack.
 */

typedef Index LuaReference;

/**
 * Type used to represent Lua library entry defined by Lua C API.
 *
 * It consists of const char *name which defines the name the function
 * is registered as and lua_CFunction which points to the target function.
 */

typedef luaL_Reg LibraryEntry;

/**
 * Type used to represent Lua library defined by Lua C API.
 *
 * It's supposed to be used as a pointer to array of Luna::LibraryEntry.
 */

typedef const LibraryEntry *Library;


/**
 * Type used to represent Lua boolean value.
 */

typedef bool BooleanValue;

/**
 * Type used to represent Lua number value.
 */

typedef double NumberValue;

/**
 * Type used to represent Lua string value.
 */

typedef std::string StringValue;

/**
 * Type used to represent Lua table value.
 *
 * It's consists of two std::unordered_map first one uses std::size_t keys,
 * while the second one uses std::string keys, just like Lua tables do.
 */

typedef std::pair<
		std::unordered_map< std::size_t, Index >,
		std::unordered_map< std::string, Index > >
		TableValue;

/**
 * Type used to represent Lua Function value.
 */

typedef lua_CFunction FunctionValue;

/**
 * Type used to represent Lua User Data value.
 */

typedef void *UserDataValue;

/**
 * Type used to represent Lua Light User Data value.
 */

typedef void *LightUserdataValue;

/**
 * Type used to represent Lua thread value.
 */

typedef LuaState ThreadValue;

/**
 * Enum used to represent a Lua value type.
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
 * Value of Luna::LuaReference which is guaranteed to be empty.
 */

constexpr LuaReference noReference = LUA_NOREF;

/**
 * Value of Luna::Index which points to Lua registry table.
 */

constexpr Index LuaRegistryIndex = LUA_REGISTRYINDEX;

}
