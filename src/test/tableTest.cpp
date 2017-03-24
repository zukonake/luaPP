#include <memory>
#include <stdexcept>
//
#include <boost/test/unit_test.hpp>
//
#include <luna/exception.hpp>
#include <luna/typedef.hpp>
#include <luna/element/number.hpp>
#include <luna/element/string.hpp>
#include <luna/element/table.hpp>
#include <luna/stack.hpp>

namespace Luna
{

BOOST_AUTO_TEST_SUITE( tableTest );

BOOST_AUTO_TEST_CASE( test )
{
	Stack tStack01;
	tStack01.doFile( "src/test/tableTest.lua" );
	tStack01.loadGlobal( "test" );
	std::shared_ptr< const Table > tTable01;
	BOOST_REQUIRE( tTable01 = std::make_shared< const Table >( tStack01, -1 ));
	BOOST_CHECK( tTable01->getType() == TABLE );
	BOOST_CHECK_EQUAL( **tTable01->at< Number >( "var" ), 12 );
	BOOST_CHECK_EQUAL( **tTable01->at< String >( "var1" ), "test" );
	BOOST_CHECK_EQUAL( **tTable01->at< Number >( 1 ), 25 );
	BOOST_CHECK_EQUAL( **tTable01->at< String >( 2 ), "test2" );

	std::shared_ptr< const Table > tTable02;
	BOOST_REQUIRE_NO_THROW( tTable02 = tTable01->at< Table >( "var2" ));
	BOOST_CHECK_EQUAL( **tTable02->at< Number >( "var0" ), 120 );
	BOOST_CHECK_EQUAL( **tTable02->at< String >( "var11" ), "test1" );
	BOOST_CHECK_EQUAL( **tTable02->at< Number >( 1 ), 24 );
	BOOST_CHECK_EQUAL( **tTable02->at< String >( 2 ), "test3" );	
	BOOST_CHECK_THROW( tTable01->at< String >( "invalidVar" ), std::out_of_range );
	BOOST_CHECK_THROW( tTable01->at< Table >( 3 ), std::out_of_range );
	BOOST_CHECK_THROW( tTable01->at< Number >( -1 ), std::out_of_range );
	BOOST_CHECK_THROW( tTable01->at< String >( 0 ), std::out_of_range );

	Stack tStack02;
	std::shared_ptr< const Table > tTable03;
	BOOST_CHECK_THROW( tTable03 = std::make_shared< const Table >( tStack02, -1 ), Exception::IndexError );
}

BOOST_AUTO_TEST_SUITE_END();

}
