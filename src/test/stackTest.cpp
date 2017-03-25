#include <boost/test/unit_test.hpp>
//
#include <memory>
//
#include <luna/exception.hpp>
#include <luna/typedef.hpp>
#include <luna/element/number.hpp>
#include <luna/element/string.hpp>
#include <luna/stack.hpp>

namespace Luna
{

BOOST_AUTO_TEST_SUITE( stackTest );

BOOST_AUTO_TEST_CASE( constructorDestructorTest )
{
	Stack *tStack01 = nullptr;
	BOOST_REQUIRE_NO_THROW( tStack01 = new Stack());
	BOOST_REQUIRE_NO_THROW( delete tStack01 );
}

BOOST_AUTO_TEST_CASE( moveTest )
{
	Stack tStack01;	
	Stack tStack02 = std::move( tStack01 );
	BOOST_CHECK( static_cast< const LuaState *>( tStack01.getState()) == nullptr );
	BOOST_CHECK( static_cast< const LuaState *>( tStack02.getState()) != nullptr );

	Stack tStack03;	
	Stack tStack04( std::move( tStack03 ));
	BOOST_CHECK( static_cast< const LuaState *>( tStack03.getState()) == nullptr );
	BOOST_CHECK( static_cast< const LuaState *>( tStack04.getState()) != nullptr );
}

BOOST_AUTO_TEST_CASE( bindTest )
{
	Stack tStack01;
	BOOST_REQUIRE_NO_THROW( tStack01.pushNumber( 54 ));
	std::shared_ptr< const Number > tNumber01 = tStack01.bind< Number >();
	BOOST_CHECK_EQUAL( **tNumber01, 54 );
	BOOST_REQUIRE_NO_THROW( tStack01.pushNumber( 23 ));
	BOOST_CHECK_EQUAL( **tStack01.bind< Number >( -2 ), 54 );
	BOOST_CHECK_THROW( tStack01.bind< Number >( 0 ), Exception::IndexError );
	BOOST_CHECK_THROW( tStack01.bind< Number >( 2000 ), Exception::IndexError );
	BOOST_CHECK_THROW( tStack01.bind< Number >( -4055 ), Exception::IndexError );
}

BOOST_AUTO_TEST_CASE( loadGlobalsTest )
{
	Stack tStack01;
	BOOST_REQUIRE_NO_THROW( tStack01.doFile( "src/test/stackTest.lua" ));
	BOOST_CHECK_EQUAL( **tStack01.loadGlobals().at< Number >( "var" ), 25 );
	BOOST_CHECK_THROW( **tStack01.loadGlobals().at< Number >( "var2" ), std::out_of_range );
}

BOOST_AUTO_TEST_SUITE_END();

}
