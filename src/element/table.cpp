#include <luna/typedef.hpp>
#include <luna/element/table.hpp>
#include <luna/stack.hpp>

namespace Luna
{

Table::Table( const Stack &stack, const Index &index ) :
	Element( dynamic_cast< const RawStack & >( stack ), index )
{
	AbsoluteIndex realIndex = stack.getAbsoluteIndex( index );
	stack.pushNil();
	while( stack.iterate( realIndex ))
	{
		if( stack.getType( -2 ) == NUMBER )
		{
			this->operator[]( stack.toNumber( -2 )) = stack.bind( -1 );
		}	
		else if( stack.getType( -2 ) == STRING )
		{
			this->operator[]( stack.toString( -2 )) = stack.bind( -1 );
		}
		stack.pop();
	}
}

const TableValue &Table::operator*() const noexcept
{
	return dynamic_cast< const TableValue & >( *this );
}

Type Table::getType() const noexcept
{
	return TABLE;
}

const TableValue &Table::get() const noexcept
{
	return dynamic_cast< const TableValue & >( *this );
}

}
