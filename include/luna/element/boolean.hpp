/* luna/element/boolean.hpp
 * Copyleft zukonake
 * Distributed under GNU General Public License Version 3
 */

#pragma once

#include <luna/typedef.hpp>
#include <luna/element/element.hpp>

namespace Luna
{

class RawStack;

class Boolean : public Element
{
public:
	explicit Boolean( const RawStack &rawStack, const Index &index = -1 );
	Boolean( Boolean &&that );

	virtual ~Boolean() = default;

	Boolean &operator=( Boolean &&that );
	operator const bool &() const noexcept;
private:
	bool mValue;
};

}
