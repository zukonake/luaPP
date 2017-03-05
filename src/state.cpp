#include <utility>
//
#include <lua.hpp>
//
#include <luna/auxiliary.hpp>
#include <luna/state.hpp>

namespace Luna
{

void LuaStateDeleter::operator()( LuaState *ptr ) const
{
	if( ptr != nullptr )
	{
		lua_close( ptr );
	}
}

State::State() :
	mL( lua_newstate( Auxiliary::allocate, nullptr ))
{
	lua_atpanic( mL.get(), Auxiliary::panic );
	luaL_openlibs( mL.get());
}

State::State( State &&that )
{
	mL = std::move( that.mL );
}

State &State::operator=( State &&that ) noexcept
{
	mL = std::move( that.mL );
	return *this;
}

State::operator LuaState *() noexcept
{
	return mL.get();
}

State::operator LuaState *() const noexcept
{
	return const_cast< LuaState *>( mL.get());
}

State::operator const LuaState *() const noexcept
{
	return mL.get();
}

}
