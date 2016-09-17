#ifndef LUASTACK_HPP
#define LUASTACK_HPP

#include <luaPP/typedef.hpp>
#include <luaPP/element/stackElement.hpp>
#include <luaPP/element/nil.hpp>
#include <luaPP/element/number.hpp>
#include <luaPP/element/string.hpp>
#include <luaPP/element/table.hpp>
#include <luaPP/element/function.hpp>

namespace LW
{

class StackElement;
class Function;

class LuaStack												///naming: right=to the top of the stack, left= to the bottom of the stack
{
public:
	LuaStack();												///libs get loaded

	virtual ~LuaStack();									///stack gets cleared

	Function* loadFile( const std::string& path );

	LuaType getType( const Index& index = -1);				///non-number,string,table,function is recognized as nil
	std::string getTypeName( const LuaType& type );			///

	NumberValue getNumber( const Index& index = -1 );		///get raw number from stack
	StringValue getString( const Index& index = -1 );		///get raw string from stack

	template< typename T = StackElement >
	T* at( const std::string& name );						///get T StackElement from mStack
	template< typename T = StackElement >
	T* get( const Index& index = -1 );						///return new T StackElement

	void loadGlobals(); 									///loads luaPP table

	Index getIndex(); 										///returns stack length

	void pushNil();

	void insert( const Index& index ); 						///insert element into index and shift elements to right
	void push( const Index& index ); 						///copies element to top of the stack
	void copy( const Index& from, const Index& to ); 		///copy element into index, replacing previous value
	void remove( const Index& index ); 						///remove element and shift elements to left
	void pop( const Index& amount = 1 );					///pop amount elements from the top of the stack
	bool iterate( const Index& index = -2 );				///iterate a table, a key is needed right to the table to keep track of the position
	Index call(); 											///call the element on the top of the stack

	constexpr static float luaVersion = 5.2;
	constexpr static float luaPPVersion = 0.2;
private:
	void clear();

	Table* mStack = nullptr;
	lua_State* mL;
};

template< typename T >
T* LuaStack::at( const std::string& name )
{
	return dynamic_cast< T* >(( *mStack )[ name ]);
}

template< typename T >
T* LuaStack::get( const Index& index )
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

}

#endif
