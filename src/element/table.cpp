#include <luna/typedef.hpp>
#include <luna/tableValue.hpp>
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
			TableValue::operator[]( stack.toNumber( -2 )) = stack.bind( -1 );
		}	
		else if( stack.getType( -2 ) == STRING )
		{
			TableValue::operator[]( stack.toString( -2 )) = stack.bind( -1 );
		}
		stack.pop();
	}
}

Table::Table( Table &&that ) :
	Element( dynamic_cast< Element && >( that )),
	TableValue( dynamic_cast< TableValue && >( that ))
{
	
}

Table &Table::operator=( Table &&that )
{
	Element::operator=( dynamic_cast< Element && >( that ));
	TableValue::operator=( dynamic_cast< TableValue && >( that ));
	return *this;
}

Type Table::getType() const noexcept
{
	return TABLE;
}

}
