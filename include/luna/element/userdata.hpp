/* @file luna/element/userData.hpp
 * @copyright Copyleft zukonake
 * @license Distributed under GNU General Public License Version 3
 */

#pragma once

#include<luna/typedef.hpp>
#include<luna/element/element.hpp>

namespace Luna
{

/**
 * Represents a user data value on the stack.
 */	
class UserData : public Element
{
public:
	using Element::Element;

	~UserData() = default;

	/**
	 * Changes the value of the user data on the stack.
	 *
	 * @param value Desired value.
	 */
	UserData &operator=( UserDataValue const &value );
	using Element::operator=;

	operator UserDataValue() const noexcept;
};

}
