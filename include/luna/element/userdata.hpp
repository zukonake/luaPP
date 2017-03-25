/* luna/element/userdata.hpp
 * Copyleft zukonake
 * Distributed under GNU General Public License Version 3
 */

#pragma once

#include <luna/typedef.hpp>
#include <luna/element/element.hpp>

namespace Luna
{
	
class Userdata : public Element
{
public:
	using Element::Element;

	virtual ~Userdata() = default;

	using Element::operator=;
};

}
