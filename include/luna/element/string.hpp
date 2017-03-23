/* luna/element/string.hpp
 * Copyleft zukonake
 * Distributed under GNU General Public License Version 3
 */

#pragma once

#include <luna/typedef.hpp>
#include <luna/value.hpp>
#include <luna/element/element.hpp>

namespace Luna
{
	
class RawStack;

class String : public Element
{
public:
	explicit String( const RawStack &rawStack, const Index &index = -1 );

	virtual ~String() = default;

	virtual const StringValue &operator*() const noexcept;

	virtual Type getType() const noexcept override;
	const StringValue &get() const noexcept;
private:
	StringValue mValue;
};

}
