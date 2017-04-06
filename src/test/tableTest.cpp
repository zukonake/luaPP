#include <stdexcept>
//
#include <boost/test/unit_test.hpp>
//
#include <luna/element/number.hpp>
#include <luna/element/string.hpp>
#include <luna/element/table.hpp>
#include <test/stackFixture.hpp>

namespace Luna::Test
{

BOOST_FIXTURE_TEST_SUITE( tableTest, StackFixture );

BOOST_AUTO_TEST_CASE( atTest00 )
{
	BOOST_REQUIRE_NO_THROW( fStack.doFile( "src/test/tableTest.lua" ));
	Table tTable01 = fStack.loadGlobal< Table >( "test" );
	BOOST_CHECK_EQUAL( tTable01.get< Number >( "var" ), 12 );
	BOOST_CHECK_EQUAL( tTable01.get< String >( "var1" ), "test" );
	BOOST_CHECK_EQUAL( tTable01.get< Number >( 1 ), 25 );
	BOOST_CHECK_EQUAL( tTable01.get< String >( 2 ), "test2" );

	Table tTable02 = tTable01.get< Table >( "var2" );
	BOOST_CHECK_EQUAL( tTable02.get< Number >( "var0" ), 120 );
	BOOST_CHECK_EQUAL( tTable02.get< String >( "var11" ), "test1" );
	BOOST_CHECK_EQUAL( tTable02.get< Number >( 1 ), 24 );
	BOOST_CHECK_EQUAL( tTable02.get< String >( 2 ), "test3" );	
	BOOST_CHECK_THROW( tTable01.get< String >( "invalidVar" ), std::out_of_range );
	BOOST_CHECK_THROW( tTable01.get< Table >( 3 ), std::out_of_range );
	BOOST_CHECK_THROW( tTable01.get< Number >( -1 ), std::out_of_range );
	BOOST_CHECK_THROW( tTable01.get< String >( 0 ), std::out_of_range );
}

//TODO set test

BOOST_AUTO_TEST_SUITE_END();

}
