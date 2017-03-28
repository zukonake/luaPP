#include <stdexcept>
//
#include <boost/test/unit_test.hpp>
//
#include <luna/element/number.hpp>
#include <luna/element/string.hpp>
#include <luna/element/table.hpp>
#include <luna/test/stackFixture.hpp>

namespace Luna::Test
{

BOOST_FIXTURE_TEST_SUITE( tableTest, StackFixture );

BOOST_AUTO_TEST_CASE( atTest00 )
{
	BOOST_REQUIRE_NO_THROW( fStack.doFile( "src/test/tableTest.lua" ));
	Table tTable01 = fStack.loadGlobal< Table >( "test" );
	BOOST_CHECK_EQUAL( tTable01.at< Number >( "var" ), 12 );
	BOOST_CHECK_EQUAL( tTable01.at< String >( "var1" ), "test" );
	BOOST_CHECK_EQUAL( tTable01.at< Number >( 1 ), 25 );
	BOOST_CHECK_EQUAL( tTable01.at< String >( 2 ), "test2" );

	Table tTable02 = tTable01.at< Table >( "var2" );
	BOOST_CHECK_EQUAL( tTable02.at< Number >( "var0" ), 120 );
	BOOST_CHECK_EQUAL( tTable02.at< String >( "var11" ), "test1" );
	BOOST_CHECK_EQUAL( tTable02.at< Number >( 1 ), 24 );
	BOOST_CHECK_EQUAL( tTable02.at< String >( 2 ), "test3" );	
	BOOST_CHECK_THROW( tTable01.at< String >( "invalidVar" ), std::out_of_range );
	BOOST_CHECK_THROW( tTable01.at< Table >( 3 ), std::out_of_range );
	BOOST_CHECK_THROW( tTable01.at< Number >( -1 ), std::out_of_range );
	BOOST_CHECK_THROW( tTable01.at< String >( 0 ), std::out_of_range );
}

//TODO operator[] test

BOOST_AUTO_TEST_SUITE_END();

}
