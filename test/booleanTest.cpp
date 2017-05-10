#include <boost/test/unit_test.hpp>
//
#include <luna/typedef.hpp>
#include <luna/element/boolean.hpp>
#include <rawStackFixture.hpp>

namespace Luna::Test
{

BOOST_FIXTURE_TEST_SUITE( booleanTest, RawStackFixture );

BOOST_AUTO_TEST_CASE( conversionTest00 )
{
	BOOST_REQUIRE_NO_THROW( fRawStack.pushBoolean( true ));
	BOOST_REQUIRE_NO_THROW( fRawStack.pushBoolean( false ));
	Boolean tBoolean00( fRawStack, -2 );
	BOOST_CHECK_EQUAL( tBoolean00, true );
	BOOST_CHECK_EQUAL( fRawStack.getSize(), 2 );
}

BOOST_AUTO_TEST_SUITE_END();

}
