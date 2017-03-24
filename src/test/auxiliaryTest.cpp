#include <boost/test/unit_test.hpp>
#include <lua.hpp>
//
#include <luna/typedef.hpp>
#include <luna/auxiliary.hpp>

namespace Luna
{

using namespace Auxiliary;

BOOST_AUTO_TEST_SUITE( auxiliaryTest );

BOOST_AUTO_TEST_CASE( getTypeNameTest )
{
	BOOST_CHECK( getTypeName( NUMBER ) == "number" );
	BOOST_CHECK( getTypeName( INVALID ) == "invalid" );
	BOOST_CHECK( getTypeName( static_cast< Type >( 250 )) == "invalid" );
}

BOOST_AUTO_TEST_CASE( allocateTest )
{
	BOOST_CHECK( allocate( nullptr, nullptr, 0, 0 ) == nullptr );
	BOOST_CHECK( allocate( nullptr, nullptr, 16, 0 ) == nullptr );

	void *ptr01 = nullptr;
	BOOST_CHECK_NO_THROW( allocate( nullptr, ptr01, 0, 0 ));
	BOOST_CHECK( ptr01 == nullptr );

	void *ptr02 = nullptr;
	BOOST_REQUIRE_NO_THROW( ptr02 = allocate( nullptr, ptr02, 0, sizeof( char )));
	BOOST_REQUIRE_NO_THROW( *static_cast< char *>( ptr02 ) = 't' );
	BOOST_CHECK_EQUAL( *static_cast< char *>( ptr02 ), 't' );
	BOOST_CHECK_NO_THROW( ptr02 = allocate( nullptr, ptr02, sizeof( char ), 0 ));
	BOOST_CHECK( ptr02 == nullptr );

	void *ptr03 = nullptr;
	BOOST_REQUIRE_NO_THROW( ptr03 = allocate( nullptr, ptr03, 0, sizeof( char )));
	BOOST_REQUIRE( ptr03 = allocate( nullptr, ptr03, sizeof( char ), sizeof( long int )));
	BOOST_CHECK( ptr03 != nullptr );
	BOOST_CHECK_NO_THROW( ptr03 = allocate( nullptr, ptr03, sizeof( long int ), 0 ));
}

BOOST_AUTO_TEST_SUITE_END();

}
