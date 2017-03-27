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
	explicit Number( RawStack const &rawStack, Index const &index = -1 );
	Number( Number &&that );

	virtual ~Number() = default;

	Number &operator=( Number &&that );
	operator NumberValue const &() const noexcept;
private:
	NumberValue mValue;
};

}
