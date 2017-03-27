/* luna/state.hpp
 * Copyleft zukonake
 * Distributed under GNU General Public License Version 3
 */

#pragma once

#include <luna/typedef.hpp>
#include <luna/stack.hpp>

namespace Luna
{

class State : public Stack
{
public:
	State();
	State( LuaState const &luaState );
	State( State &&that );

	virtual ~State();

	State &operator=( State &&that ) noexcept;

	operator LuaState () const noexcept;

	NumberValue getLuaVersion();
private:
	LuaState mLuaState;
};


}
