/* luna/element/element.hpp
 * Copyleft zukonake
 * Distributed under GNU General Public License Version 3
 */

#pragma once

#include <luna/typedef.hpp>

namespace Luna
{

class Stack;

class Element
{
public:
	explicit Element( const Stack &stack, const Index &index = -1 );
	Element( Element &&that );

	virtual ~Element();

	Element &operator=( Element &&that );

	virtual Type getType() const noexcept = 0;
private:
	const Stack &mStack;
	Index mIndex;
};

}
