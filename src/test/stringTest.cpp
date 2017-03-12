#include <memory>
//
#include <boost/test/unit_test.hpp>
//
#include <luna/typedef.hpp>
#include <luna/rawStack.hpp>
#include <luna/element/string.hpp>

namespace Luna
{

BOOST_AUTO_TEST_SUITE( stringTest );

BOOST_AUTO_TEST_CASE( test )
{
	RawStack tRawStack01;
	BOOST_REQUIRE_NO_THROW( tRawStack01.pushString( "test" ));
	BOOST_REQUIRE_NO_THROW( tRawStack01.pushString( "xd" ));
	std::shared_ptr< const String > tString01;
	BOOST_REQUIRE_NO_THROW( tString01 = std::make_shared< const String >( tRawStack01, -1 ));
	BOOST_CHECK( tString01->getType() == STRING );
	BOOST_CHECK( tString01->get() == "xd" );
	BOOST_CHECK( **tString01 == "xd" );
	BOOST_CHECK_EQUAL( tRawStack01.getSize(), 2 );
}

BOOST_AUTO_TEST_SUITE_END();

}
