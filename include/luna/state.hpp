/* luna/state.hpp
 * Copyleft zukonake
 * Distributed under GNU General Public License Version 3
 */

#pragma once

#include <memory>
//
#include <lua.hpp>
//
#include <luna/typedef.hpp>

namespace Luna
{

struct LuaStateDeleter
{
	void operator()( LuaState *ptr ) const;
};

class State
{
public:
	State();
	State( State &&that );

	virtual ~State() = default;

	State &operator=( State &&that ) noexcept;

	operator LuaState *() noexcept;
	operator const LuaState *() const noexcept;
private:
	std::unique_ptr< LuaState, LuaStateDeleter > mL;
};


}
