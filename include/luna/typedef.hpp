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
	NIL = LUA_TNIL,
	BOOLEAN = LUA_TBOOLEAN,
	NUMBER = LUA_TNUMBER,
	STRING = LUA_TSTRING,
	TABLE = LUA_TTABLE,
	LIGHT_USER_DATA = LUA_TLIGHTUSERDATA,
	USER_DATA = LUA_TUSERDATA,
	FUNCTION = LUA_TFUNCTION,
	THREAD = LUA_TTHREAD,
	INVALID = LUA_TNONE
};

/**
 * Used to represent Lua C API return codes.
 */
enum ReturnCode
{
	OK = LUA_OK,
	YIELD = LUA_YIELD,
	RUNTIME_ERROR = LUA_ERRUN,
	SYNTAX_ERROR = LUA_ERRSYNTAX,
	MEMORY_ERROR = LUA_ERRMEM,
	GARBAGE_COLLECTOR_ERROR = LUA_ERRGCMM,
	UNKNOWN_ERROR = LUA_ERRERR
}

/**
 * Reference which is guaranteed to be empty.
 */
constexpr LuaReference noReference = LUA_NOREF;

/**
 * Points to Lua registry table.
 */
constexpr Index LuaRegistryIndex = LUA_REGISTRYINDEX;

/** 
 * Used when all returned value of Lua Function are to be pushed on the stack.
 *
 * @see RawStack::call 
 */
constexpr Size LuaMultiReturn = LUA_MULTRET;
}
