#include <boost/test/unit_test.hpp>
#include <lua.hpp>
//
#include <luna/typedef.hpp>
#include <luna/auxiliary.hpp>

namespace Luna::Auxiliary::Test
{

BOOST_AUTO_TEST_SUITE( auxiliaryTest );

BOOST_AUTO_TEST_CASE( getTypeNameTest00 )
{
	BOOST_CHECK( getTypeName( NUMBER ) == "number" );
	BOOST_CHECK( getTypeName( INVALID ) == "invalid" );
	BOOST_CHECK( getTypeName( static_cast< Type >( 250 )) == "invalid" );
}

BOOST_AUTO_TEST_CASE( allocateTest00 )
{
	BOOST_CHECK( allocate( nullptr, nullptr, 0, 0 ) == nullptr );
	BOOST_CHECK( allocate( nullptr, nullptr, 16, 0 ) == nullptr );
}

BOOST_AUTO_TEST_CASE( allocateTest01 )
{
	void *ptr00 = nullptr;
	BOOST_REQUIRE_NO_THROW( ptr00 = allocate( nullptr, ptr00, 0, 0 ));
	BOOST_CHECK( ptr00 == nullptr );
}

BOOST_AUTO_TEST_CASE( allocateTest02 )
{
	void *ptr00 = nullptr;
	BOOST_REQUIRE_NO_THROW( ptr00 = allocate( nullptr, ptr00, 0, sizeof( char )));
	BOOST_REQUIRE_NO_THROW( *static_cast< char *>( ptr00 ) = 't' );
	BOOST_CHECK_EQUAL( *static_cast< char *>( ptr00 ), 't' );
	BOOST_CHECK_NO_THROW( ptr00 = allocate( nullptr, ptr00, sizeof( char ), 0 ));
	BOOST_CHECK( ptr00 == nullptr );
}

BOOST_AUTO_TEST_CASE( allocateTest03 )
{
	void *ptr00 = nullptr;
	BOOST_REQUIRE_NO_THROW( ptr00 = allocate( nullptr, ptr00, 0, sizeof( char )));
	BOOST_REQUIRE( ptr00 = allocate( nullptr, ptr00, sizeof( char ), sizeof( long int )));
	BOOST_CHECK( ptr00 != nullptr );
	BOOST_CHECK_NO_THROW( ptr00 = allocate( nullptr, ptr00, sizeof( long int ), 0 ));
}

BOOST_AUTO_TEST_SUITE_END();

}
