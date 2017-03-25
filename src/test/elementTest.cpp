#include <boost/test/unit_test.hpp>
//
#include <luna/typedef.hpp>
#include <luna/auxiliary.hpp>
#include <luna/rawStack.hpp>
#include <luna/element/element.hpp>

namespace Luna
{

BOOST_AUTO_TEST_SUITE( elementTest );

BOOST_AUTO_TEST_CASE( test )
{
	RawStack tRawStack01;
	BOOST_REQUIRE_NO_THROW( tRawStack01.pushNumber( 25 ));
	Element *tElement01 = nullptr;
	BOOST_CHECK_NO_THROW( tElement01 = new Element( tRawStack01, -1 ));
	BOOST_CHECK_NO_THROW( delete tElement01 );
	BOOST_CHECK_EQUAL( tRawStack01.getSize(), 1 );

	BOOST_REQUIRE_NO_THROW( tRawStack01.pushNumber( 24 ));
	BOOST_REQUIRE_NO_THROW( tRawStack01.pushNumber( 12 ));
	{
		BOOST_REQUIRE_NO_THROW( Element( tRawStack01, 2 ));
	}
	BOOST_CHECK_EQUAL( tRawStack01.getSize(), 3 );
}

BOOST_AUTO_TEST_SUITE_END();

}
