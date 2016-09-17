#ifndef LUASTATE_HPP
#define LUASTATE_HPP

#include <typedef.hpp>

namespace LW
{

class StackElement;

class LuaState
{
public:
	LuaState();

	virtual ~LuaState();

	operator lua_State*();

	void loadFile( const std::string& path );

	LuaType getType( const Index& index );
	std::string getTypeName( const LuaType& type );
	StackElement* evaluateType( const Index& index );

	NumberValue getNumber( const Index& index );
	StringValue getString( const Index& index );

	void getVariable( const std::string& name );

	Index getIndex();

	void pushNil();

	void insert( const Index& index );
	void push( const Index& index );
	void copy( const Index& from, const Index& to );
	void remove( const Index& index );
	void pop( const Index& amount );
	bool iterate( const Index& index );
	Index call();

	constexpr static float luaVersion = 5.2;
	constexpr static float luaPPVersion = 0.1;
private:
	lua_State* mL;
};

}

#endif
