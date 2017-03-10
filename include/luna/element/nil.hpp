/* luna/element/nil.hpp
 * Copyleft zukonake
 * Distributed under GNU General Public License Version 3
 */

#pragma once

#include <luna/typedef.hpp>
#include <luna/element/element.hpp>

namespace Luna
{
	
class Nil : public Element
{
public:
	explicit Nil( const RawStack &stack, const Index &index = -1 );
	Nil( Nil &&that );

	virtual ~Nil() = default;

	Nil &operator=( Nil &&that );

	virtual Type getType() const noexcept override;
};

}
