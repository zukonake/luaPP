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
	explicit Element( RawStack &rawStack );
	Element( RawStack &rawStack, LuaReference const &reference );
	Element( Element &&that );

	virtual ~Element() = default;

	Element &operator=( Element &&that );

	virtual LuaReference const &getReference() const noexcept final;
protected:
	RawStack &mRawStack;
private:
	LuaReference mReference;
};

}
