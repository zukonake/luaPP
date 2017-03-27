#include <utility>
//
#include <luna/typedef.hpp>
#include <luna/rawStack.hpp>
#include <luna/element/table.hpp>

namespace Luna
{

Table::Table( RawStack const &rawStack, Index const &index ) :
	Element( rawStack , index )
{
	AbsoluteIndex realIndex = rawStack.getAbsoluteIndex( index );
	rawStack.pushNil();
	while( rawStack.iterate( realIndex ))
	{
		rawStack.insert( -2 );
		if( rawStack.getType( -1 ) == NUMBER )
		{
			this->operator[]( rawStack.toNumber( -1 )) = rawStack.getAbsoluteIndex( -2 );
		}	
		else if( rawStack.getType( -1 ) == STRING )
		{
			this->operator[]( rawStack.toString( -1 )) = rawStack.getAbsoluteIndex( -2 );
		}
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

Index &Table::operator[]( const std::size_t &index )
{	
	return TableValue::first[ index ];
}

Index &Table::operator[]( const std::string &key )
{
	return TableValue::second[ key ];
}

}
