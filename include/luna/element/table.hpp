/* luna/element/table.hpp
 * Copyleft zukonake
 * Distributed under GNU General Public License Version 3
 */

#pragma once

#include <luna/typedef.hpp>
#include <luna/value.hpp>
#include <luna/element/element.hpp>

namespace Luna
{

class Stack;

class Table : public Element, public TableValue
{
public:
	explicit Table( const Stack &stack, const Index &index = -1 );

	virtual ~Table() = default;

	using TableValue::operator[];

	const TableValue &operator*() const noexcept;

	virtual Type getType() const noexcept override;

	const TableValue &get() const noexcept;
};

}
