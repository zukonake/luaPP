/* @file luna/element/lightUserData.hpp
 * @copyright Copyleft zukonake
 * @license Distributed under GNU General Public License Version 3
 */

#pragma once

#include<luna/typedef.hpp>
#include<luna/element/element.hpp>

namespace Luna
{
	
/**
 * Represents a light user data value on the stack.
 */
class LightUserData : public Element
{
public:
	using Element::Element;

	~LightUserData() = default;

	/**
	 * Changes the value of the element on the stack.
	 *
	 * @param value Desired value.
	 */
	LightUserData &operator( LightUserDataValue const &value );
	using Element::operator=;

	operator LightUserDataValue() const noexcept;
};

}
