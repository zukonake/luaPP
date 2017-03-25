#include <boost/test/unit_test.hpp>
//
#include <luna/typedef.hpp>
#include <luna/auxiliary.hpp>
#include <luna/rawStack.hpp>
#include <luna/element/element.hpp>

namespace Luna
{

struct tElement : public Element
{
	using Element::Element;

	virtual ~tElement() = default;

	virtual Type getType() const noexcept override
	{
		return NIL;
	}
};

BOOST_AUTO_TEST_SUITE( elementTest );

BOOST_AUTO_TEST_CASE( test )
{
	RawStack tRawStack01;
	BOOST_REQUIRE_NO_THROW( tRawStack01.pushNumber( 25 ));
	Element *tElement01;
	BOOST_REQUIRE_NO_THROW( tElement01 = new tElement( tRawStack01, -1 ));
	BOOST_REQUIRE_NO_THROW( delete tElement01 );
	BOOST_CHECK_EQUAL( tRawStack01.getSize(), 1 );
	BOOST_CHECK( tRawStack01.getType( -1 ) == NIL );

	BOOST_REQUIRE_NO_THROW( tRawStack01.pushNumber( 24 ));
	BOOST_REQUIRE_NO_THROW( tRawStack01.pushNumber( 12 ));
	{
		BOOST_REQUIRE_NO_THROW( tElement( tRawStack01, 2 ));
	}
	BOOST_CHECK_EQUAL( tRawStack01.getSize(), 3 );
	BOOST_CHECK( tRawStack01.getType( -2 ) == NIL );
}

BOOST_AUTO_TEST_SUITE_END();

}
