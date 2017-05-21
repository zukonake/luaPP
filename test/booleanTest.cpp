#include <boost/test/unit_test.hpp>
//
#include <luna/typedef.hpp>
#include <luna/element/boolean.hpp>
#include "rawStackFixture.hpp"

namespace Luna::Test
{

BOOST_FIXTURE_TEST_SUITE( booleanTest, RawStackFixture,
	* boost::unit_test::depends_on( "rawStackTest" )
	* boost::unit_test::depends_on( "elementTest" ));

BOOST_AUTO_TEST_CASE( conversionTest00 )
{
	BOOST_REQUIRE_NO_THROW( fRawStack.pushBoolean( true ));
	Boolean tBoolean00( fRawStack );
	BOOST_REQUIRE_NO_THROW( fRawStack.pushBoolean( false ));
	BOOST_CHECK_EQUAL( tBoolean00, true );
	BOOST_CHECK_EQUAL( fRawStack.getSize(), 1 );
}

BOOST_AUTO_TEST_SUITE_END();

}
