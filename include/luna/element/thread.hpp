/* @file luna/element/thread.hpp
 * @copyright Copyleft zukonake
 * @license Distributed under GNU General Public License Version 3
 */

#pragma once

#include<luna/typedef.hpp>
#include<luna/element/element.hpp>

namespace Luna
{

/**
 * Represents a thread value on the stack.
 */	
class Thread : public Element
{
public:
	Thread( Thread const &that );
	using Element::Element;

	~Thread() = default;

	Thread &operator=( Thread const &that );

	/**
	 * Changes the value of the element on the stack.
	 *
	 * @param value Desired value.
	 */
	Thread &operator=( ThreadValue const &value );
	using Element::operator=;

	operator ThreadValue() const noexcept;
};

}
