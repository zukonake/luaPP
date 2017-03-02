/* luna/element/userdata.hpp
 * Copyleft zukonake
 * Distributed under GNU General Public License Version 3
 */

#pragma once

#include <luna/typedef.hpp>
#include <luna/element/element.hpp>

namespace Luna
{
	
class Userdata : public Element
{
public:
	explicit Userdata( const Stack &stack, const Index &index = -1 );
	Userdata( Userdata &&that );

	virtual ~Userdata() = default;

	Userdata &operator( Userdata &&that );

	virtual Type getType() const noexcept override;
};

}
