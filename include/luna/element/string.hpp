/* luna/element/string.hpp
 * Copyleft zukonake
 * Distributed under GNU General Public License Version 3
 */

#pragma once

#include <luna/typedef.hpp>
#include <luna/element/element.hpp>

namespace Luna
{
	
class RawStack;

class String : public Element, public StringValue
{
public:
	explicit String( RawStack const &rawStack, Index const &index = -1 );
	String( String &&that );

	virtual ~String() = default;

	String &operator=( String &&that );
};

}
