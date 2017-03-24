/* luna/rawStack.hpp
 * Copyleft zukonake
 * Distributed under GNU General Public License Version 3
 */

#pragma once

#include <string>
//
#include <luna/typedef.hpp>
#include <luna/state.hpp>

namespace Luna
{

class RawStack
{
public:
	RawStack();
	RawStack( RawStack &&that );

	virtual ~RawStack() = default;

	RawStack &operator=( RawStack &&that );

	/* loads code and pushes it onto stack
	 */
	void loadFile( const std::string &path ) const;
	void loadString( const std::string &value ) const;

	/* loads all the global variables
	 * on to the stack
	 */
	void loadGlobals() const;

	/* loads a global variable on to the stack
	 */
	void loadGlobal( const std::string &name ) const;

	/* returns the value of an element at given
	 * index as a number or string
	 */
	NumberValue toNumber( const Index &index = -1 ) const;
	StringValue toString( const Index &index = -1 ) const;

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
	void pushNumber( const NumberValue &value ) const;
	void pushString( const StringValue &value ) const;

	/* replaces value from one index
	 * with another
	 */
	void replace( const Index &from, const Index &to ) const;

	/* replace value from one index
	 * with another and removes
	 * the original value
	 */
	void move( const Index &from, const Index &to ) const;

	/* swaps position of two elements
	 */
	void swap( const Index &one, const Index &two ) const;

	/* pushes the element from the
	 * given index
	 */
	void copy( const Index &from  = -1 ) const;

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
	 * returns true if the table has not
	 * been fully iterated yet a nil
	 * should be pushed before calling it
	 */
	bool iterate( const Index &index = -2 ) const;

	/* pops given amount of elements
	 */
	void pop( const Size &space = 1 ) const;

	void clear() const noexcept;

	/* returns whether element at
	 * given index exists
	 */
	bool isValid( const Index &index = -1 ) const noexcept;

	/* returns the type of element
	 * at given index, returns INVALID
	 * if the element is invalid or
	 * does not exist
	 */
	Type getType( const Index &index = -1 ) const; 
	Size getSize() const noexcept;
	const State &getState() const noexcept;
	Index getRelativeIndex( const AbsoluteIndex &index ) const;
	AbsoluteIndex getAbsoluteIndex( const Index &index ) const;
private:
	void checkForError( const int &code, const std::string &message = "" ) const;
	void allocate( const Size &size = 1 ) const;
	void validate( const Index &index ) const;
	void validateType( const Index &index, const Type &type ) const;

	State mState;
};

}
