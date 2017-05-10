#include <boost/test/unit_test.hpp>
//
#include <luna/typedef.hpp>
#include <luna/auxiliary.hpp>
#include <luna/element/element.hpp>
#include <rawStackFixture.hpp>

namespace Luna::Test
{

BOOST_FIXTURE_TEST_SUITE( elementTest, RawStackFixture );

BOOST_AUTO_TEST_CASE( getValueTest00 )
{
	BOOST_REQUIRE_NO_THROW( fRawStack.pushNumber( 62 ));
	BOOST_CHECK_EQUAL( fRawStack.getSize(), 1 );
	Element tElement00( fRawStack );
	BOOST_CHECK_EQUAL( fRawStack.getSize(), 0 );
	BOOST_REQUIRE_NO_THROW( tElement00.getValue());
	BOOST_REQUIRE_NO_THROW( tElement00.getValue());
	BOOST_CHECK_EQUAL( fRawStack.getSize(), 2 );
	BOOST_CHECK_EQUAL( fRawStack.toNumber(), 62 );
}

BOOST_AUTO_TEST_SUITE_END();

}
