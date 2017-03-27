#include <utility>
//
#include <boost/test/unit_test.hpp>
//
#include <luna/exception.hpp>
#include <luna/typedef.hpp>
#include <luna/rawStack.hpp>

namespace Luna
{

class RawStackFixture
{
	Fixture() :
		mState();
		fLuaState( mState );
		fRawStack( dynamic_cast< RawStack & >( mState ));
	{
		
	}
	RawStack &fRawStack;
	LuaState &fLuaState;
private:
	State mState;
}

BOOST_FIXTURE_TEST_SUITE( rawStackTest, RawStackFixture );

BOOST_AUTO_TEST_CASE( loadFileTest00 )
{
	BOOST_REQUIRE_NO_THROW( fRawStack.loadFile( "src/test/rawStackTest.lua" ));
	BOOST_REQUIRE_NO_THROW( fRawStack.call());
	BOOST_REQUIRE_NO_THROW( fRawStack.loadGlobal( "testString" ));
	BOOST_CHECK_EQUAL( fRawStack.toString(), "test" );
	BOOST_CHECK_EQUAL( fRawStack.getSize(), 2 );
}

BOOST_AUTO_TEST_CASE( loadFileTest01 )
{
	BOOST_CHECK_THROW( fRawStack.loadFile( "src/test/nofile.lua" ), Exception::FileError );
	BOOST_CHECK_EQUAL( fRawStack.getSize(), 0 );
}

BOOST_AUTO_TEST_CASE( loadStringTest00 )
{
	BOOST_REQUIRE_NO_THROW( fRawStack.loadString( "var = 'test'" ));
	BOOST_REQUIRE_NO_THROW( fRawStack.call());
	BOOST_REQUIRE_NO_THROW( fRawStack.loadGlobal( "testString" ));
	BOOST_CHECK_EQUAL( fRawStack.toString(), "test" );
	BOOST_CHECK_EQUAL( fRawStack.getSize(), 2 );
}

BOOST_AUTO_TEST_CASE( loadStringTest01 )
{
	BOOST_CHECK_THROW( fRawStack.loadString( "invad code = a{{sdaPSAP" ), Exception::SyntaxError );
	BOOST_CHECK_EQUAL( fRawStack.getSize(), 0 );
}

BOOST_AUTO_TEST_CASE( doFileTest00 )
{
	BOOST_REQUIRE_NO_THROW( fRawStack.doFile( "src/test/rawStackTest.lua" ));
	BOOST_REQUIRE_NO_THROW( fRawStack.loadGlobal( "testString" ));
	BOOST_CHECK_EQUAL( fRawStack.toString(), "test" );
	BOOST_CHECK_EQUAL( fRawStack.getSize(), 2 );
}

BOOST_AUTO_TEST_CASE( doFileTest01 )
{
	BOOST_CHECK_NO_THROW( fRawStack.doFile( "src/test/nofile.lua" ), Exception::FileError );
	BOOST_CHECK_EQUAL( fRawStack.getSize(), 0 );
}

BOOST_AUTO_TEST_CASE( doStringTest00 )
{
	BOOST_REQUIRE_NO_THROW( fRawStack.doString( "var = 'test'" ));
	BOOST_REQUIRE_NO_THROW( fRawStack.loadGlobal( "testString" ));
	BOOST_CHECK_EQUAL( fRawStack.toString(), "test" );
	BOOST_CHECK_EQUAL( fRawStack.getSize(), 2 );
}

BOOST_AUTO_TEST_CASE( doStringTest01 )
{
	BOOST_CHECK_NO_THROW( fRawStack.doString( "sdfasdfwe23r23423{}{{@" ), Exception::SyntaxError );
	BOOST_CHECK_EQUAL( fRawStack.getSize(), 0 );
}

BOOST_AUTO_TEST_CASE( callTest00 )
{
	BOOST_REQUIRE_NO_THROW( fRawStack.loadFile( "src/test/rawStackTest.lua" ));
	BOOST_CHECK_NO_THROW( fRawStack.call( -1 ));
	BOOST_CHECK_EQUAL( fRawStack.getSize(), 1 );
	BOOST_REQUIRE_NO_THROW( fRawStack.loadGlobal( "testFunction" ));
	BOOST_CHECK_NO_THROW( fRawStack.call( -1 ));
	BOOST_CHECK_EQUAL( fRawStack.getSize(), 4 );
	BOOST_CHECK_EQUAL( fRawStack.toString( -2 ), "test1" );
	BOOST_CHECK_EQUAL( fRawStack.toNumber( -1 ), 123 );
}

BOOST_AUTO_TEST_CASE( callTest01 )
{
	BOOST_REQUIRE_NO_THROW( fRawStack.loadString( "var = 'test'" ));
	BOOST_CHECK_THROW( fRawStack.call( -20 ), Exception::IndexError );
	BOOST_CHECK_THROW( fRawStack.call( 0 ), Exception::IndexError );
	BOOST_CHECK_THROW( fRawStack.call( 20 ), Exception::IndexError );
	BOOST_CHECK_EQUAL( fRawStack.getSize(), 1 );
}

BOOST_AUTO_TEST_CASE( callTest02 )
{
	BOOST_REQUIRE_NO_THROW( fRawStack.pushNumber( 23 ));
	BOOST_CHECK_THROW( fRawStack.call( -1 ), Exception::TypeError );
	BOOST_CHECK_EQUAL( fRawStack.getSize(), 1 );
}

BOOST_AUTO_TEST_CASE( pushNilTest00 )
{
	BOOST_REQUIRE_NO_THROW( fRawStack.pushNil());
	BOOST_CHECK( fRawStack.getType() == NIL );
}

BOOST_AUTO_TEST_CASE( pushBooleanTest00 )
{
	BOOST_REQUIRE_NO_THROW( fRawStack.pushBoolean( true ));
	BOOST_REQUIRE( fRawStack.getType() == BOOLEAN );
	BOOST_CHECK_EQUAL( fRawStack.toBoolean(), true );
}

BOOST_AUTO_TEST_CASE( pushNumberTest00 )
{
	BOOST_REQUIRE_NO_THROW( fRawStack.pushNumber( 25 ));
	BOOST_REQUIRE( fRawStack.getType() == NUMBER );
	BOOST_CHECK_EQUAL( fRawStack.toNumber(), 25 );
}

BOOST_AUTO_TEST_CASE( pushStringTest00 )
{
	BOOST_REQUIRE_NO_THROW( fRawStack.pushString( "tet" ));
	BOOST_REQUIRE( fRawStack.getType() == STRING );
	BOOST_CHECK_EQUAL( fRawStack.toString(), "tet" );
}

BOOST_AUTO_TEST_CASE( pushTableTest00 )
{
	BOOST_REQUIRE_NO_THROW( fRawStack.pushTable()); 
	BOOST_REQUIRE( fRawStack.getType() == TABLE );
	BOOST_CHECK_NO_THROW( fRawStack.setRawTableField( -1, "" ), "tet" );
	BOOST_CHECK_EQUAL( fRawStack.getRawTableField( -1, "" ), "tet" );
}

BOOST_AUTO_TEST_CASE( pushLightUserDataTest00 )
{

}

BOOST_AUTO_TEST_CASE( pushUserDataTest00 )
{

}

BOOST_AUTO_TEST_CASE( pushFunctionTest00 )
{

}

BOOST_AUTO_TEST_CASE( pushClosureTest00 )
{

}

BOOST_AUTO_TEST_CASE( pushThreadTest00 )
{

}

BOOST_AUTO_TEST_CASE( pushMetaTableTest00 )
{

}

BOOST_AUTO_TEST_CASE( loadGlobalTest00 )
{
	BOOST_REQUIRE_NO_THROW( fRawStack.doString( "var = 23" ));
	BOOST_REQUIRE_NO_THROW( fRawStack.loadGlobal( "var" ));
	BOOST_CHECK_EQUAL( fRawStack.getSize(), 2 );
	BOOST_CHECK_EQUAL( fRawStack.toNumber(), 23 );
}

BOOST_AUTO_TEST_CASE( loadGlobalTest01 )
{
	BOOST_REQUIRE_NO_THROW( fRawStack.doString( "var = 23" ));
	BOOST_CHECK_THROW( fRawStack.loadGlobal( "varr" ), Exception::StackError );
	BOOST_CHECK_EQUAL( fRawStack.getSize(), 1 );
}

BOOST_AUTO_TEST_CASE( loadGlobalTest02 )
{
	BOOST_CHECK_THROW( fRawStack.loadGlobal( "var" ), Exception::StackError );
	BOOST_CHECK_EQUAL( fRawStack.getSize(), 0 );
}

BOOST_AUTO_TEST_CASE( loadGlobalTableTest00 )
{
	BOOST_REQUIRE_NO_THROW( fRawStack.doString( "var = 25" ));
	BOOST_REQUIRE_NO_THROW( fRawStack.loadGlobalTable());
	BOOST_CHECK_EQUAL( fRawStack.getSize(), 2 );
	BOOST_REQUIRE_NO_THROW( fRawStack.getRawTableField( -1, "var" ));
	BOOST_CHECK_EQUAL( fRawStack.toNumber(), 25 );
}

BOOST_AUTO_TEST_CASE( loadGlobalTableTest00 )
{
	BOOST_CHECK_THROW( fRawStack.loadGlobalTable(), Exception::StackError );
	BOOST_CHECK_EQUAL( fRawStack.getSize(), 1 );
}

BOOST_AUTO_TEST_CASE( newThreadTest00 )
{

}

BOOST_AUTO_TEST_CASE( neweReferenceTest00 )
{

}

BOOST_AUTO_TEST_CASE( dereferenceTest00 )
{

}

BOOST_AUTO_TEST_CASE( registerLibraryTest00 )
{

}

BOOST_AUTO_TEST_CASE( registerFunctionTest00 )
{

}

BOOST_AUTO_TEST_CASE( registerValueTest00 )
{

}

BOOST_AUTO_TEST_CASE( toNumberTest00 )
{

}

BOOST_AUTO_TEST_CASE( toBooleanTest00 )
{

}

BOOST_AUTO_TEST_CASE( toStringTest00 )
{

}

BOOST_AUTO_TEST_CASE( toTableTest00 )
{

}

BOOST_AUTO_TEST_CASE( toUserDataTest00 )
{

}

BOOST_AUTO_TEST_CASE( toFunctionTest00 )
{

}

BOOST_AUTO_TEST_CASE( toThreadTest00 )
{

}

BOOST_AUTO_TEST_CASE( getLengthTest00 )
{

}

BOOST_AUTO_TEST_CASE( getTypeTest00 )
{

}

BOOST_AUTO_TEST_CASE( getTableFieldTest00 )
{

}

BOOST_AUTO_TEST_CASE( getRawTableFieldTest00 )
{

}

BOOST_AUTO_TEST_CASE( getMetaFieldTest00 )
{

}

BOOST_AUTO_TEST_CASE( getMetaTableTest00 )
{

}

BOOST_AUTO_TEST_CASE( setTableFieldTest00 )
{

}

BOOST_AUTO_TEST_CASE( setRawTableFieldTest00 )
{

}

BOOST_AUTO_TEST_CASE( setMetaTableTest00 )
{

}

BOOST_AUTO_TEST_CASE( setUserDataTest00 )
{

}

BOOST_AUTO_TEST_CASE( copyTest00 )
{
	BOOST_REQUIRE_NO_THROW( fRawStack.pushNumber( 64 ));
	BOOST_CHECK_NO_THROW( fRawStack.copy( 1 ));
	BOOST_CHECK_EQUAL( fRawStack.getSize(), 2 );
	BOOST_CHECK_EQUAL( fRawStack.toNumber( -2 ), 64 );
	BOOST_CHECK_EQUAL( fRawStack.toNumber(), 64 );
}

BOOST_AUTO_TEST_CASE( copyTest01 )
{
	BOOST_REQUIRE_NO_THROW( fRawStack.pushNumber( 64 ));
	BOOST_REQUIRE_NO_THROW( fRawStack.pushNumber( 32 ));
	BOOST_REQUIRE_NO_THROW( fRawStack.pushString( "test" ));
	BOOST_REQUIRE_NO_THROW( fRawStack.pushNumber( 12 ));
	BOOST_CHECK_NO_THROW( fRawStack.copy( -2 ));
	BOOST_CHECK_EQUAL( fRawStack.getSize(), 5 );
	BOOST_CHECK_EQUAL( fRawStack.toNumber( -3 ), 32 );
	BOOST_CHECK_EQUAL( fRawStack.toNumber(), 32 );
}

BOOST_AUTO_TEST_CASE( copyTest02 )
{
	BOOST_REQUIRE_NO_THROW( fRawStack.pushNumber( 64 ));
	BOOST_CHECK_THROW( fRawStack.copy( -2 ), Exception::IndexError );
	BOOST_CHECK_THROW( fRawStack.copy( 2 ), Exception::IndexError );
	BOOST_CHECK_EQUAL( fRawStack.getSize(), 1 );
}

BOOST_AUTO_TEST_CASE( copyTest03 )
{
	BOOST_CHECK_THROW( fRawStack.copy( 0 ), Exception::IndexError );
	BOOST_CHECK_THROW( fRawStack.copy( 10 ), Exception::IndexError );
	BOOST_CHECK_THROW( fRawStack.copy( -23 ), Exception::IndexError );
	BOOST_CHECK_EQUAL( fRawStack.getSize(), 0 );
}

BOOST_AUTO_TEST_CASE( insertTest00 )
{
	BOOST_REQUIRE_NO_THROW( fRawStack.pushNumber( 64 ));
	BOOST_REQUIRE_NO_THROW( fRawStack.pushString( "asd" ));
	BOOST_REQUIRE_NO_THROW( fRawStack.pushString( "test" ));
	BOOST_CHECK_NO_THROW( fRawStack.insert( 1 ));
	BOOST_CHECK_EQUAL( fRawStack.getSize(), 3 );
	BOOST_CHECK_EQUAL( fRawStack.toString( -3 ), "test" );
	BOOST_CHECK_EQUAL( fRawStack.toString(), "asd" );
}

BOOST_AUTO_TEST_CASE( insertTest01 )
{
	BOOST_REQUIRE_NO_THROW( fRawStack.pushNumber( 64 ));
	BOOST_CHECK_NO_THROW( fRawStack.insert( -1 ));
	BOOST_CHECK_EQUAL( fRawStack.toNumber(), 64 );
}

BOOST_AUTO_TEST_CASE( insertTest02 )
{
	BOOST_REQUIRE_NO_THROW( fRawStack.pushNumber( 64 ));
	BOOST_REQUIRE_NO_THROW( fRawStack.pushString( 64 ));
	BOOST_CHECK_THROW( fRawStack.insert( -3 ), Exception::IndexError );
	BOOST_CHECK_THROW( fRawStack.insert( 3 ), Exception::IndexError );
	BOOST_CHECK_EQUAL( fRawStack.getSize(), 2 );
}

BOOST_AUTO_TEST_CASE( insertTest03 )
{
	BOOST_CHECK_THROW( fRawStack.insert( 0 ), Exception::IndexError );
	BOOST_CHECK_THROW( fRawStack.insert( 10 ), Exception::IndexError );
	BOOST_CHECK_THROW( fRawStack.insert( -23 ), Exception::IndexError );
	BOOST_CHECK_EQUAL( fRawStack.getSize(), 0 );
}

BOOST_AUTO_TEST_CASE( removeTest00 )
{
	BOOST_REQUIRE_NO_THROW( fRawStack.pushNumber( 64 ));
	BOOST_REQUIRE_NO_THROW( fRawStack.pushString( "asd" ));
	BOOST_REQUIRE_NO_THROW( fRawStack.pushString( "test" ));
	BOOST_CHECK_NO_THROW( fRawStack.remove( 2 ));
	BOOST_CHECK_EQUAL( fRawStack.getSize(), 2 );
	BOOST_CHECK_EQUAL( fRawStack.toString(), "test" );
}

BOOST_AUTO_TEST_CASE( removeTest01 )
{
	BOOST_REQUIRE_NO_THROW( fRawStack.pushNumber( 64 ));
	BOOST_CHECK_NO_THROW( fRawStack.remove( -1 ));
	BOOST_CHECK_EQUAL( fRawStack.getSize(), 0 );
}

BOOST_AUTO_TEST_CASE( removeTest02 )
{
	BOOST_REQUIRE_NO_THROW( fRawStack.pushNumber( 64 ));
	BOOST_REQUIRE_NO_THROW( fRawStack.pushString( "asd" ));
	BOOST_REQUIRE_NO_THROW( fRawStack.pushString( "test" ));
	BOOST_CHECK_THROW( fRawStack.remove( -4 ), Exception::IndexError );
	BOOST_CHECK_THROW( fRawStack.remove( 4 ), Exception::IndexError );
	BOOST_CHECK_EQUAL( fRawStack.getSize(), 3 );
}

BOOST_AUTO_TEST_CASE( removeTest03 )
{
	BOOST_CHECK_THROW( fRawStack.remove( 0 ), Exception::IndexError );
	BOOST_CHECK_THROW( fRawStack.remove( -4 ), Exception::IndexError );
	BOOST_CHECK_THROW( fRawStack.remove( 4 ), Exception::IndexError );
	BOOST_CHECK_EQUAL( fRawStack.getSize(), 0 );
}

BOOST_AUTO_TEST_CASE( eraseTest00 )
{
	BOOST_REQUIRE_NO_THROW( fRawStack.pushNumber( 64 ));
	BOOST_REQUIRE_NO_THROW( fRawStack.pushString( "asd" ));
	BOOST_REQUIRE_NO_THROW( fRawStack.pushString( "test" ));
	BOOST_CHECK_NO_THROW( fRawStack.erase( 2 ));
	BOOST_CHECK_EQUAL( fRawStack.getSize(), 3 );
	BOOST_CHECK( fRawStack.getType( -2 ), NIL );
	BOOST_CHECK_EQUAL( fRawStack.toString(), "test" );
}

BOOST_AUTO_TEST_CASE( eraseTest01 )
{
	BOOST_REQUIRE_NO_THROW( fRawStack.pushNumber( 64 ));
	BOOST_CHECK_NO_THROW( fRawStack.erase( -1 ));
	BOOST_CHECK( fRawStack.getType(), NIL );
	BOOST_CHECK_EQUAL( fRawStack.getSize(), 1 );
}

BOOST_AUTO_TEST_CASE( eraseTest02 )
{
	BOOST_REQUIRE_NO_THROW( fRawStack.pushNumber( 64 ));
	BOOST_REQUIRE_NO_THROW( fRawStack.pushString( "asd" ));
	BOOST_REQUIRE_NO_THROW( fRawStack.pushString( "test" ));
	BOOST_CHECK_THROW( fRawStack.erase( -4 ), Exception::IndexError );
	BOOST_CHECK_THROW( fRawStack.erase( 4 ), Exception::IndexError );
	BOOST_CHECK_EQUAL( fRawStack.getSize(), 3 );
}

BOOST_AUTO_TEST_CASE( eraseTest03 )
{
	BOOST_CHECK_THROW( fRawStack.erase( 0 ), Exception::IndexError );
	BOOST_CHECK_THROW( fRawStack.erase( -4 ), Exception::IndexError );
	BOOST_CHECK_THROW( fRawStack.erase( 4 ), Exception::IndexError );
	BOOST_CHECK_EQUAL( fRawStack.getSize(), 0 );
}

BOOST_AUTO_TEST_CASE( popTest00 )
{
	BOOST_REQUIRE_NO_THROW( fRawStack.pushNumber( 64 ));
	BOOST_REQUIRE_NO_THROW( fRawStack.pushString( "asd" ));
	BOOST_REQUIRE_NO_THROW( fRawStack.pushString( "test" ));
	BOOST_CHECK_NO_THROW( fRawStack.pop( 2 ));
	BOOST_CHECK_EQUAL( fRawStack.getSize(), 1 );
	BOOST_CHECK_EQUAL( fRawStack.toNumber(), 64 );
}

BOOST_AUTO_TEST_CASE( popTest01 )
{
	BOOST_REQUIRE_NO_THROW( fRawStack.pushNumber( 64 ));
	BOOST_CHECK_NO_THROW( fRawStack.pop( 1 ));
	BOOST_CHECK_EQUAL( fRawStack.getSize(), 0 );
}

BOOST_AUTO_TEST_CASE( popTest02 )
{
	BOOST_REQUIRE_NO_THROW( fRawStack.pushNumber( 64 ));
	BOOST_REQUIRE_NO_THROW( fRawStack.pushString( "asd" ));
	BOOST_REQUIRE_NO_THROW( fRawStack.pushString( "test" ));
	BOOST_CHECK_THROW( fRawStack.pop( 4 ), Exception::IndexError );
	BOOST_CHECK_EQUAL( fRawStack.getSize(), 3 );
}

BOOST_AUTO_TEST_CASE( popTest03 )
{
	BOOST_CHECK_THROW( fRawStack.pop( -4 ), Exception::IndexError );
	BOOST_CHECK_THROW( fRawStack.pop( 4 ), Exception::IndexError );
	BOOST_CHECK_EQUAL( fRawStack.getSize(), 0 );
}

BOOST_AUTO_TEST_CASE( popTest04 )
{
	BOOST_CHECK_THROW( fRawStack.pop( 0 ), Exception::IndexError );
}

BOOST_AUTO_TEST_CASE( replaceTest00 )
{
	
}

BOOST_FIXTURE_TEST_SUITE_END();

}
