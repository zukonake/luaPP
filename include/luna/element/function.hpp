/* luna/element/function.hpp
 * Copyleft zukonake
 * Distributed under GNU General Public License Version 3
 */

#pragma once

#include <luna/typedef.hpp>
#include <luna/element/element.hpp>

namespace Luna
{
	
class Function : public Element
{
public:
	explicit Function( const Stack &stack, const Index &index = -1 );
	Function( Function &&that );

	virtual ~Function() = default;

	Function &operator=( Function &&that );

	virtual Type getType() const noexcept override;
};

}
