/* luna/element/number.hpp
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

class Number : public Element
{
public:
	explicit Number( const RawStack &rawStack, const Index &index = -1 );
	Number( Number &&that );

	virtual ~Number() = default;

	Number &operator=( Number &&that );
	virtual const NumberValue &operator*() const noexcept;

	virtual Type getType() const noexcept override;
	const NumberValue &get() const noexcept;
private:
	NumberValue mValue;
};

}
