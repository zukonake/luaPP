/* luna/element/lightUserdata.hpp
 * Copyleft zukonake
 * Distributed under GNU General Public License Version 3
 */

#pragma once

#include <luna/typedef.hpp>
#include <luna/element/element.hpp>

namespace Luna
{
	
class LightUserdata : public Element
{
public:
	explicit LightUserdata( const RawStack &stack, const Index &index = -1 );
	LightUserdata( LightUserdata &&that );

	virtual ~LightUserdata() = default;

	LightUserdata &operator=( LightUserdata &&that );

	virtual Type getType() const noexcept override;
};

}
