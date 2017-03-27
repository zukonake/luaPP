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

State::State() :
	mLuaState( lua_newstate( Auxiliary::allocate, nullptr )),
	Stack( mLuaState )
{
	if( mLuaState == nullptr )
	{
		throw Exception::StateError( "Luna::State::State: couldn't create LuaState" );
		return;
	}
	lua_atpanic( mLuaState, Auxiliary::panic );
	luaL_openlibs( mLuaState );
}

State::State( LuaState const &luaState ) :
	mLuaState( luaState )
{
	
}

State::State( State &&that ) :
	mLuaState( std::move( that.mLuaState ))
{

}

State::~State()
{
	if( mL != nullptr )
	{
		lua_close( mLuaState );
	}
}

State &State::operator=( State &&that ) noexcept
{
	mLuaState = std::move( that.mLuaState );
	return *this;
}

State::operator LuaState () const noexcept
{
	return mLuaState;
}

}
