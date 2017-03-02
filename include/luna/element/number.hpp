/* luna/element/number.hpp
 * Copyleft zukonake
 * Distributed under GNU General Public License Version 3
 */

#pragma once

#include <luna/typedef.hpp>
#include <luna/element/element.hpp>

namespace Luna
{
	
class Number : public Element
{
public:
	typedef float Value;

	explicit Number( const Stack &stack, const Index &index = -1 );
	Number( Number &&that );

	virtual ~Number() = default;

	Number &operator=( Number &&that );

	virtual Type getType() const noexcept override;

	Value get() const noexcept;
private:
	Value mValue;
};

}
