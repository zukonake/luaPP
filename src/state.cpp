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
	Stack( mLuaState ),
	mLuaState( lua_newstate( Auxiliary::allocate, nullptr ))
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
	Stack( mLuaState ),
	mLuaState( luaState )
{
	
}

State::State( State &&that ) :
	Stack( mLuaState ),
	mLuaState( std::move( that.mLuaState ))
{

}

State::~State()
{
	if( mLuaState != nullptr )
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
