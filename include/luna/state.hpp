/* luna/state.hpp
 * Copyleft zukonake
 * Distributed under GNU General Public License Version 3
 */

#pragma once

#include <luna/typedef.hpp>
#include <luna/stack.hpp>

namespace Luna
{

/** 
 * Main class wrapping the Luna::LuaState and Luna::Stack.
 */

class State : public Stack
{
public:

	/**
	 * Constructs a new State.
	 *
	 * A new LuaState is created, its allocate and panic functions set and
	 * its libs loaded.
	 */
	
	State();

	/**
	 * Constructs a new State, from an existing Luna::LuaState.
	 *
	 * The LuaState is unchanged.
	 */

	State( LuaState const &luaState );

	/**
	 * Moves the Luna::LuaState to new Luna::State.
	 *
	 * @param that Its Luna::LuaState will be set to nullptr.
	 */

	State( State &&that );

	/**
	 * Closes the Luna::LuaState.
	 */

	virtual ~State();

	/**
	 * Moves the Luna::LuaState to an existing Luna::State.
	 *
	 * @param that Its Luna::LuaState will be set to nullptr.
	 */

	State &operator=( State &&that ) noexcept;

	/**
	 * Returns an underlying Luna::LuaState.
	 */

	operator LuaState () const noexcept;

	/**
	 * Returns its Lua Version;
	 */

	NumberValue getLuaVersion();
private:
	LuaState mLuaState;
};


}
