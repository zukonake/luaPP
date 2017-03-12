/* luna/element/number.hpp
 * Copyleft zukonake
 * Distributed under GNU General Public License Version 3
 */

#pragma once

#include <luna/typedef.hpp>
#include <luna/element/element.hpp>

namespace Luna
{

class RawStack;

class Number : public Element
{
public:
	typedef float Value;

	explicit Number( const RawStack &rawStack, const Index &index = -1 );

	virtual ~Number() = default;

	virtual const Value &operator*() const noexcept;

	virtual Type getType() const noexcept override;
	const Value &get() const noexcept;
private:
	Value mValue;
};

}
