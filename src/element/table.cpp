#include <luna/typedef.hpp>
#include <luna/value.hpp>
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

Table::Table( Table &&that ) :
	Element( dynamic_cast< Element && >( that )),
	TableValue( dynamic_cast< TableValue && >( that ))
{
	
}

Table &Table::operator=( Table &&that )
{
	dynamic_cast< Element && >( *this ) = dynamic_cast< Element && >( that );
	dynamic_cast< TableValue && >( *this ) = dynamic_cast< TableValue && >( that );
	return *this;
}

Type Table::getType() const noexcept
{
	return TABLE;
}

}
