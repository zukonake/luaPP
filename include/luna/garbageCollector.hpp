/**
 * @file luna/garbageCollector.hpp
 * Copyleft zukonake
 * Distributed under GNU General Public License Version 3
 */

#pragma once

#include <luna/typedef.hpp>

namespace Luna
{

/**
 * Represents the Lua C API garbage collector.
 */
class GarbageCollector
{
public:
	GarbageCollector( LuaState const &luaState );

	virtual ~GarbageCollector() = default;

private:
	LuaState const &mLuaState;
}

}
