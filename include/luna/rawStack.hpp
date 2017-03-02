/* luna/rawStack.hpp
 * Copyleft zukonake
 * Distributed under GNU General Public License Version 3
 */

#pragma once

#include <string>
//
#include <luna/typedef.hpp>
#include <luna/state.hpp>
#include <luna/element/number.hpp>
#include <luna/element/string.hpp>

namespace Luna
{

class RawStack
{
public:
	RawStack();
	RawStack( RawStack &&that );

	virtual ~RawStack();

	RawStack &operator=( RawStack &&that );

	/* loads code and pushes it onto stack
	 */
	void loadFile( const std::string &path ) const;
	void loadString( const std::string &value ) const;

	/* loads a global variable on to the stack
	 */
	void loadGlobal( const std::string &name ) const;

	/* loads all the global variables
	 * on to the stack
	 */
	void loadGlobals() const;

	/* returns the value of an element at given
	 * index as a number or string
	 */
	Number::Value toNumber( const Index &index = -1 ) const;
	String::Value toString( const Index &index = -1 ) const;

	/* loads code, pushes it onto stack
	 * and calls call()
	 */
	Size doFile( const std::string &path ) const;
	Size doString( const std::string &value ) const;

	/* call function at given index
	 * and returns number of returned
	 * elements
	 */
	Size call( const Index &index = -1 ) const;

	void pushNil() const;
	void pushNumber( const Number::Value &value ) const;
	void pushString( const String::Value &value ) const;

	/* copies value from one index
	 * to another
	 */
	void copy( const Index &from, const Index &to ) const;

	/* moves value from one index
	 * to another
	 */
	void move( const Index &from, const Index &to ) const;

	/* swaps position of two elements
	 */
	void swap( const Index &one, const Index &two ) const;

	/* moves top element to given index
	 * shifting up elements above
	 */
	void insert( const Index &index = -1 ) const;

	/* removes element at given index
	 * shifting down elements above
	 */
	void remove( const Index &index = -1 ) const;

	/* removes element at given index
	 * and replaces it with nil
	 */
	void erase( const Index &index = -1 ) const;

	/* pops key and pushes key-value
	 * pair from a table at given index
	 */
	void iterate( const Index &index = -1 ) const;

	/* pops given amount of elements
	 */
	void pop( const Size &space = -1 ) const;

	/* clears the stack and resizes it
	 * to given size
	 */
	void clear( const Size &newSize = 0 ) const noexcept;

	/* returns whether element at
	 * given index exists
	 */
	bool isValid( const Index &index = -1 ) const noexcept;

	Type getType( const Index &index = -1 ) const; 
	Size getSize() const noexcept;
	const State &getState() const noexcept;
	Index getRelativeIndex( const AbsoluteIndex &index ) const;
	AbsoluteIndex getAbsoluteIndex( const Index &index ) const;
private:
	void allocate( const Size &space = 1 ) const;
	void guaranteeValidity( const Index &index = -1 ) const;

	State mState;
};

}
