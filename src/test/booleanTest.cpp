#include <boost/test/unit_test.hpp>
//
#include <luna/typedef.hpp>
#include <luna/rawStack.hpp>
#include <luna/element/boolean.hpp>

namespace Luna
{

BOOST_AUTO_TEST_SUITE( booleanTest );

BOOST_AUTO_TEST_CASE( test )
{
	RawStack tRawStack01;
	BOOST_REQUIRE_NO_THROW( tRawStack01.pushBoolean( true ));
	BOOST_REQUIRE_NO_THROW( tRawStack01.pushBoolean( false ));
	Boolean tBoolean01( tRawStack01, -2 );
	BOOST_CHECK_EQUAL( tBoolean01, true );
	BOOST_CHECK_EQUAL( tRawStack01.getSize(), 2 );
}

BOOST_AUTO_TEST_SUITE_END();

}
