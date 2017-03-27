/* luna/garbageCollector.hpp
 * Copyleft zukonake
 * Distributed under GNU General Public License Version 3
 */

#pragma once

#include <luna/typedef.hpp>

namespace Luna
{

class GarbageCollector
{
public:
	GarbageCollector( LuaState const &luaState );

	virtual ~GarbageCollector() = default;

private:
	LuaState const &mLuaState;
}

}
