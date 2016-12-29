//2016-luaPP zukonake

#ifndef LPP_LUASTACK_HPP
#define LPP_LUASTACK_HPP

#include <string>
//
#include <nonCopyable.hpp>
//
#include <luaPP/typedef.hpp>
#include <luaPP/element/table.hpp>

class lua_State;

namespace LPP
{

class StackElement;
class Function;

class LuaStack : virtual NonCopyable								///naming: right=to the top of the stack, left= to the bottom of the stack
{
public:
	LuaStack();														///libs get loaded

	virtual ~LuaStack();											///stack gets cleared

	const Function* loadFile( const std::string& path ) const;		///load a file as a lua function
	const Function* loadString( const std::string& value ) const;	///load a string as a lua function

	LuaType getType( const Index& index = -1) const noexcept;		///non-number,string,table,function is recognized as nil
	std::string getTypeName( const LuaType& type ) const noexcept;	///

	NumberValue getNumber( const Index& index = -1 ) const;			///get raw number from stack
	StringValue getString( const Index& index = -1 ) const;			///get raw string from stack

	template< typename T = StackElement >
	const T* at( const std::string& name ) const;					///get T StackElement from mStack
	template< typename T >
	const T* get( const Index& index = -1 ) const;					//return new T StackElement
	const StackElement* get( const Index& index = -1 ) const;		///return new StackElement

	void loadGlobals();												///loads luaPP table from top of the stack
	void loadGlobal( const std::string& name ) const;				///load single global from top of the stack
	const Table* getGlobals() const noexcept;						///returns mStack

	Index getIndex() const noexcept; 								///returns stack length

	bool isValid( const Index& index = -1 ) const noexcept;			///checks whether element is valid
	Index isFree( const Index& space = 1 ) const noexcept;

	void pushNil() const noexcept;
	void pushNumber( const NumberValue& value ) const;
	void pushString( const StringValue& value ) const;

	void insert( const Index& index ) const; 						///insert element into index and shift elements to right
	void push( const Index& index ) const; 							///copies element to top of the stack
	void copy( const Index& from, const Index& to ) const; 			///copy element into index, replacing previous value
	void replace( const Index& to ) const;							///moves element from top of the stack into index, replacing previous value
	void remove( const Index& index ) const; 						///remove element and shift elements to left
	void pop( const Index& amount = 1 ) const;						///pop amount elements from the top of the stack
	bool iterate( const Index& index = -2 ) const;					///iterate a table, a key is needed right to the table to keep track of the position
	Index call() const; 											///call the element on the top of the stack

	constexpr static float luaVersion = 5.2;
	constexpr static float luaPPVersion = 0.88;
private:
	void clear() noexcept;

	const Table* mStack = nullptr;
	lua_State* mL;
};

template< typename T >
const T* LuaStack::at( const std::string& name ) const
{
	return mStack->at< T >( name );
}

template< typename T >
const T* LuaStack::get( const Index& index ) const
{
	return dynamic_cast< const T* >( get( index ));
}

}

#endif
