/* luna/element/element.hpp
 * Copyleft zukonake
 * Distributed under GNU General Public License Version 3
 */

#pragma once

#include <luna/typedef.hpp>

namespace Luna
{

class RawStack;

class Element
{
public:
	explicit Element( RawStack const &stack, Index const &index = -1 );
	Element( Element &&that );

	virtual ~Element() = default;

	Element &operator=( Element &&that );

	virtual Index const &getIndex() const noexcept final;
protected:
	RawStack const &mRawStack;
private:
	Index mIndex;
};

}
