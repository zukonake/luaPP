/* luna/element/table.hpp
 * Copyleft zukonake
 * Distributed under GNU General Public License Version 3
 */

#pragma once

#include <luna/typedef.hpp>
#include <luna/tableValue.hpp>
#include <luna/element/element.hpp>

namespace Luna
{

class Stack;

class Table : public Element, public TableValue
{
public:
	explicit Table( const Stack &stack, const Index &index = -1 );
	Table( Table &&that );

	virtual ~Table() = default;

	using TableValue::operator[];

	Table &operator=( Table &&that );

	using TableValue::at;

	virtual Type getType() const noexcept override;
};

}
