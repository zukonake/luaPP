/* @file luna/element/string.hpp
 * @copyright Copyleft zukonake
 * @license Distributed under GNU General Public License Version 3
 */

#pragma once

#include<luna/typedef.hpp>
#include<luna/element/element.hpp>

namespace Luna
{

/**
 * Represents a string value on the stack.
 */	
class String : public Element
{
public:
	String( String const &that );
	using Element::Element;

	~String() = default;

	String &operator=( String const &that );

	/**
	 * Changes the value of the element on the stack.
	 * 
	 * @param value Desired value.
	 */
	String &operator=( StringValue const &value );
	using Element::operator=;

	operator StringValue() const noexcept;
	operator char const *() const noexcept;
};

}
