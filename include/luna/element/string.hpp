/* luna/element/string.hpp
 * Copyleft zukonake
 * Distributed under GNU General Public License Version 3
 */

#pragma once

#include <string>
//
#include <luna/typedef.hpp>
#include <luna/element/element.hpp>

namespace Luna
{
	
class RawStack;

class String : public Element
{
public:
	typedef std::string Value;

	explicit String( const RawStack &rawStack, const Index &index = -1 );

	virtual ~String() = default;

	virtual const Value &operator*() const noexcept;

	virtual Type getType() const noexcept override;
	const Value &get() const noexcept;
private:
	Value mValue;
};

}
