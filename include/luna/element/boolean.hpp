/* @file luna/element/boolean.hpp
 * @copyright Copyleft zukonake
 * @license Distributed under GNU General Public License Version 3
 */

#pragma once

#include<luna/typedef.hpp>
#include<luna/element/element.hpp>

namespace Luna
{

/**
 * Represents a boolean value on the stack.
 */
class Boolean : public Element
{
public:
	using Element::Element;
	Boolean( Boolean const &that );

	~Boolean() = default;

	Boolean &operator=( Boolean const &that );

	/**
	 * Changes the value of the element on the stack.
	 *
	 * @param value Desired value.
	 */
	Boolean &operator=( BooleanValue const &value );
	using Element::operator=;

	operator BooleanValue() const noexcept;
};

}
