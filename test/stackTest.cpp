#include <boost/test/unit_test.hpp>
//
#include <luna/exception.hpp>
#include <luna/element/number.hpp>
#include <luna/element/string.hpp>
#include <luna/element/table.hpp>
#include <stackFixture.hpp>

namespace Luna::Test
{

BOOST_FIXTURE_TEST_SUITE( stackTest, StackFixture );

BOOST_AUTO_TEST_CASE( atTest00 )
{
	BOOST_REQUIRE_NO_THROW( fStack.pushNumber( 31 ));
	BOOST_REQUIRE_NO_THROW( fStack.pushString( "asdf" ));
	BOOST_CHECK_EQUAL( fStack.at< Number >( -2 ), 31 );
	BOOST_CHECK_EQUAL( fStack.at< String >( 2 ), "asdf" );
	BOOST_CHECK_EQUAL( fStack.getSize(), 2 );
}

BOOST_AUTO_TEST_CASE( atTest01 )
{
	BOOST_REQUIRE_NO_THROW( fStack.pushNumber( 31 ));
	BOOST_REQUIRE_NO_THROW( fStack.pushString( "asdf" ));
	BOOST_CHECK_THROW( fStack.at< Number >( -3 ), Exception::IndexError );
	BOOST_CHECK_THROW( fStack.at< String >( 3 ), Exception::IndexError );
	BOOST_CHECK_EQUAL( fStack.getSize(), 2 );
}

BOOST_AUTO_TEST_CASE( loadGlobalTest00 )
{	
	BOOST_REQUIRE_NO_THROW( fStack.doFile( "stackTest.lua" ));
	Number tNumber00 = fStack.loadGlobal< Number >( "var" );
	BOOST_CHECK_EQUAL( tNumber00, 234 );
}

BOOST_AUTO_TEST_CASE( loadGlobalTest01 )
{	
	BOOST_CHECK_THROW( fStack.loadGlobal< Number >( "var" ), Exception::StackError );
	BOOST_CHECK_EQUAL( fStack.getSize(), 0 );
}

BOOST_AUTO_TEST_CASE( loadGlobalTest02 )
{	
	BOOST_REQUIRE_NO_THROW( fStack.doFile( "stackTest.lua" ));
	BOOST_CHECK_THROW( fStack.loadGlobal< String >( "var" ), Exception::TypeError );
}

BOOST_AUTO_TEST_SUITE_END();

}
