#include <boost/test/unit_test.hpp>
//
#include <luna/typedef.hpp>
#include <luna/auxiliary.hpp>
#include <luna/rawStack.hpp>
#include <luna/element/element.hpp>

namespace Luna
{

struct F
{
	RawStack tRS;
	F()
	{
		tRS.pushNumber( 32 );
	}
};

struct tElement : public Element
{
	using Element::Element;

	virtual ~tElement() = default;

	virtual Type getType() const noexcept override
	{
		return NIL;
	}
};

BOOST_FIXTURE_TEST_SUITE( elementTest, F );

BOOST_AUTO_TEST_CASE( test )
{
	Element *tElement01;
	BOOST_REQUIRE_NO_THROW( tElement01 = new tElement( tRS, -1 ));
	BOOST_REQUIRE_NO_THROW( delete tElement01 );
	BOOST_CHECK_EQUAL( tRS.getSize(), 1 );
	BOOST_CHECK( tRS.getType( -1 ) == NIL );

	BOOST_REQUIRE_NO_THROW( tRS.pushNumber( 24 ));
	BOOST_REQUIRE_NO_THROW( tRS.pushNumber( 12 ));
	{
		BOOST_REQUIRE_NO_THROW( tElement( tRS, 2 ));
	}
	BOOST_CHECK_EQUAL( tRS.getSize(), 3 );
	BOOST_CHECK( tRS.getType( -2 ) == NIL );
}

BOOST_AUTO_TEST_SUITE_END();

}
