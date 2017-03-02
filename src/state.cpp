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

State::operator lua_State *() noexcept
{
	return mL.get();
}

State::operator const lua_State *() const noexcept
{
	return mL.get();
}

}
