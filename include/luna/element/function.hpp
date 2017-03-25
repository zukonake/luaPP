/* luna/element/function.hpp
 * Copyleft zukonake
 * Distributed under GNU General Public License Version 3
 */

#pragma once

#include <luna/typedef.hpp>
#include <luna/element/element.hpp>

namespace Luna
{
	
class Function : public Element
{
public:
	using Element::Element;

	virtual ~Function() = default;

	using Element::operator=;

	Size call() const;
};

}
