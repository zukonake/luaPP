#include <boost/test/unit_test.hpp>
//
#include <luna/typedef.hpp>
#include <luna/element/number.hpp>
#include <rawStackFixture.hpp>

namespace Luna::Test
{

BOOST_FIXTURE_TEST_SUITE( numberTest, RawStackFixture,
	* boost::unit_test::depends_on( "rawStackTest" )
	* boost::unit_test::depends_on( "elementTest" ));

BOOST_AUTO_TEST_CASE( conversionTest )
{
	BOOST_REQUIRE_NO_THROW( fRawStack.pushNumber( 32 ));
	BOOST_REQUIRE_NO_THROW( fRawStack.pushNumber( 24 ));
	Number tNumber00( fRawStack, -2 );
	BOOST_CHECK_EQUAL( tNumber00, 32 );
	BOOST_CHECK_EQUAL( fRawStack.getSize(), 2 );
}

BOOST_AUTO_TEST_SUITE_END();

}
