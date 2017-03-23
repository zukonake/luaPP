/* luna/element/thread.hpp
 * Copyleft zukonake
 * Distributed under GNU General Public License Version 3
 */

#pragma once

#include <luna/typedef.hpp>
#include <luna/element/element.hpp>

namespace Luna
{
	
class Thread : public Element
{
public:
	using Element::Element;

	virtual ~Thread() = default;

	using Element::operator=;

	virtual Type getType() const noexcept override;
};

}
