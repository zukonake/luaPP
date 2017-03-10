/* luna/element/string.hpp
 * Copyleft zukonake
 * Distributed under GNU General Public License Version 3
 */

#pragma once

#include <luna/typedef.hpp>
#include <luna/element/element.hpp>

namespace Luna
{
	
class String : public Element
{
public:
	typedef std::string Value;

	explicit String( const RawStack &stack, const Index &index = -1 );
	String( String &&that );

	virtual ~String() = default;

	String &operator=( String &&that );

	virtual Type getType() const noexcept override;

	Value get() const noexcept;
private:
	Value mValue;
};

}
