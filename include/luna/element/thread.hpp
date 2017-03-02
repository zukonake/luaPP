/* luna/element/thread.hpp
 * Copyleft zukonake
 * Distributed under GNU General Public License Version 3
 */

#pragma once

#include <luna/typedef.hpp>
#include <luna/element/element.hpp>

namespace Luna
{
	
class Thread : public Element
{
public:
	explicit Thread( const Stack &stack, const Index &index = -1 );
	Thread( Thread &&that );

	virtual ~Thread() = default;

	Thread &operator( Thread &&that );

	virtual Type getType() const noexcept override;
};

}
