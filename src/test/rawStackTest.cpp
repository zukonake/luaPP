#include <utility>
//
#include <boost/test/unit_test.hpp>
//
#include <luna/exception.hpp>
#include <luna/typedef.hpp>
#include <luna/auxiliary.hpp> //TODO
#include <luna/rawStack.hpp>

namespace Luna
{

BOOST_AUTO_TEST_SUITE( rawStackTest );

BOOST_AUTO_TEST_CASE( constructorDestructorTest )
{
	RawStack *tRawStack01 = nullptr;
	BOOST_REQUIRE_NO_THROW( tRawStack01 = new RawStack());
	BOOST_REQUIRE_NO_THROW( delete tRawStack01 );
}

BOOST_AUTO_TEST_CASE( moveTest )
{
	RawStack tRawStack01;	
	RawStack tRawStack02 = std::move( tRawStack01 );
	BOOST_CHECK( static_cast< const LuaState *>( tRawStack01.getState()) == nullptr );
	BOOST_CHECK( static_cast< const LuaState *>( tRawStack02.getState()) != nullptr );

	RawStack tRawStack03;	
	RawStack tRawStack04( std::move( tRawStack03 ));
	BOOST_CHECK( static_cast< const LuaState *>( tRawStack03.getState()) == nullptr );
	BOOST_CHECK( static_cast< const LuaState *>( tRawStack04.getState()) != nullptr );
}

BOOST_AUTO_TEST_CASE( writingTest )
{
	RawStack tRawStack01;
	BOOST_REQUIRE_NO_THROW( tRawStack01.pushNil());
	BOOST_CHECK( tRawStack01.getType() == NIL );

	RawStack tRawStack02;
	BOOST_REQUIRE_NO_THROW( tRawStack02.pushNumber( 25 ));
	BOOST_REQUIRE( tRawStack02.getType() == NUMBER );
	BOOST_CHECK_EQUAL( tRawStack02.toNumber(), 25 );

	RawStack tRawStack03;
	BOOST_REQUIRE_NO_THROW( tRawStack03.pushString( "tet" ));
	BOOST_REQUIRE( tRawStack03.getType() == STRING );
	BOOST_CHECK_EQUAL( tRawStack03.toString(), "tet" );
}

BOOST_AUTO_TEST_CASE( readingTest )
{
	RawStack tRawStack01;
	BOOST_REQUIRE_NO_THROW( tRawStack01.loadFile( "src/test/rawStackTest.lua" ));
	BOOST_REQUIRE_NO_THROW( tRawStack01.call());
	BOOST_REQUIRE_NO_THROW( tRawStack01.loadGlobal( "luna" ));
	BOOST_CHECK( tRawStack01.getType() == TABLE );
	BOOST_CHECK_EQUAL( tRawStack01.getSize(), 2 );

	RawStack tRawStack02;
	BOOST_REQUIRE_NO_THROW( tRawStack02.loadString( "var = 'test'" ));
	BOOST_REQUIRE_NO_THROW( tRawStack02.call());
	BOOST_REQUIRE_NO_THROW( tRawStack02.loadGlobal( "var" ));
	BOOST_CHECK_EQUAL( tRawStack02.toString(), "test" );
	BOOST_CHECK_EQUAL( tRawStack01.getSize(), 2 );

	RawStack tRawStack03;
	BOOST_REQUIRE_NO_THROW( tRawStack03.doFile( "src/test/rawStackTest.lua" ));
	BOOST_REQUIRE_NO_THROW( tRawStack03.loadGlobal( "luna" ));
	BOOST_CHECK( tRawStack01.getType() == TABLE );
	BOOST_CHECK_EQUAL( tRawStack01.getSize(), 2 );

	RawStack tRawStack04;
	BOOST_REQUIRE_NO_THROW( tRawStack04.doString( "var = 'test'" ));
	BOOST_REQUIRE_NO_THROW( tRawStack04.loadGlobal( "var" ));
	BOOST_CHECK_EQUAL( tRawStack04.toString(), "test" );
	BOOST_CHECK_EQUAL( tRawStack01.getSize(), 2 );

	RawStack tRawStack05;
	BOOST_REQUIRE_NO_THROW( tRawStack05.doFile( "src/test/rawStackTest.lua" ));
	BOOST_REQUIRE_NO_THROW( tRawStack05.loadGlobal( "luna" ));
	BOOST_CHECK_THROW( tRawStack05.toString(), std::runtime_error );
	BOOST_CHECK_THROW( tRawStack05.toNumber( -5 ), Exception::IndexError );
	BOOST_CHECK_THROW( tRawStack05.toNumber( 0 ), Exception::IndexError );
	BOOST_CHECK_THROW( tRawStack05.toNumber( 50 ), Exception::IndexError );

	RawStack tRawStack06;
	BOOST_REQUIRE_NO_THROW( tRawStack06.loadString( "var = 'test'" ));
	BOOST_CHECK_THROW( tRawStack06.call( -20 ), Exception::IndexError );
	BOOST_CHECK_THROW( tRawStack06.call( 0 ), Exception::IndexError );
	BOOST_CHECK_THROW( tRawStack06.call( 20 ), Exception::IndexError );

	RawStack tRawStack07;
	BOOST_REQUIRE_NO_THROW( tRawStack07.doString( "var = 'test'" ));
	BOOST_CHECK_THROW( tRawStack07.loadGlobal( "varr" ), Exception::StackError );

	RawStack tRawStack08;
	BOOST_CHECK_THROW( tRawStack08.loadGlobals(), Exception::StackError );

	RawStack tRawStack09;
	BOOST_REQUIRE_NO_THROW( tRawStack09.doString( "var = 'test'" ));
	BOOST_REQUIRE_NO_THROW( tRawStack09.loadGlobal( "var" ));
	BOOST_CHECK_EQUAL( tRawStack09.toString( -1 ), "test" );

	RawStack tRawStack10;
	BOOST_CHECK_THROW( tRawStack10.loadFile( "src/test/nofile.lua" ), Exception::FileError );
	BOOST_CHECK_THROW( tRawStack10.loadString( "invalidCode" ), Exception::SyntaxError );
}

BOOST_AUTO_TEST_CASE( rawMethodTest )
{
	RawStack tRawStack01;
	BOOST_REQUIRE_NO_THROW( tRawStack01.pushNumber( 64 ));
	BOOST_REQUIRE_NO_THROW( tRawStack01.pushString( "test" ));
	BOOST_CHECK_NO_THROW( tRawStack01.replace( -1, -2 ));
	BOOST_CHECK_THROW( tRawStack01.replace( 0, 0 ), Exception::IndexError );
	BOOST_CHECK_THROW( tRawStack01.replace( 100, 0 ), Exception::IndexError );
	BOOST_CHECK_THROW( tRawStack01.replace( -100, 0 ), Exception::IndexError );
	BOOST_CHECK_THROW( tRawStack01.replace( 0, 100 ), Exception::IndexError );
	BOOST_CHECK_THROW( tRawStack01.replace( 0, -100 ), Exception::IndexError );
	BOOST_CHECK_EQUAL( tRawStack01.getSize(), 2 );
	BOOST_CHECK_EQUAL( tRawStack01.toString( -1 ), tRawStack01.toString( -2 ));

	RawStack tRawStack02;
	BOOST_REQUIRE_NO_THROW( tRawStack02.pushNumber( 64 ));
	BOOST_REQUIRE_NO_THROW( tRawStack02.pushString( "test" ));
	BOOST_CHECK_NO_THROW( tRawStack02.swap( -1, -2 ));
	BOOST_CHECK_THROW( tRawStack02.swap( 100, 0 ), Exception::IndexError );
	BOOST_CHECK_THROW( tRawStack02.swap( -100, 0 ), Exception::IndexError );
	BOOST_CHECK_THROW( tRawStack02.swap( 0, 100 ), Exception::IndexError );
	BOOST_CHECK_THROW( tRawStack02.swap( 0, -100 ), Exception::IndexError );
	BOOST_CHECK_NO_THROW( tRawStack02.swap( 0, 0 ));
	BOOST_CHECK_EQUAL( tRawStack02.getSize(), 2 );
	BOOST_CHECK_EQUAL( tRawStack02.toNumber( -1 ), 64 ); 
	BOOST_CHECK_EQUAL( tRawStack02.toString( -2 ), "test" );

	RawStack tRawStack03;
	BOOST_REQUIRE_NO_THROW( tRawStack03.pushNumber( 64 ));
	BOOST_REQUIRE_EQUAL( tRawStack03.getSize(), 1 );
	BOOST_CHECK_NO_THROW( tRawStack03.copy( 1 ));
	BOOST_CHECK_THROW( tRawStack03.copy( 100 ), Exception::IndexError );
	BOOST_CHECK_THROW( tRawStack03.copy( 0 ), Exception::IndexError );
	BOOST_CHECK_THROW( tRawStack03.copy( -100 ), Exception::IndexError );
	BOOST_CHECK_EQUAL( tRawStack03.getSize(), 2 );
	BOOST_CHECK_EQUAL( tRawStack03.toNumber( -1 ), tRawStack03.toNumber( -2 ));

	RawStack tRawStack04;
	BOOST_REQUIRE_NO_THROW( tRawStack04.pushNumber( 64 ));
	BOOST_REQUIRE_EQUAL( tRawStack04.getSize(), 1 );
	BOOST_CHECK_NO_THROW( tRawStack04.copy( 1 ));
	BOOST_CHECK_THROW( tRawStack04.copy( 100 ), Exception::IndexError );
	BOOST_CHECK_THROW( tRawStack04.copy( 0 ), Exception::IndexError );
	BOOST_CHECK_THROW( tRawStack04.copy( -100 ), Exception::IndexError );
	BOOST_CHECK_EQUAL( tRawStack04.getSize(), 2 );
	BOOST_CHECK_EQUAL( tRawStack04.toNumber( -1 ), tRawStack04.toNumber( -2 ));

	RawStack tRawStack05;
	BOOST_REQUIRE_NO_THROW( tRawStack05.pushNumber( 64 ));
	BOOST_REQUIRE_NO_THROW( tRawStack05.pushString( "test" ));
	BOOST_REQUIRE_NO_THROW( tRawStack05.pushNumber( 32 ));
	BOOST_CHECK_NO_THROW( tRawStack05.insert( -3 ));
	BOOST_CHECK_THROW( tRawStack05.insert( 0 ), Exception::IndexError );
	BOOST_CHECK_THROW( tRawStack05.insert( 100 ), Exception::IndexError );
	BOOST_CHECK_THROW( tRawStack05.insert( -100 ), Exception::IndexError );
	BOOST_CHECK_EQUAL( tRawStack05.getSize(), 3 );
	BOOST_CHECK_EQUAL( tRawStack05.toNumber( -3 ), 32 );
	BOOST_CHECK_EQUAL( tRawStack05.toString( 3 ), "test" );

	RawStack tRawStack06;
	BOOST_REQUIRE_NO_THROW( tRawStack06.pushNumber( 64 ));
	BOOST_REQUIRE_NO_THROW( tRawStack06.pushString( "test" ));
	BOOST_REQUIRE_NO_THROW( tRawStack06.pushNumber( 32 ));
	BOOST_CHECK_NO_THROW( tRawStack06.remove( -2 ));
	BOOST_CHECK_THROW( tRawStack06.remove( 0 ), Exception::IndexError );
	BOOST_CHECK_THROW( tRawStack06.remove( 100 ), Exception::IndexError );
	BOOST_CHECK_THROW( tRawStack06.remove( -100 ), Exception::IndexError );
	BOOST_CHECK_EQUAL( tRawStack06.getSize(), 2 );
	BOOST_CHECK_EQUAL( tRawStack06.toNumber( -2 ), 64 );
	BOOST_CHECK_EQUAL( tRawStack06.toNumber( -1 ), 32 );

	RawStack tRawStack07;
	BOOST_REQUIRE_NO_THROW( tRawStack07.pushNumber( 64 ));
	BOOST_REQUIRE_NO_THROW( tRawStack07.pushString( "test" ));
	BOOST_REQUIRE_NO_THROW( tRawStack07.pushNumber( 32 ));
	BOOST_CHECK_NO_THROW( tRawStack07.erase( -2 ));
	BOOST_CHECK_THROW( tRawStack07.erase( 0 ), Exception::IndexError );
	BOOST_CHECK_THROW( tRawStack07.erase( 100 ), Exception::IndexError );
	BOOST_CHECK_THROW( tRawStack07.erase( -100 ), Exception::IndexError );
	BOOST_CHECK_EQUAL( tRawStack07.getSize(), 3 );
	BOOST_CHECK_EQUAL( tRawStack07.toNumber( -3 ), 64 );
	BOOST_CHECK( tRawStack07.getType( -2 ) == NIL );
	BOOST_CHECK_EQUAL( tRawStack07.toNumber( -1 ), 32 );

	RawStack tRawStack08;
	BOOST_REQUIRE_NO_THROW( tRawStack08.doString( "testTable = { var1 = 2, var2 = 'test' }" ));
	BOOST_REQUIRE_NO_THROW( tRawStack08.loadGlobal( "testTable" ));
	BOOST_REQUIRE_NO_THROW( tRawStack08.pushNil());
	BOOST_CHECK_THROW( tRawStack08.iterate( 0 ), Exception::IndexError );
	BOOST_CHECK_THROW( tRawStack08.iterate( 100 ), Exception::IndexError );
	BOOST_CHECK_THROW( tRawStack08.iterate( -100 ), Exception::IndexError );
	BOOST_CHECK_EQUAL( tRawStack08.getSize(), 3 );
	std::string key;
	while( tRawStack08.iterate())
	{
		BOOST_REQUIRE_NO_THROW( key = tRawStack08.toString( -2 ));
		if( key == "var1" )
		{
			BOOST_CHECK_EQUAL( tRawStack08.toNumber( -1 ), 2 );
		}	
		else if( key == "var2" )
		{	
			BOOST_CHECK_EQUAL( tRawStack08.toString( -1 ), "test" );
		}
		else
		{
			BOOST_REQUIRE( false );
		}
		BOOST_REQUIRE_NO_THROW( tRawStack08.pop());
	}

	RawStack tRawStack09;
	BOOST_REQUIRE_NO_THROW( tRawStack09.pushNumber( 64 ));
	BOOST_REQUIRE_NO_THROW( tRawStack09.pushString( "test" ));
	BOOST_REQUIRE_NO_THROW( tRawStack09.pushNumber( 32 ));
	BOOST_CHECK_NO_THROW( tRawStack09.pop( 2 ));
	BOOST_CHECK_NO_THROW( tRawStack09.pop( 0 ));
	BOOST_CHECK_THROW( tRawStack09.pop( 100 ), Exception::StackError );
	BOOST_CHECK_THROW( tRawStack09.pop( -100 ), Exception::StackError );
	BOOST_CHECK_EQUAL( tRawStack09.getSize(), 1 );
	BOOST_CHECK_EQUAL( tRawStack09.toNumber( -1 ), 64 );

	RawStack tRawStack10;
	BOOST_REQUIRE_NO_THROW( tRawStack10.pushNumber( 64 ));
	BOOST_REQUIRE_NO_THROW( tRawStack10.pushString( "test" ));
	BOOST_REQUIRE_NO_THROW( tRawStack10.pushNumber( 32 ));
	BOOST_CHECK_NO_THROW( tRawStack10.clear());
	BOOST_CHECK_EQUAL( tRawStack10.getSize(), 0 );

	RawStack tRawStack11;
	BOOST_REQUIRE_NO_THROW( tRawStack11.pushNumber( 64 ));
	BOOST_REQUIRE_NO_THROW( tRawStack11.pushString( "test" ));
	BOOST_CHECK_NO_THROW( tRawStack11.move( -1, -2 ));
	BOOST_CHECK_THROW( tRawStack11.move( 100, 0 ), Exception::IndexError );
	BOOST_CHECK_THROW( tRawStack11.move( -100, 0 ), Exception::IndexError );
	BOOST_CHECK_THROW( tRawStack11.move( 0, 100 ), Exception::IndexError );
	BOOST_CHECK_THROW( tRawStack11.move( 0, -100 ), Exception::IndexError );
	BOOST_CHECK_THROW( tRawStack11.move( 0, 0 ), Exception::IndexError );
	BOOST_CHECK_EQUAL( tRawStack11.getSize(), 1 );
	BOOST_CHECK_EQUAL( tRawStack11.toString( -1 ), "test" );
}

BOOST_AUTO_TEST_CASE( getTest )
{
	RawStack tRawStack01;
	BOOST_REQUIRE_NO_THROW( tRawStack01.pushNumber( 20 ));
	BOOST_CHECK_EQUAL( tRawStack01.isValid(), true );
	BOOST_CHECK_EQUAL( tRawStack01.isValid( 1 ), true );
	BOOST_CHECK_EQUAL( tRawStack01.isValid( -1 ), true );
	BOOST_CHECK_EQUAL( tRawStack01.isValid( 0 ), false );
	BOOST_CHECK_EQUAL( tRawStack01.isValid( 2 ), false );
	BOOST_CHECK_EQUAL( tRawStack01.isValid( -2 ), false );
	BOOST_CHECK_EQUAL( tRawStack01.isValid( 32768 ), false );
	BOOST_CHECK_EQUAL( tRawStack01.isValid( -32768 ), false );

	RawStack tRawStack02;
	BOOST_REQUIRE_NO_THROW( tRawStack02.pushNumber( 20 ));
	BOOST_CHECK_EQUAL( tRawStack02.getSize(), 1 );	
	BOOST_REQUIRE_NO_THROW( tRawStack02.pushNumber( 32 ));
	BOOST_CHECK_EQUAL( tRawStack02.getSize(), 2 );	
	BOOST_REQUIRE_NO_THROW( tRawStack02.pop( 1 ));
	BOOST_CHECK_EQUAL( tRawStack02.getSize(), 1 );

	RawStack tRawStack03;
	BOOST_CHECK( static_cast< const LuaState * >( tRawStack03.getState()) != nullptr );

	RawStack tRawStack04;
	BOOST_REQUIRE_NO_THROW( tRawStack04.pushNumber( 20 ));
	BOOST_CHECK_EQUAL( tRawStack04.getRelativeIndex( 1 ), -1 );	
	BOOST_CHECK_EQUAL( tRawStack04.getAbsoluteIndex( -1 ), 1 );	
	BOOST_CHECK_THROW( tRawStack04.getRelativeIndex( 1000 ), Exception::IndexError );	
	BOOST_CHECK_THROW( tRawStack04.getRelativeIndex( -1000 ), Exception::IndexError );
	BOOST_CHECK_THROW( tRawStack04.getRelativeIndex( 0 ), Exception::IndexError );
	BOOST_CHECK_THROW( tRawStack04.getAbsoluteIndex( 1000 ), Exception::IndexError );	
	BOOST_CHECK_THROW( tRawStack04.getAbsoluteIndex( -1000 ), Exception::IndexError );
	BOOST_CHECK_THROW( tRawStack04.getAbsoluteIndex( 0 ), Exception::IndexError );
	BOOST_REQUIRE_NO_THROW( tRawStack04.pushNumber( 32 ));
	BOOST_CHECK_EQUAL( tRawStack04.getRelativeIndex( 1 ), -2 );	
	BOOST_CHECK_EQUAL( tRawStack04.getAbsoluteIndex( -1 ), 2 );	
	BOOST_CHECK_EQUAL( tRawStack04.getRelativeIndex( 2 ), -1 );	
	BOOST_CHECK_EQUAL( tRawStack04.getAbsoluteIndex( -2 ), 1 );	
	BOOST_REQUIRE_NO_THROW( tRawStack04.pop( 1 ));
	BOOST_CHECK_EQUAL( tRawStack04.getRelativeIndex( 1 ), -1 );	
	BOOST_CHECK_EQUAL( tRawStack04.getAbsoluteIndex( -1 ), 1 );	

	RawStack tRawStack05;
	BOOST_REQUIRE_NO_THROW( tRawStack05.pushNumber( 20 ));
	BOOST_CHECK( tRawStack05.getType() == NUMBER );	
	BOOST_CHECK_THROW( tRawStack05.getType( 0 ), Exception::IndexError );
	BOOST_CHECK_THROW( tRawStack05.getType( 100 ), Exception::IndexError );
	BOOST_CHECK_THROW( tRawStack05.getType( -100 ), Exception::IndexError );
	BOOST_REQUIRE_NO_THROW( tRawStack05.pushString( "tet" ));
	BOOST_CHECK( tRawStack05.getType() == STRING );	
	BOOST_REQUIRE_NO_THROW( tRawStack05.pop( 1 ));
}

BOOST_AUTO_TEST_SUITE_END();

}
