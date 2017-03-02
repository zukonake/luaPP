#include <utility>
//
#include <boost/test/unit_test.hpp>
#include <lua.hpp>
//
#include <luna/state.hpp>

namespace Luna
{

BOOST_AUTO_TEST_SUITE( stateTest );

BOOST_AUTO_TEST_CASE( constructorTest )
{
	BOOST_REQUIRE_NO_THROW( State());
}

BOOST_AUTO_TEST_CASE( conversionTest )
{
	State tState01;
	BOOST_REQUIRE( static_cast< lua_State * >( tState01 ) != nullptr );
	BOOST_CHECK_NO_THROW( lua_isnone( tState01, -1 ));
}

BOOST_AUTO_TEST_CASE( moveTest )
{
	State tState01;
	BOOST_REQUIRE( static_cast< lua_State * >( tState01 ) != nullptr );
	State tState02 = std::move( tState01 );
	BOOST_CHECK( static_cast< lua_State * >( tState01 ) == nullptr );
	BOOST_CHECK( static_cast< lua_State * >( tState02 ) != nullptr );
	BOOST_CHECK_NO_THROW( lua_isnone( tState02, -1 ));

	State tState03;
	BOOST_REQUIRE( static_cast< lua_State * >( tState03 ) != nullptr );
	State tState04( std::move( tState03 ));
	BOOST_CHECK( static_cast< lua_State * >( tState03 ) == nullptr );
	BOOST_CHECK( static_cast< lua_State * >( tState04 ) != nullptr );
	BOOST_CHECK_NO_THROW( lua_isnone( tState04, -1 ));
}

BOOST_AUTO_TEST_SUITE_END();

}
