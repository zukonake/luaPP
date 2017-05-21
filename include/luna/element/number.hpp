/**
 * @file luna/element/number.hpp
 * @copyright Copyleft zukonake
 * @license Distributed under GNU General Public License Version 3
 */

#pragma once

#include<luna/typedef.hpp>
#include<luna/element/element.hpp>

namespace Luna
{

/**
 * Represents a number value on the stack.
 */
class Number : public Element
{
public:
	Number( Number const &that );
	using Element::Element;

	~Number() = default;

	Number &operator=( Number const &that );

	/** 
	 * Changes the value of the element on the stack.
	 *
	 * @param value Desired value.
	 */
	Number &operator=( NumberValue const &value );
	using Element::operator=;

	operator NumberValue() const;
};

}
