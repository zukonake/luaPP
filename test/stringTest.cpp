#include <memory>
//
#include <boost/test/unit_test.hpp>
//
#include <luna/typedef.hpp>
#include <luna/rawStack.hpp>
#include <luna/element/string.hpp>
#include <rawStackFixture.hpp>

namespace Luna::Test::Test
{

BOOST_FIXTURE_TEST_SUITE( stringTest, RawStackFixture,
	* boost::unit_test::depends_on( "rawStackTest" )
	* boost::unit_test::depends_on( "elementTest" ));

BOOST_AUTO_TEST_CASE( conversionTest00 )
{
	BOOST_REQUIRE_NO_THROW( fRawStack.pushString( "test" ));
	BOOST_REQUIRE_NO_THROW( fRawStack.pushString( "xd" ));
	String tString00( fRawStack, -1 );
	BOOST_CHECK_EQUAL( tString00, "xd" );
	BOOST_CHECK_EQUAL( fRawStack.getSize(), 2 );
}

BOOST_AUTO_TEST_SUITE_END();

}
