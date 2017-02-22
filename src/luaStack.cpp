//2016-luaPP zukonake

#include <luaPP/luaStack.hpp>
//
#include <lua.hpp>
//
#include <luaPP/element/stackElement.hpp>
#include <luaPP/element/nil.hpp>
#include <luaPP/element/number.hpp>
#include <luaPP/element/string.hpp>
#include <luaPP/element/table.hpp>
#include <luaPP/element/function.hpp>

using namespace LPP;

LuaStack::LuaStack()
{
	mL = luaL_newstate();
	if( mL == NULL )
	{
		throw std::runtime_error( "LuaStack::LuaStack: couldn't create lua_State" );
		return;
	}
	luaL_openlibs( mL );
}

LuaStack::~LuaStack()
{
	clear();
	lua_close( mL );
}

const Function* LuaStack::loadFile( const std::string& path ) const
{
	if( !isFree() )
	{
		throw std::runtime_error( "LuaStack::loadFile: not enough space on stack" );
		return nullptr;
	}
	if( luaL_loadfile( mL, path.c_str()) != LUA_OK )
	{
		throw std::runtime_error( "LuaStack::loadFile: " + getString( -1 ));
	}
	return new Function( *this, -1 );
}

const Function* LuaStack::loadString( const std::string& value ) const
{
	if( !isFree() )
	{
		throw std::runtime_error( "LuaStack::loadString: not enough space on stack" );
		return nullptr;
	}
	if( luaL_loadstring( mL, value.c_str()) != LUA_OK )
	{
		throw std::runtime_error( "LuaStack::loadString: " + getString( -1 ));
	}
	return new Function( *this, -1 );
}

LuaType LuaStack::getType( const Index& index ) const noexcept
{
	switch( lua_type( mL, index ) )
	{
		case LUA_TNUMBER:
		return LuaType::NUMBER;
		break;

		case LUA_TSTRING:
		return LuaType::STRING;
		break;

		case LUA_TTABLE:
		return LuaType::TABLE;
		break;

		case LUA_TFUNCTION:
		return LuaType::FUNCTION;
		break;

		default:
		return LuaType::NIL;
		break;
	}
}

std::string LuaStack::getTypeName( const LuaType& type ) const noexcept
{
	switch( type )
	{
		case LuaType::NUMBER:
		return "number";
		break;

		case LuaType::STRING:
		return "string";
		break;

		case LuaType::TABLE:
		return "table";
		break;

		case LuaType::FUNCTION:
		return "function";
		break;

		default:
		return "nil";
		break;
	}
}

NumberValue LuaStack::getNumber( const Index& index ) const
{
	if( getType( index ) != LuaType::NUMBER )
	{
		throw std::runtime_error( "LuaStack::getNumber: tried to convert a non-number lua type to number" );
		return 0;
	}
	return ( NumberValue )lua_tonumber( mL, index );
}

StringValue LuaStack::getString( const Index& index ) const
{
	if( getType( index ) != LuaType::STRING )
	{
		throw std::runtime_error( "LuaStack::getString: tried to convert a non-string lua type to string" );
		return "";
	}
	return ( StringValue )lua_tostring( mL, index );
}

const StackElement* LuaStack::get( const Index& index ) const
{
	switch( getType( index ) )
	{
		case LuaType::NUMBER:
		return new Number( *this, index );
		break;

		case LuaType::STRING:
		return new String( *this, index );
		break;

		case LuaType::TABLE:
		return new Table( *this, index );
		break;

		case LuaType::FUNCTION:
		return new Function( *this, index );
		break;

		default:
		return new Nil( *this, index );
		break;
	}
}

void LuaStack::loadGlobals()
{
	if( !isFree() )
	{
		throw std::runtime_error( "LuaStack::loadGlobals: not enough space on stack" );
		return;
	}
	clear();
	lua_getglobal( mL, "luaPP" );
	mStack = new Table( *this, -1 );
}

void LuaStack::loadGlobal( const std::string& name ) const
{
	if( !isFree() )
	{
		throw std::runtime_error( "LuaStack::loadGlobal: not enough space on stack" );
		return;
	}
	lua_getglobal( mL, name.c_str());
}

const Table* LuaStack::getGlobals() const noexcept
{
	return mStack;
}

Index LuaStack::getIndex() const noexcept
{
	return ( Index )lua_gettop( mL );
}

bool LuaStack::isValid( const Index& index ) const noexcept
{
	return !lua_isnone( mL, index );
}

Index LuaStack::isFree( const Index& space ) const noexcept
{
	return ( Index )lua_checkstack( mL, space );
}

void LuaStack::pushNil() const noexcept
{
	lua_pushnil( mL );
}

void LuaStack::pushNumber( const NumberValue& value ) const
{
	if( !isFree() )
	{
		throw std::runtime_error( "LuaStack::pushNumber: not enough space on stack" );
		return;
	}
	lua_pushnumber( mL, value );
}

void LuaStack::pushString( const StringValue& value ) const
{
	if( !isFree() )
	{
		throw std::runtime_error( "LuaStack::pushString: not enough space on stack" );
		return;
	}
	lua_pushstring( mL, value.c_str() );
}

void LuaStack::insert( const Index& index ) const
{
	if( index > 0 )
	{
		if( !isValid( index ))
		{
			throw std::logic_error( "LuaStack::insert: invalid element given" );
			return;
		}
		lua_insert( mL, index );
	}
	else if( index < 0 )
	{
		if( !isValid( getIndex() + ( index + 1 )))
		{
			throw std::logic_error( "LuaStack::insert: invalid element given" );
			return;
		}
		lua_insert( mL, getIndex() + ( index + 1 ));
	}
	else
	{
		throw std::logic_error( "LuaStack::insert: index 0 given" );
	}
}

void LuaStack::push( const Index& index ) const
{
	if( !isValid( index ))
	{
		throw std::logic_error( "LuaStack::push: invalid element given" );
		return;
	}
	if( !isFree() )
	{
		throw std::runtime_error( "LuaStack::push: not enough space on stack" );
		return;
	}
	lua_pushvalue( mL, index );
}

void LuaStack::copy( const Index& from, const Index& to ) const
{
	if( !isValid( from ) or !isValid( to ))
	{
		throw std::logic_error( "LuaStack::copy: invalid element given" );
		return;
	}
	lua_copy( mL, from, to );
}

void LuaStack::replace( const Index& to ) const
{
	if( !isValid( -1 ) or !isValid( to ))
	{
		throw std::logic_error( "LuaStack::replace: invalid element given" );
		return;
	}
	lua_replace( mL, to );
}

void LuaStack::remove( const Index& index ) const
{
	if( !isValid( index ))
	{
		throw std::logic_error( "LuaStack::remove: invalid element given" );
		return;
	}
	lua_remove( mL, index );
}

void LuaStack::pop( const Index& amount ) const
{
	if( amount < 0 or amount > getIndex())
	{
		throw std::logic_error( "LuaStack::pop: invalid amount given" );
		return;
	}
	lua_pop( mL, amount );
}

bool LuaStack::iterate( const Index& index ) const
{
	if( !isValid( index ) or !isValid( index + 1 ) )
	{
		throw std::logic_error( "LuaStack::remove: invalid element given" );
		return false;
	}
	if( !isFree() )
	{
		throw std::runtime_error( "LuaStack::iterate: not enough space on stack" );
		return false;
	}
	return ( bool )lua_next( mL, index );
}

Index LuaStack::call() const
{
	Index before = getIndex();
	if( lua_pcall( mL, 0, LUA_MULTRET, 0 ) != LUA_OK )
	{
		throw std::runtime_error( "LuaStack::call: " + getString( -1 ));
	}
	Index after = getIndex();
	return after - before;
}

void LuaStack::clear() noexcept
{
	if( mStack != nullptr )
	{
		delete mStack;
		mStack = nullptr;
	}
}
