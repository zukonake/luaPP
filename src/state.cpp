#include <stdexcept>
#include <utility>
#include <memory>
//
#include <lua.hpp>
//
#include <luna/exception.hpp>
#include <luna/typedef.hpp>
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
	if( mL == nullptr )
	{
		throw Exception::StateError( "Luna::State::State: couldn't create LuaState" );
		return;
	}
	lua_atpanic( mL.get(), Auxiliary::panic );
	luaL_openlibs( mL.get());
}

State::State( State &&that ) :
	mL( std::move( that.mL ))
{

}

State &State::operator=( State &&that ) noexcept
{
	mL = std::move( that.mL );
	return *this;
}

State::operator LuaState *() const noexcept
{
	return const_cast< LuaState * >( mL.get());
}

}
