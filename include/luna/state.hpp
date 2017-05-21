/**
 * @file luna/state.hpp
 * @copyright Copyleft zukonake
 * @license Distributed under GNU General Public License Version 3
 */

#pragma once

#include <luna/typedef.hpp>
#include <luna/stack.hpp>

namespace Luna
{

/** 
 * Main class wrapping the LuaState and Stack.
 */
class State : public Stack
{
public:

	/**
	 * Constructs a new State, with a new LuaState.
	 *
	 * A new LuaState is created, its allocate and panic functions set and
	 * its libs loaded.
	 */
	State();

	/**
	 * Constructs a new State, from an existing LuaState.
	 *
	 * The LuaState is unchanged.
	 */
	State( LuaState const &luaState );

	/**
	 * Moves the LuaState to new State.
	 *
	 * @param that Its LuaState will be set to nullptr.
	 */
	State( State &&that );

	/**
	 * Closes the LuaState.
	 */
	virtual ~State();

	/**
	 * Moves the LuaState to an existing State.
	 *
	 * @param that Its LuaState will be set to nullptr.
	 */
	State &operator=( State &&that ) noexcept;

	/**
	 * Returns an underlying LuaState.
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
