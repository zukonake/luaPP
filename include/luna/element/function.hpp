/* @file luna/element/function.hpp
 * @copyright Copyleft zukonake
 * @license Distributed under GNU General Public License Version 3
 */

#pragma once

#include<luna/typedef.hpp>
#include<luna/element/element.hpp>

namespace Luna
{

/**
 * Represents a function value on the stack.
 */	
class Function : public Element
{
public:
	using Element::Element;

	~Function() = default;

	/**
	 * Changes the value of the element on the stack.
	 *
	 * @param value Desired value.
	 */
	Boolean &operator=( FunctionValue const &value );
	using Element::operator=;

	operator FunctionValue() const noexcept;

	Size call() const;
};

}
