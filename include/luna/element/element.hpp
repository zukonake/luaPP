/* @file luna/element/element.hpp
 * @copyright Copyleft zukonake
 * @license Distributed under GNU General Public License Version 3
 */

#pragma once

#include<luna/typedef.hpp>

namespace Luna
{

class RawStack;

/**
 * Represent an element on the stack.
 */
class Element
{
public:

	/**
	 * Constructs a new Element from the top value on a RawStack.
	 *
	 * Top value will be popped.
	 */
	explicit Element( RawStack &rawStack );

	/**
	 * Constructs a new Element from a reference.
	 *
	 * The reference refers to table on LuaRegistryIndex.
	 *
	 * @param rawStack Source RawStack.
	 * @param reference Source reference.
	 */
	Element( RawStack &rawStack, LuaReference const &reference );

	/**
	 * Moves an Element.
	 *
	 * Target gains source's reference.
	 * Source's reference is set to noReference.
	 */
	Element( Element &&that );



	/**
	 * Deconstructs an Element.
	 *
	 * The reference will get dereferenced,
	 * thus its value pushed onto stack.
	 */
	virtual ~Element();



	/**
	 * Moves an Element.
	 *
	 * Target gains source's reference.
	 * Source's reference is set to noReference.
	 * Target and source should have the same RawStack reference.
	 */
	Element &operator=( Element &&that );



	/**
	 * Pushes a dereferenced copy of the value onto the stack.
	 */
	virtual void getValue();

	/**
	 * Pops a value on the stack and reassigns the referenced value.
	 */
	virtual void setValue();

	/**
	 * Returns the LuaReference.
	 */
	virtual LuaReference const &getReference() const noexcept;
protected:
	RawStack &mRawStack;
	LuaReference mReference;
};

}
