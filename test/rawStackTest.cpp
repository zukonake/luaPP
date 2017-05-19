#include <utility>
//
#include <boost/test/unit_test.hpp>
//
#include <luna/exception.hpp>
#include <luna/typedef.hpp>
#include "rawStackFixture.hpp"

#include <luna/auxiliary.hpp> //TODO
#include <iostream>

namespace Luna::Test
{

BOOST_FIXTURE_TEST_SUITE( rawStackTest, RawStackFixture,
	* boost::unit_test::depends_on( "auxiliaryTest" ));

BOOST_AUTO_TEST_CASE( loadFileTest00 )
{
	BOOST_REQUIRE_NO_THROW( fRawStack.loadFile( "test.lua" ));
	fRawStack.call();
	BOOST_REQUIRE_NO_THROW( fRawStack.getGlobal( "testString" ));
	BOOST_CHECK_EQUAL( fRawStack.toString(), "test" );
	BOOST_CHECK_EQUAL( fRawStack.getSize(), 2 );
}

BOOST_AUTO_TEST_CASE( loadFileTest01 )
{
	BOOST_CHECK_THROW( fRawStack.loadFile( "nofile.lua" ), Exception::FileError );
	BOOST_CHECK_EQUAL( fRawStack.getSize(), 0 );
}

BOOST_AUTO_TEST_CASE( loadFileTest02 )
{
	BOOST_CHECK_THROW( fRawStack.loadFile( "badTest.lua" ), Exception::SyntaxError );
	BOOST_CHECK_EQUAL( fRawStack.getSize(), 0 );
}



BOOST_AUTO_TEST_CASE( loadStringTest00 )
{
	BOOST_REQUIRE_NO_THROW( fRawStack.loadString( "testString = 'test'" ));
	BOOST_REQUIRE_NO_THROW( fRawStack.call());
	BOOST_REQUIRE_NO_THROW( fRawStack.getGlobal( "testString" ));
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
	BOOST_REQUIRE_NO_THROW( fRawStack.doFile( "test.lua" ));
	BOOST_REQUIRE_NO_THROW( fRawStack.getGlobal( "testString" ));
	BOOST_CHECK_EQUAL( fRawStack.toString(), "test" );
	BOOST_CHECK_EQUAL( fRawStack.getSize(), 2 );
}

BOOST_AUTO_TEST_CASE( doFileTest01 )
{
	BOOST_CHECK_THROW( fRawStack.doFile( "nofile.lua" ), Exception::FileError );
	BOOST_CHECK_EQUAL( fRawStack.getSize(), 0 );
}

BOOST_AUTO_TEST_CASE( doFileTest02 )
{
	BOOST_CHECK_THROW( fRawStack.doFile( "badTest.lua" ), Exception::SyntaxError );
	BOOST_CHECK_EQUAL( fRawStack.getSize(), 0 );
}



BOOST_AUTO_TEST_CASE( doStringTest00 )
{
	BOOST_REQUIRE_NO_THROW( fRawStack.doString( "testString = 'test'" ));
	BOOST_REQUIRE_NO_THROW( fRawStack.getGlobal( "testString" ));
	BOOST_CHECK_EQUAL( fRawStack.toString(), "test" );
	BOOST_CHECK_EQUAL( fRawStack.getSize(), 2 );
}

BOOST_AUTO_TEST_CASE( doStringTest01 )
{
	BOOST_CHECK_THROW( fRawStack.doString( "sdfasdfwe23r23423{}{{@" ), Exception::SyntaxError );
	BOOST_CHECK_EQUAL( fRawStack.getSize(), 0 );
}



BOOST_AUTO_TEST_CASE( callTest00 )
{
	BOOST_REQUIRE_NO_THROW( fRawStack.loadFile( "test.lua" ));
	BOOST_CHECK_NO_THROW( fRawStack.call( -1 ));
	BOOST_CHECK_EQUAL( fRawStack.getSize(), 1 );
	BOOST_REQUIRE_NO_THROW( fRawStack.getGlobal( "testFunction" ));
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

BOOST_AUTO_TEST_CASE( callTest03 )
{
	BOOST_REQUIRE_NO_THROW( fRawStack.doFile( "test2.lua" ));
	BOOST_REQUIRE_NO_THROW( fRawStack.getGlobal( "testFunction" ));
	BOOST_REQUIRE_NO_THROW( fRawStack.pushNumber( 20 ));
	BOOST_REQUIRE_NO_THROW( fRawStack.pushNumber( 5 ));
	BOOST_CHECK_NO_THROW( fRawStack.call( -3, 2, 2 ));
	BOOST_CHECK_EQUAL( fRawStack.getSize(), 4 );
	BOOST_CHECK_EQUAL( fRawStack.toString( -1 ), "40" );
	BOOST_CHECK_EQUAL( fRawStack.toNumber( -2 ), 53 );
}

BOOST_AUTO_TEST_CASE( callTest04 )
{
	BOOST_REQUIRE_NO_THROW( fRawStack.doFile( "test2.lua" ));
	BOOST_REQUIRE_NO_THROW( fRawStack.getGlobal( "testFunction" ));
	BOOST_REQUIRE_NO_THROW( fRawStack.pushNumber( 20 ));
	BOOST_REQUIRE_NO_THROW( fRawStack.pushNumber( 5 ));
	BOOST_CHECK_THROW( fRawStack.call( -3, 2, 4 ), Exception::IndexError);
	BOOST_CHECK_EQUAL( fRawStack.getSize(), 4 );
}

BOOST_AUTO_TEST_CASE( callTest05 )
{
	BOOST_REQUIRE_NO_THROW( fRawStack.doFile( "test2.lua" ));
	BOOST_REQUIRE_NO_THROW( fRawStack.getGlobal( "testFunction" ));
	BOOST_CHECK_THROW( fRawStack.call( -1, 3, 0 ), Exception::UnexpectedReturnError );
	BOOST_CHECK_EQUAL( fRawStack.getSize(), 2 );
}

BOOST_AUTO_TEST_CASE( callTest06 )
{
	BOOST_REQUIRE_NO_THROW( fRawStack.doFile( "test2.lua" ));
	BOOST_REQUIRE_NO_THROW( fRawStack.getGlobal( "testFunction" ));
	BOOST_REQUIRE_NO_THROW( fRawStack.pushNumber( 20 ));
	BOOST_REQUIRE_NO_THROW( fRawStack.pushNumber( 5 ));
	BOOST_CHECK_NO_THROW( fRawStack.call( -3, LuaMultiReturn, 2 ));
	BOOST_CHECK_EQUAL( fRawStack.getSize(), 4 );
	BOOST_CHECK_EQUAL( fRawStack.toString( -1 ), "40" );
	BOOST_CHECK_EQUAL( fRawStack.toNumber( -2 ), 53 );
	BOOST_CHECK_NO_THROW( fRawStack.call( -3, LuaMultiReturn, 2 ));
	BOOST_CHECK_EQUAL( fRawStack.getSize(), 2 );
}

BOOST_AUTO_TEST_CASE( callTest07 )
{
	BOOST_REQUIRE_NO_THROW( fRawStack.doFile( "test2.lua" ));
	BOOST_REQUIRE_NO_THROW( fRawStack.getGlobal( "testFunction" ));
	BOOST_REQUIRE_NO_THROW( fRawStack.pushNumber( 20 ));
	BOOST_REQUIRE_NO_THROW( fRawStack.pushNumber( 5 ));
	BOOST_CHECK_THROW( fRawStack.call( -3, 3, 2 ), Exception::UnexpectedReturnError );
	BOOST_CHECK_EQUAL( fRawStack.getSize(), 4 );
}


//TODO check for args
BOOST_AUTO_TEST_CASE( callMetaMethodTest00 )
{
	BOOST_REQUIRE_NO_THROW( fRawStack.doFile( "test.lua" ));
	BOOST_REQUIRE_NO_THROW( fRawStack.getGlobal( "testStuff" ));
	BOOST_CHECK_NO_THROW( fRawStack.callMetaMethod( -1, "toString" ));
	BOOST_CHECK_EQUAL( fRawStack.toString(), "Is this of workingz?" );
	BOOST_CHECK_EQUAL( fRawStack.getSize(), 3 );
}

BOOST_AUTO_TEST_CASE( callMetaMethodTest01 )
{
	BOOST_CHECK_THROW( fRawStack.callMetaMethod( -100, "toString" ), Exception::IndexError );
	BOOST_CHECK_EQUAL( fRawStack.getSize(), 0 );
}

BOOST_AUTO_TEST_CASE( callMetaMethodTest02 )
{
	BOOST_REQUIRE_NO_THROW( fRawStack.doFile( "test.lua" ));
	BOOST_REQUIRE_NO_THROW( fRawStack.getGlobal( "testStuff" ));
	BOOST_CHECK_THROW( fRawStack.callMetaMethod( -1, "nope" ), Exception::StackError );
	BOOST_CHECK_EQUAL( fRawStack.getSize(), 2 );
}



BOOST_AUTO_TEST_CASE( pushNilTest00 )
{
	BOOST_REQUIRE_NO_THROW( fRawStack.pushNil());
	BOOST_CHECK( fRawStack.getType() == NIL );
	BOOST_CHECK_EQUAL( fRawStack.getSize(), 1 );
}



BOOST_AUTO_TEST_CASE( pushBooleanTest00 )
{
	BOOST_REQUIRE_NO_THROW( fRawStack.pushBoolean( true ));
	BOOST_CHECK( fRawStack.getType() == BOOLEAN );
	BOOST_CHECK_EQUAL( fRawStack.toBoolean(), true );
	BOOST_CHECK_EQUAL( fRawStack.getSize(), 1 );
}



BOOST_AUTO_TEST_CASE( pushNumberTest00 )
{
	BOOST_REQUIRE_NO_THROW( fRawStack.pushNumber( 25 ));
	BOOST_CHECK( fRawStack.getType() == NUMBER );
	BOOST_CHECK_EQUAL( fRawStack.toNumber(), 25 );
	BOOST_CHECK_EQUAL( fRawStack.getSize(), 1 );
}



BOOST_AUTO_TEST_CASE( pushStringTest00 )
{
	BOOST_REQUIRE_NO_THROW( fRawStack.pushString( "tet" ));
	BOOST_CHECK( fRawStack.getType() == STRING );
	BOOST_CHECK_EQUAL( fRawStack.toString(), "tet" );
	BOOST_CHECK_EQUAL( fRawStack.getSize(), 1 );
}



BOOST_AUTO_TEST_CASE( pushLightUserDataTest00 )
{
	LightUserDataValue test = new int( 253 );
	BOOST_REQUIRE_NO_THROW( fRawStack.pushLightUserData( test ));
	BOOST_CHECK( fRawStack.getType() == LIGHT_USER_DATA );
	BOOST_CHECK_EQUAL( *static_cast< int * >( fRawStack.toLightUserData()), 253 );
	BOOST_CHECK_EQUAL( fRawStack.getSize(), 1 );
}



BOOST_AUTO_TEST_CASE( pushUserDataTest00 )
{
	//TODO
}



int testFunction( LuaState L )
{
	int a = lua_tonumber( L, -1 );
	lua_pushnumber( L, a * a );
	return 1;
}

BOOST_AUTO_TEST_CASE( pushFunctionTest00 )
{
	BOOST_REQUIRE_NO_THROW( fRawStack.pushFunction( testFunction ));
	BOOST_CHECK( fRawStack.getType() == FUNCTION );
	BOOST_REQUIRE_NO_THROW( fRawStack.pushNumber( 15 ));
	BOOST_CHECK_NO_THROW( fRawStack.call( -1, 1, 1 ));
	BOOST_CHECK_EQUAL( fRawStack.toNumber(), 225 );
	BOOST_CHECK_EQUAL( fRawStack.getSize(), 3 );
}



BOOST_AUTO_TEST_CASE( pushClosureTest00 )
{
	//TODO
}



BOOST_AUTO_TEST_CASE( pushThreadTest00 )
{
	//TODO
}



BOOST_AUTO_TEST_CASE( pushLibraryTest00 )
{
	//TODO
}



BOOST_AUTO_TEST_CASE( pushGlobalTableTest00 )
{
	BOOST_REQUIRE_NO_THROW( fRawStack.pushGlobalTable());
	BOOST_CHECK( fRawStack.getType() == TABLE );
	BOOST_CHECK_EQUAL( fRawStack.getSize(), 1 );
}

BOOST_AUTO_TEST_CASE( pushGlobalTableTest01 )
{
	BOOST_CHECK_NO_THROW( fRawStack.pushGlobalTable());
	BOOST_CHECK( fRawStack.getType() == TABLE );
}



BOOST_AUTO_TEST_CASE( newMetaTableTest00 )
{
	BOOST_CHECK_NO_THROW( fRawStack.newMetaTable( "test" ));
	BOOST_CHECK( fRawStack.getType() == TABLE );
	BOOST_CHECK_EQUAL( fRawStack.getSize(), 1 );
}

BOOST_AUTO_TEST_CASE( newMetaTableTest01 )
{
	BOOST_REQUIRE_NO_THROW( fRawStack.newMetaTable( "test" ));
	BOOST_CHECK_THROW( fRawStack.newMetaTable( "test" ), Exception::ReservedNameError );
	BOOST_CHECK( fRawStack.getType() == TABLE );
	BOOST_CHECK_EQUAL( fRawStack.getSize(), 1 );
} //TODO more tests to check in practice



BOOST_AUTO_TEST_CASE( newTableTest00 )
{
	BOOST_REQUIRE_NO_THROW( fRawStack.newTable()); 
	BOOST_REQUIRE( fRawStack.getType() == TABLE );
	BOOST_REQUIRE_NO_THROW( fRawStack.pushNumber( 23 ));
	BOOST_REQUIRE_NO_THROW( fRawStack.setRawTableField( -2, "asd" ));
	BOOST_REQUIRE_NO_THROW( fRawStack.pop());
	BOOST_REQUIRE_NO_THROW( fRawStack.getRawTableField( -1, "asd" ));
	BOOST_CHECK_EQUAL( fRawStack.toNumber(), 23 );
}

BOOST_AUTO_TEST_CASE( newTableTest01 )
{
	BOOST_REQUIRE_NO_THROW( fRawStack.newTable( 1, 2 )); 
	BOOST_REQUIRE( fRawStack.getType() == TABLE );
	BOOST_REQUIRE_NO_THROW( fRawStack.pushNumber( 23 ));
	BOOST_REQUIRE_NO_THROW( fRawStack.setRawTableField( -2, "asd" ));
	BOOST_REQUIRE_NO_THROW( fRawStack.pop());
	BOOST_REQUIRE_NO_THROW( fRawStack.pushString( "10" ));
	BOOST_REQUIRE_NO_THROW( fRawStack.setRawTableField( -2, "asda" ));
	BOOST_REQUIRE_NO_THROW( fRawStack.pop());
	BOOST_REQUIRE_NO_THROW( fRawStack.pushNumber( 25 ));
	BOOST_REQUIRE_NO_THROW( fRawStack.setRawTableField( -2, "asd" ));
	BOOST_REQUIRE_NO_THROW( fRawStack.pop());
	BOOST_REQUIRE_NO_THROW( fRawStack.pushString( "asdas" ));
	BOOST_REQUIRE_NO_THROW( fRawStack.setRawTableField( -2, 1 ));
	BOOST_REQUIRE_NO_THROW( fRawStack.pop());
	BOOST_REQUIRE_NO_THROW( fRawStack.getRawTableField( -1, "asd" ));
	BOOST_CHECK_EQUAL( fRawStack.toNumber(), 23 );
	BOOST_REQUIRE_NO_THROW( fRawStack.getRawTableField( -1, "asda" ));
	BOOST_CHECK_EQUAL( fRawStack.toString(), "10" );
	BOOST_REQUIRE_NO_THROW( fRawStack.getRawTableField( -1, 1 ));
	BOOST_CHECK_EQUAL( fRawStack.toString(), "asdas" );
}



BOOST_AUTO_TEST_CASE( newUserDataTest00 )
{
	//TODO
}



BOOST_AUTO_TEST_CASE( newThreadTest00 )
{
	//TODO
}



BOOST_AUTO_TEST_CASE( newReferenceTest00 )
{
	BOOST_REQUIRE_NO_THROW( fRawStack.pushNumber( 23 ));
	LuaReference tReference00;
	BOOST_REQUIRE_NO_THROW( tReference00 = fRawStack.newReference( -1 ));
	BOOST_CHECK_EQUAL( fRawStack.getSize(), 0 );
	BOOST_REQUIRE_NO_THROW( fRawStack.getRawTableField( LuaRegistryIndex, tReference00 ));
	BOOST_CHECK_EQUAL( fRawStack.toNumber(), 23 );
}

BOOST_AUTO_TEST_CASE( newReferenceTest01 )
{
	BOOST_REQUIRE_NO_THROW( fRawStack.newTable());
	BOOST_REQUIRE_NO_THROW( fRawStack.pushNumber( 25 ));
	BOOST_REQUIRE_NO_THROW( fRawStack.pushString( "asdasda" ));
	LuaReference tReference00;
	BOOST_REQUIRE_NO_THROW( tReference00 = fRawStack.newReference( -1, -3 ));
	LuaReference tReference01;
	BOOST_REQUIRE_NO_THROW( tReference01 = fRawStack.newReference( -1, -2 ));
	BOOST_CHECK_EQUAL( fRawStack.getSize(), 1 );
	BOOST_REQUIRE_NO_THROW( fRawStack.getRawTableField( -1, tReference00 ));
	BOOST_CHECK_EQUAL( fRawStack.toNumber(), 25 );
	BOOST_REQUIRE_NO_THROW( fRawStack.pop());
	BOOST_REQUIRE_NO_THROW( fRawStack.getRawTableField( -1, tReference01 ));
	BOOST_CHECK_EQUAL( fRawStack.toString(), "asdasda" );
}

BOOST_AUTO_TEST_CASE( newReferenceTest02 )
{
	BOOST_CHECK_THROW( fRawStack.newReference( -1 ), Exception::IndexError );
	BOOST_CHECK_EQUAL( fRawStack.getSize(), 0 );
}

BOOST_AUTO_TEST_CASE( newReferenceTest03 )
{
	BOOST_REQUIRE_NO_THROW( fRawStack.pushNumber( 25 ));
	BOOST_CHECK_THROW( fRawStack.newReference( -1, -2 ), Exception::IndexError );
	BOOST_CHECK_EQUAL( fRawStack.getSize(), 1 );
}

BOOST_AUTO_TEST_CASE( newReferenceTest04 )
{
	BOOST_REQUIRE_NO_THROW( fRawStack.pushNumber( 25 ));
	BOOST_REQUIRE_NO_THROW( fRawStack.pushNumber( 25 ));
	BOOST_CHECK_THROW( fRawStack.newReference( -1, -2 ), Exception::TypeError );
	BOOST_CHECK_EQUAL( fRawStack.getSize(), 2 );
}

BOOST_AUTO_TEST_CASE( newReferenceTest05 )
{
	BOOST_REQUIRE_NO_THROW( fRawStack.newTable());
	BOOST_REQUIRE_NO_THROW( fRawStack.pushNumber( 25 ));
	LuaReference tReference00;
	BOOST_REQUIRE_NO_THROW( tReference00 = fRawStack.newReference( -1, -2 ));
	BOOST_CHECK_EQUAL( fRawStack.getSize(), 1 );
	BOOST_REQUIRE_NO_THROW( fRawStack.getRawTableField( LuaRegistryIndex, tReference00 ));
	BOOST_CHECK( fRawStack.getType() == NIL );
	BOOST_CHECK_EQUAL( fRawStack.getSize(), 2 );
}



BOOST_AUTO_TEST_CASE( dereferenceTest00 )
{
	BOOST_REQUIRE_NO_THROW( fRawStack.pushNumber( 23 ));
	LuaReference tReference00;
	BOOST_REQUIRE_NO_THROW( tReference00 = fRawStack.newReference( -1 ));
	BOOST_CHECK_EQUAL( fRawStack.getSize(), 0 );
	BOOST_REQUIRE_NO_THROW( fRawStack.dereference( tReference00 ));
	BOOST_CHECK_EQUAL( fRawStack.toNumber(), 23 );
	BOOST_REQUIRE_NO_THROW( fRawStack.getRawTableField( LuaRegistryIndex, tReference00 ));
	BOOST_CHECK( fRawStack.getType() == NIL );
}

BOOST_AUTO_TEST_CASE( dereferenceTest01 )
{
	BOOST_REQUIRE_NO_THROW( fRawStack.newTable());
	BOOST_REQUIRE_NO_THROW( fRawStack.pushString( "asdasda" ));
	LuaReference tReference00;
	BOOST_REQUIRE_NO_THROW( tReference00 = fRawStack.newReference( -1, -2 ));
	BOOST_CHECK_EQUAL( fRawStack.getSize(), 1 );
	BOOST_REQUIRE_NO_THROW( fRawStack.dereference( tReference00, -1 ));
	BOOST_CHECK_EQUAL( fRawStack.toString(), "asdasda" );
	BOOST_REQUIRE_NO_THROW( fRawStack.getRawTableField( -2, tReference00 ));
	BOOST_CHECK( fRawStack.getType() == NIL );
}

BOOST_AUTO_TEST_CASE( dereferenceTest02 )
{
	BOOST_CHECK_NO_THROW( fRawStack.dereference( 123123 ));
	BOOST_CHECK( fRawStack.getType() == NIL );
}

BOOST_AUTO_TEST_CASE( dereferenceTest03 )
{
	BOOST_CHECK_THROW( fRawStack.dereference( 123123, -2 ), Exception::IndexError );
	BOOST_CHECK_EQUAL( fRawStack.getSize(), 0 );
}



BOOST_AUTO_TEST_CASE( registerValueTest00 )
{
	BOOST_REQUIRE_NO_THROW( fRawStack.pushString( "testoh" ));
	BOOST_REQUIRE_NO_THROW( fRawStack.registerValue( -1, "testVar" ));
	BOOST_CHECK_EQUAL( fRawStack.getSize(), 1 );
	BOOST_REQUIRE_NO_THROW( fRawStack.getGlobal( "testVar" ));
	BOOST_CHECK_EQUAL( fRawStack.toString(), "testoh" );
	BOOST_REQUIRE_NO_THROW( fRawStack.registerValue( -1, "testVar" ));
	BOOST_REQUIRE_NO_THROW( fRawStack.getGlobal( "testVar" ));
	BOOST_CHECK_EQUAL( fRawStack.toString(), "testoh" );
}

BOOST_AUTO_TEST_CASE( registerValueTest01 )
{
	BOOST_CHECK_THROW( fRawStack.registerValue( -1, "noVar" ), Exception::IndexError );
	BOOST_CHECK_EQUAL( fRawStack.getSize(), 0 );
	BOOST_CHECK_NO_THROW( fRawStack.getGlobal( "noVar" ));
	BOOST_CHECK( fRawStack.getType() == NIL );
}



BOOST_AUTO_TEST_CASE( toNumberTest00 )
{
	BOOST_REQUIRE_NO_THROW( fRawStack.pushNumber( 25 ));
	BOOST_CHECK_EQUAL( fRawStack.toNumber(), 25 );
	BOOST_CHECK( fRawStack.getType() == NUMBER );
	BOOST_CHECK_EQUAL( fRawStack.getSize(), 1 );
}

BOOST_AUTO_TEST_CASE( toNumberTest01 )
{
	BOOST_REQUIRE_NO_THROW( fRawStack.pushString( "asd" ));
	BOOST_CHECK_THROW( fRawStack.toNumber(), Exception::TypeError );
	BOOST_CHECK_EQUAL( fRawStack.getSize(), 1 );
}

BOOST_AUTO_TEST_CASE( toNumberTest02 )
{
	BOOST_CHECK_THROW( fRawStack.toNumber(), Exception::IndexError );
	BOOST_CHECK_EQUAL( fRawStack.getSize(), 0 );
}



BOOST_AUTO_TEST_CASE( toBooleanTest00 )
{
	BOOST_REQUIRE_NO_THROW( fRawStack.pushBoolean( true ));
	BOOST_CHECK_EQUAL( fRawStack.toBoolean(), true );
	BOOST_CHECK( fRawStack.getType() == BOOLEAN);
	BOOST_CHECK_EQUAL( fRawStack.getSize(), 1 );
}

BOOST_AUTO_TEST_CASE( toBooleanTest01 )
{
	BOOST_REQUIRE_NO_THROW( fRawStack.pushString( "asd" ));
	BOOST_CHECK_THROW( fRawStack.toBoolean(), Exception::TypeError );
	BOOST_CHECK_EQUAL( fRawStack.getSize(), 1 );
}

BOOST_AUTO_TEST_CASE( toBooleanTest02 )
{
	BOOST_CHECK_THROW( fRawStack.toBoolean(), Exception::IndexError );
	BOOST_CHECK_EQUAL( fRawStack.getSize(), 0 );
}



BOOST_AUTO_TEST_CASE( toStringTest00 )
{
	BOOST_REQUIRE_NO_THROW( fRawStack.pushString( "Asd" ));
	BOOST_CHECK_EQUAL( fRawStack.toString(), "Asd" );
	BOOST_CHECK( fRawStack.getType() == STRING );
	BOOST_CHECK_EQUAL( fRawStack.getSize(), 1 );
}

BOOST_AUTO_TEST_CASE( toStringTest01 )
{
	BOOST_REQUIRE_NO_THROW( fRawStack.pushNumber( 32 ));
	BOOST_CHECK_THROW( fRawStack.toString(), Exception::TypeError );
	BOOST_CHECK_EQUAL( fRawStack.getSize(), 1 );
}

BOOST_AUTO_TEST_CASE( toStringTest02 )
{
	BOOST_CHECK_THROW( fRawStack.toString(), Exception::IndexError );
	BOOST_CHECK_EQUAL( fRawStack.getSize(), 0 );
}



BOOST_AUTO_TEST_CASE( toTableTest00 )
{
	//TODO
}

BOOST_AUTO_TEST_CASE( toTableTest01 )
{
	BOOST_REQUIRE_NO_THROW( fRawStack.pushString( "asd" ));
	BOOST_CHECK_THROW( fRawStack.toTable(), Exception::TypeError );
	BOOST_CHECK_EQUAL( fRawStack.getSize(), 1 );
}

BOOST_AUTO_TEST_CASE( toTableTest02 )
{
	BOOST_CHECK_THROW( fRawStack.toTable(), Exception::IndexError );
	BOOST_CHECK_EQUAL( fRawStack.getSize(), 0 );
}



BOOST_AUTO_TEST_CASE( toLightUserDataTest00 )
{
	BOOST_REQUIRE_NO_THROW( fRawStack.pushLightUserData( new int( 35 )));
	BOOST_CHECK_EQUAL( *static_cast< int * >( fRawStack.toLightUserData()), 35 );
	BOOST_CHECK_EQUAL( fRawStack.getSize(), 1 );
	BOOST_CHECK_NO_THROW( delete static_cast< int * >( fRawStack.toLightUserData()));
}

BOOST_AUTO_TEST_CASE( toLightUserDataTest01 )
{
	BOOST_REQUIRE_NO_THROW( fRawStack.pushString( "asd" ));
	BOOST_CHECK_THROW( fRawStack.toLightUserData(), Exception::TypeError );
	BOOST_CHECK_EQUAL( fRawStack.getSize(), 1 );
}

BOOST_AUTO_TEST_CASE( toLightUserDataTest02 )
{
	BOOST_CHECK_THROW( fRawStack.toLightUserData(), Exception::IndexError );
	BOOST_CHECK_EQUAL( fRawStack.getSize(), 0 );
}



BOOST_AUTO_TEST_CASE( toUserDataTest00 )
{
	BOOST_REQUIRE_NO_THROW( fRawStack.newUserData( sizeof( int )));
	BOOST_CHECK_NO_THROW( *static_cast< int * >( fRawStack.toUserData()) = 96 );
	BOOST_CHECK_EQUAL( fRawStack.getSize(), 1 );
	BOOST_CHECK_EQUAL( *static_cast< int * >( fRawStack.toUserData()), 96 );
	BOOST_CHECK_NO_THROW( delete static_cast< int * >( fRawStack.toUserData()));
	BOOST_CHECK_EQUAL( fRawStack.getSize(), 1 );
}

BOOST_AUTO_TEST_CASE( toUserDataTest01 )
{
	BOOST_REQUIRE_NO_THROW( fRawStack.pushString( "asd" ));
	BOOST_CHECK_THROW( fRawStack.toUserData(), Exception::TypeError );
	BOOST_CHECK_EQUAL( fRawStack.getSize(), 1 );
}

BOOST_AUTO_TEST_CASE( toUserDataTest02 )
{
	BOOST_CHECK_THROW( fRawStack.toUserData(), Exception::IndexError );
	BOOST_CHECK_EQUAL( fRawStack.getSize(), 0 );
}



BOOST_AUTO_TEST_CASE( toFunctionTest00 )
{
	BOOST_REQUIRE_NO_THROW( fRawStack.pushFunction( testFunction ));
	BOOST_CHECK_EQUAL( (fRawStack.toFunction())( fRawStack.getLuaState()), 1 );
	BOOST_CHECK_EQUAL( fRawStack.getSize(), 1 );
}

BOOST_AUTO_TEST_CASE( toFunctionTest01 )
{
	BOOST_REQUIRE_NO_THROW( fRawStack.pushString( "asd" ));
	BOOST_CHECK_THROW( fRawStack.toFunction(), Exception::TypeError );
	BOOST_CHECK_EQUAL( fRawStack.getSize(), 1 );
}

BOOST_AUTO_TEST_CASE( toFunctionTest02 )
{
	BOOST_CHECK_THROW( fRawStack.toFunction(), Exception::IndexError );
	BOOST_CHECK_EQUAL( fRawStack.getSize(), 0 );
}



BOOST_AUTO_TEST_CASE( toThreadTest00 )
{
	BOOST_REQUIRE_NO_THROW( fRawStack.newThread());
	BOOST_CHECK_NO_THROW( fRawStack.toThread()); //TODO test if the thread actually works fine
	BOOST_CHECK_EQUAL( fRawStack.getSize(), 1 );
}

BOOST_AUTO_TEST_CASE( toThreadTest01 )
{
	BOOST_REQUIRE_NO_THROW( fRawStack.pushString( "asd" ));
	BOOST_CHECK_THROW( fRawStack.toThread(), Exception::TypeError );
	BOOST_CHECK_EQUAL( fRawStack.getSize(), 1 );
}

BOOST_AUTO_TEST_CASE( toThreadTest02 )
{
	BOOST_CHECK_THROW( fRawStack.toThread(), Exception::IndexError );
	BOOST_CHECK_EQUAL( fRawStack.getSize(), 0 );
}



BOOST_AUTO_TEST_CASE( getLengthTest00 )
{
	BOOST_REQUIRE_NO_THROW( fRawStack.newTable( 1, 2 )); 
	BOOST_REQUIRE_NO_THROW( fRawStack.pushNumber( 23 ));
	BOOST_REQUIRE_NO_THROW( fRawStack.setRawTableField( -2, "asd" ));
	BOOST_REQUIRE_NO_THROW( fRawStack.pop());
	BOOST_REQUIRE_NO_THROW( fRawStack.pushString( "10" ));
	BOOST_REQUIRE_NO_THROW( fRawStack.setRawTableField( -2, "asda" ));
	BOOST_REQUIRE_NO_THROW( fRawStack.pop());
	BOOST_REQUIRE_NO_THROW( fRawStack.pushString( "asdas" ));
	BOOST_REQUIRE_NO_THROW( fRawStack.setRawTableField( -2, 1 ));
	BOOST_REQUIRE_NO_THROW( fRawStack.pop());
	BOOST_CHECK_EQUAL( fRawStack.getLength(), 3 );
	BOOST_CHECK_EQUAL( fRawStack.getSize(), 1 );
}

BOOST_AUTO_TEST_CASE( getLengthTest01 )
{
	BOOST_REQUIRE_NO_THROW( fRawStack.pushString( "xd_asd l" ));
	BOOST_CHECK_EQUAL( fRawStack.getLength(), 8 );
}

BOOST_AUTO_TEST_CASE( getLengthTest02 )
{
	BOOST_CHECK_THROW( fRawStack.getLength(), Exception::IndexError );
}



BOOST_AUTO_TEST_CASE( getTypeTest00 )
{
	BOOST_REQUIRE_NO_THROW( fRawStack.pushString( "asd" ));
	BOOST_CHECK( fRawStack.getType() == STRING );
}

BOOST_AUTO_TEST_CASE( getTypeTest01 )
{
	BOOST_CHECK_THROW( fRawStack.getType(), Exception::IndexError );
}

BOOST_AUTO_TEST_CASE( getTypeTest02 )
{
	BOOST_REQUIRE_NO_THROW( fRawStack.pushString( "asd" ));
	BOOST_REQUIRE_NO_THROW( fRawStack.pushNumber( 25 ));
	BOOST_CHECK( fRawStack.getType( -1 ) == NUMBER );
	BOOST_CHECK( fRawStack.getType( -2 ) == STRING );
}



BOOST_AUTO_TEST_CASE( getTableFieldTest00 )
{
	BOOST_REQUIRE_NO_THROW( fRawStack.newTable( 1, 2 )); 
	BOOST_REQUIRE_NO_THROW( fRawStack.pushNumber( 23 ));
	BOOST_REQUIRE_NO_THROW( fRawStack.setRawTableField( -2, "asd" ));
	BOOST_REQUIRE_NO_THROW( fRawStack.pop());
	BOOST_REQUIRE_NO_THROW( fRawStack.pushString( "10" ));
	BOOST_REQUIRE_NO_THROW( fRawStack.setRawTableField( -2, "asda" ));
	BOOST_REQUIRE_NO_THROW( fRawStack.pop());
	BOOST_REQUIRE_NO_THROW( fRawStack.pushString( "asdas" ));
	BOOST_REQUIRE_NO_THROW( fRawStack.setRawTableField( -2, 1 ));
	BOOST_REQUIRE_NO_THROW( fRawStack.pop());
	BOOST_REQUIRE_NO_THROW( fRawStack.pushString( "asda" ));
	BOOST_CHECK_NO_THROW( fRawStack.getTableField( -2 ));
	BOOST_CHECK_EQUAL( fRawStack.toString(), "10" );
	BOOST_CHECK_EQUAL( fRawStack.getSize(), 2 );
}

BOOST_AUTO_TEST_CASE( getTableFieldTest01 )
{
	BOOST_CHECK_THROW( fRawStack.getTableField( -1 ), Exception::IndexError );
}

BOOST_AUTO_TEST_CASE( getTableFieldTest02 )
{
	BOOST_REQUIRE_NO_THROW( fRawStack.pushNil());
	BOOST_CHECK_THROW( fRawStack.getTableField( -1 ), Exception::TypeError );
}

BOOST_AUTO_TEST_CASE( getTableFieldTest03 )
{
	BOOST_REQUIRE_NO_THROW( fRawStack.newTable( 0, 0 ));
	BOOST_REQUIRE_NO_THROW( fRawStack.pushNil());
	BOOST_CHECK_THROW( fRawStack.getTableField( -2 ), Exception::TypeError );
}

BOOST_AUTO_TEST_CASE( getTableFieldTest04 )
{
	BOOST_REQUIRE_NO_THROW( fRawStack.newTable( 0, 0 ));
	BOOST_REQUIRE_NO_THROW( fRawStack.pushNumber( 1 ));
	BOOST_CHECK_THROW( fRawStack.getTableField( -2 ), Exception::KeyError );
}

BOOST_AUTO_TEST_CASE( getTableFieldTest05 )
{
	BOOST_REQUIRE_NO_THROW( fRawStack.newTable( 1, 2 )); 
	BOOST_REQUIRE_NO_THROW( fRawStack.pushNumber( 23 ));
	BOOST_REQUIRE_NO_THROW( fRawStack.setRawTableField( -2, "asd" ));
	BOOST_REQUIRE_NO_THROW( fRawStack.pop());
	BOOST_REQUIRE_NO_THROW( fRawStack.pushString( "10" ));
	BOOST_REQUIRE_NO_THROW( fRawStack.setRawTableField( -2, "asda" ));
	BOOST_REQUIRE_NO_THROW( fRawStack.pop());
	BOOST_REQUIRE_NO_THROW( fRawStack.pushString( "asdas" ));
	BOOST_REQUIRE_NO_THROW( fRawStack.setRawTableField( -2, 1 ));
	BOOST_REQUIRE_NO_THROW( fRawStack.pop());
	BOOST_CHECK_NO_THROW( fRawStack.getTableField( -1, 1 ));
	BOOST_CHECK_EQUAL( fRawStack.toNumber(), 23 );
	BOOST_CHECK_EQUAL( fRawStack.getSize(), 2 );
}

BOOST_AUTO_TEST_CASE( getTableFieldTest06 )
{
	BOOST_CHECK_THROW( fRawStack.getTableField( -1, 1 ), Exception::IndexError );
}

BOOST_AUTO_TEST_CASE( getTableFieldTest07 )
{
	BOOST_REQUIRE_NO_THROW( fRawStack.pushNil());
	BOOST_CHECK_THROW( fRawStack.getTableField( -1, 1 ), Exception::TypeError );
}

BOOST_AUTO_TEST_CASE( getTableFieldTest08 )
{
	BOOST_REQUIRE_NO_THROW( fRawStack.newTable( 0, 0 ));
	BOOST_CHECK_THROW( fRawStack.getTableField( -1, 1 ), Exception::KeyError );
}

BOOST_AUTO_TEST_CASE( getTableFieldTest09 )
{
	BOOST_REQUIRE_NO_THROW( fRawStack.newTable( 1, 2 )); 
	BOOST_REQUIRE_NO_THROW( fRawStack.pushNumber( 23 ));
	BOOST_REQUIRE_NO_THROW( fRawStack.setRawTableField( -2, "asd" ));
	BOOST_REQUIRE_NO_THROW( fRawStack.pop());
	BOOST_REQUIRE_NO_THROW( fRawStack.pushString( "10" ));
	BOOST_REQUIRE_NO_THROW( fRawStack.setRawTableField( -2, "asda" ));
	BOOST_REQUIRE_NO_THROW( fRawStack.pop());
	BOOST_REQUIRE_NO_THROW( fRawStack.pushString( "asdas" ));
	BOOST_REQUIRE_NO_THROW( fRawStack.setRawTableField( -2, 1 ));
	BOOST_REQUIRE_NO_THROW( fRawStack.pop());
	BOOST_CHECK_NO_THROW( fRawStack.getTableField( -1, "asda" ));
	BOOST_CHECK_EQUAL( fRawStack.toString(), "10" );
	BOOST_CHECK_EQUAL( fRawStack.getSize(), 2 );
}

BOOST_AUTO_TEST_CASE( getTableFieldTest10 )
{
	BOOST_CHECK_THROW( fRawStack.getTableField( -1, "a" ), Exception::IndexError );
}

BOOST_AUTO_TEST_CASE( getTableFieldTest11 )
{
	BOOST_REQUIRE_NO_THROW( fRawStack.pushNil());
	BOOST_CHECK_THROW( fRawStack.getTableField( -1, "a" ), Exception::TypeError );
}

BOOST_AUTO_TEST_CASE( getTableFieldTest12 )
{
	BOOST_REQUIRE_NO_THROW( fRawStack.newTable( 0, 0 ));
	BOOST_CHECK_THROW( fRawStack.getTableField( -1, "a" ), Exception::KeyError );
}
//TODO check for meta methods



BOOST_AUTO_TEST_CASE( getRawTableFieldTest00 )
{
	BOOST_REQUIRE_NO_THROW( fRawStack.newTable( 1, 2 )); 
	BOOST_REQUIRE_NO_THROW( fRawStack.pushNumber( 23 ));
	BOOST_REQUIRE_NO_THROW( fRawStack.setRawTableField( -2, "asd" ));
	BOOST_REQUIRE_NO_THROW( fRawStack.pop());
	BOOST_REQUIRE_NO_THROW( fRawStack.pushString( "10" ));
	BOOST_REQUIRE_NO_THROW( fRawStack.setRawTableField( -2, "asda" ));
	BOOST_REQUIRE_NO_THROW( fRawStack.pop());
	BOOST_REQUIRE_NO_THROW( fRawStack.pushString( "asdas" ));
	BOOST_REQUIRE_NO_THROW( fRawStack.setRawTableField( -2, 1 ));
	BOOST_REQUIRE_NO_THROW( fRawStack.pop());
	BOOST_REQUIRE_NO_THROW( fRawStack.pushString( "asda" ));
	BOOST_CHECK_NO_THROW( fRawStack.getRawTableField( -2 ));
	BOOST_CHECK_EQUAL( fRawStack.toString(), "10" );
	BOOST_CHECK_EQUAL( fRawStack.getSize(), 2 );
}

BOOST_AUTO_TEST_CASE( getRawTableFieldTest01 )
{
	BOOST_CHECK_THROW( fRawStack.getRawTableField( -1 ), Exception::IndexError );
}

BOOST_AUTO_TEST_CASE( getRawTableFieldTest02 )
{
	BOOST_REQUIRE_NO_THROW( fRawStack.pushNil());
	BOOST_CHECK_THROW( fRawStack.getRawTableField( -1 ), Exception::TypeError );
}

BOOST_AUTO_TEST_CASE( getRawTableFieldTest03 )
{
	BOOST_REQUIRE_NO_THROW( fRawStack.newTable( 0, 0 ));
	BOOST_REQUIRE_NO_THROW( fRawStack.pushNil());
	BOOST_CHECK_THROW( fRawStack.getRawTableField( -2 ), Exception::TypeError );
}

BOOST_AUTO_TEST_CASE( getRawTableFieldTest04 )
{
	BOOST_REQUIRE_NO_THROW( fRawStack.newTable( 0, 0 ));
	BOOST_REQUIRE_NO_THROW( fRawStack.pushNumber( 1 ));
	BOOST_CHECK_THROW( fRawStack.getRawTableField( -2 ), Exception::KeyError );
}

BOOST_AUTO_TEST_CASE( getRawTableFieldTest05 )
{
	BOOST_REQUIRE_NO_THROW( fRawStack.newTable( 1, 2 )); 
	BOOST_REQUIRE_NO_THROW( fRawStack.pushNumber( 23 ));
	BOOST_REQUIRE_NO_THROW( fRawStack.setRawTableField( -2, "asd" ));
	BOOST_REQUIRE_NO_THROW( fRawStack.pop());
	BOOST_REQUIRE_NO_THROW( fRawStack.pushString( "10" ));
	BOOST_REQUIRE_NO_THROW( fRawStack.setRawTableField( -2, "asda" ));
	BOOST_REQUIRE_NO_THROW( fRawStack.pop());
	BOOST_REQUIRE_NO_THROW( fRawStack.pushString( "asdas" ));
	BOOST_REQUIRE_NO_THROW( fRawStack.setRawTableField( -2, 1 ));
	BOOST_REQUIRE_NO_THROW( fRawStack.pop());
	BOOST_CHECK_NO_THROW( fRawStack.getRawTableField( -1, 1 ));
	BOOST_CHECK_EQUAL( fRawStack.toNumber(), 23 );
	BOOST_CHECK_EQUAL( fRawStack.getSize(), 2 );
}

BOOST_AUTO_TEST_CASE( getRawTableFieldTest06 )
{
	BOOST_CHECK_THROW( fRawStack.getRawTableField( -1, 1 ), Exception::IndexError );
}

BOOST_AUTO_TEST_CASE( getRawTableFieldTest07 )
{
	BOOST_REQUIRE_NO_THROW( fRawStack.pushNil());
	BOOST_CHECK_THROW( fRawStack.getRawTableField( -1, 1 ), Exception::TypeError );
}

BOOST_AUTO_TEST_CASE( getRawTableFieldTest08 )
{
	BOOST_REQUIRE_NO_THROW( fRawStack.newTable( 0, 0 ));
	BOOST_CHECK_THROW( fRawStack.getRawTableField( -1, 1 ), Exception::KeyError );
}

BOOST_AUTO_TEST_CASE( getRawTableFieldTest09 )
{
	BOOST_REQUIRE_NO_THROW( fRawStack.newTable( 1, 2 )); 
	BOOST_REQUIRE_NO_THROW( fRawStack.pushNumber( 23 ));
	BOOST_REQUIRE_NO_THROW( fRawStack.setRawTableField( -2, "asd" ));
	BOOST_REQUIRE_NO_THROW( fRawStack.pop());
	BOOST_REQUIRE_NO_THROW( fRawStack.pushString( "10" ));
	BOOST_REQUIRE_NO_THROW( fRawStack.setRawTableField( -2, "asda" ));
	BOOST_REQUIRE_NO_THROW( fRawStack.pop());
	BOOST_REQUIRE_NO_THROW( fRawStack.pushString( "asdas" ));
	BOOST_REQUIRE_NO_THROW( fRawStack.setRawTableField( -2, 1 ));
	BOOST_REQUIRE_NO_THROW( fRawStack.pop());
	BOOST_CHECK_NO_THROW( fRawStack.getRawTableField( -1, "asda" ));
	BOOST_CHECK_EQUAL( fRawStack.toString(), "10" );
	BOOST_CHECK_EQUAL( fRawStack.getSize(), 2 );
}

BOOST_AUTO_TEST_CASE( getRawTableFieldTest10 )
{
	BOOST_CHECK_THROW( fRawStack.getRawTableField( -1, "a" ), Exception::IndexError );
}

BOOST_AUTO_TEST_CASE( getRawTableFieldTest11 )
{
	BOOST_REQUIRE_NO_THROW( fRawStack.pushNil());
	BOOST_CHECK_THROW( fRawStack.getRawTableField( -1, "a" ), Exception::TypeError );
}

BOOST_AUTO_TEST_CASE( getRawTableFieldTest12 )
{
	BOOST_REQUIRE_NO_THROW( fRawStack.newTable( 0, 0 ));
	BOOST_CHECK_THROW( fRawStack.getRawTableField( -1, "a" ), Exception::KeyError );
}
//TODO check for meta methods



BOOST_AUTO_TEST_CASE( getMetaFieldTest00 )
{

}



BOOST_AUTO_TEST_CASE( getMetaTableTest00 )
{

}



BOOST_AUTO_TEST_CASE( getGlobalTest00 )
{
	BOOST_REQUIRE_NO_THROW( fRawStack.doString( "var = 23" ));
	BOOST_REQUIRE_NO_THROW( fRawStack.getGlobal( "var" ));
	BOOST_CHECK_EQUAL( fRawStack.getSize(), 2 );
	BOOST_CHECK_EQUAL( fRawStack.toNumber(), 23 );
}

BOOST_AUTO_TEST_CASE( getGlobalTest01 )
{
	BOOST_REQUIRE_NO_THROW( fRawStack.doString( "var = 23" ));
	BOOST_REQUIRE_NO_THROW( fRawStack.getGlobal( "varr" ));
	BOOST_CHECK( fRawStack.getType() == NIL );
	BOOST_CHECK_EQUAL( fRawStack.getSize(), 2 );
}

BOOST_AUTO_TEST_CASE( getGlobalTest02 )
{
	BOOST_REQUIRE_NO_THROW( fRawStack.getGlobal( "var" ));
	BOOST_CHECK( fRawStack.getType() == NIL );
	BOOST_CHECK_EQUAL( fRawStack.getSize(), 1 );
}



BOOST_AUTO_TEST_CASE( setTableFieldTest00 )
{
	BOOST_REQUIRE_NO_THROW( fRawStack.newTable( 1, 2 )); 
	BOOST_REQUIRE_NO_THROW( fRawStack.pushNumber( 23 ));
	BOOST_REQUIRE_NO_THROW( fRawStack.setRawTableField( -2, "asd" ));
	BOOST_REQUIRE_NO_THROW( fRawStack.pop());
	BOOST_REQUIRE_NO_THROW( fRawStack.pushString( "asd" ));
	BOOST_CHECK_NO_THROW( fRawStack.getRawTableField( -2 ));
	BOOST_CHECK_EQUAL( fRawStack.toNumber(), 23 );
	BOOST_CHECK_EQUAL( fRawStack.getSize(), 2 );
}

BOOST_AUTO_TEST_CASE( setTableFieldTest01 )
{
	BOOST_CHECK_THROW( fRawStack.setRawTableField( -1 ), Exception::IndexError );
}

BOOST_AUTO_TEST_CASE( setTableFieldTest02 )
{
	BOOST_REQUIRE_NO_THROW( fRawStack.pushNil());
	BOOST_REQUIRE_NO_THROW( fRawStack.pushNil());
	BOOST_CHECK_THROW( fRawStack.setRawTableField( -1 ), Exception::TypeError );
}

BOOST_AUTO_TEST_CASE( setTableFieldTest03 )
{
	BOOST_REQUIRE_NO_THROW( fRawStack.newTable( 0, 0 ));
	BOOST_REQUIRE_NO_THROW( fRawStack.pushNil());
	BOOST_REQUIRE_NO_THROW( fRawStack.pushNil());
	BOOST_CHECK_THROW( fRawStack.setRawTableField( -3 ), Exception::TypeError );
}

BOOST_AUTO_TEST_CASE( setTableFieldTest04 )
{
	BOOST_REQUIRE_NO_THROW( fRawStack.newTable( 1, 2 )); 
	BOOST_REQUIRE_NO_THROW( fRawStack.pushNumber( 23 ));
	BOOST_REQUIRE_NO_THROW( fRawStack.setRawTableField( -2, 1 ));
	BOOST_REQUIRE_NO_THROW( fRawStack.pop());
	BOOST_CHECK_NO_THROW( fRawStack.getRawTableField( -1, 1 ));
	BOOST_CHECK_EQUAL( fRawStack.toNumber(), 23 );
	BOOST_CHECK_EQUAL( fRawStack.getSize(), 2 );
}

BOOST_AUTO_TEST_CASE( setTableFieldTest05 )
{
	BOOST_CHECK_THROW( fRawStack.setRawTableField( -1, 1 ), Exception::IndexError );
}

BOOST_AUTO_TEST_CASE( setTableFieldTest06 )
{
	BOOST_REQUIRE_NO_THROW( fRawStack.pushNil());
	BOOST_REQUIRE_NO_THROW( fRawStack.pushNil());
	BOOST_CHECK_THROW( fRawStack.setRawTableField( -1, 1 ), Exception::TypeError );
}

BOOST_AUTO_TEST_CASE( setTableFieldTest07 )
{
	BOOST_REQUIRE_NO_THROW( fRawStack.newTable( 0, 0 ));
	BOOST_REQUIRE_NO_THROW( fRawStack.pushNil());
	BOOST_CHECK_THROW( fRawStack.setRawTableField( -2, -3 ), Exception::KeyError );
}

BOOST_AUTO_TEST_CASE( setTableFieldTest08 )
{
	BOOST_REQUIRE_NO_THROW( fRawStack.newTable( 1, 2 )); 
	BOOST_REQUIRE_NO_THROW( fRawStack.pushNumber( 23 ));
	BOOST_REQUIRE_NO_THROW( fRawStack.setRawTableField( -2, "asd" ));
	BOOST_REQUIRE_NO_THROW( fRawStack.pop());
	BOOST_CHECK_NO_THROW( fRawStack.getRawTableField( -1, "asd" ));
	BOOST_CHECK_EQUAL( fRawStack.toNumber(), 23 );
	BOOST_CHECK_EQUAL( fRawStack.getSize(), 2 );
}

BOOST_AUTO_TEST_CASE( setTableFieldTest09 )
{
	BOOST_CHECK_THROW( fRawStack.setRawTableField( -1, "a" ), Exception::IndexError );
}

BOOST_AUTO_TEST_CASE( setTableFieldTest10 )
{
	BOOST_REQUIRE_NO_THROW( fRawStack.pushNil());
	BOOST_REQUIRE_NO_THROW( fRawStack.pushNil());
	BOOST_CHECK_THROW( fRawStack.setRawTableField( -1, "a" ), Exception::TypeError );
}

BOOST_AUTO_TEST_CASE( setTableFieldTest11 )
{
	BOOST_REQUIRE_NO_THROW( fRawStack.newTable( 0, 0 ));
	BOOST_REQUIRE_NO_THROW( fRawStack.pushNil());
	BOOST_CHECK_THROW( fRawStack.setRawTableField( -2, "a" ), Exception::KeyError );
}
//TODO meta



BOOST_AUTO_TEST_CASE( setRawTableFieldTest00 )
{
	BOOST_REQUIRE_NO_THROW( fRawStack.newTable( 1, 2 )); 
	BOOST_REQUIRE_NO_THROW( fRawStack.pushNumber( 23 ));
	BOOST_REQUIRE_NO_THROW( fRawStack.setRawTableField( -2, "asd" ));
	BOOST_REQUIRE_NO_THROW( fRawStack.pop());
	BOOST_REQUIRE_NO_THROW( fRawStack.pushString( "asd" ));
	BOOST_CHECK_NO_THROW( fRawStack.getRawTableField( -2 ));
	BOOST_CHECK_EQUAL( fRawStack.toNumber(), 23 );
	BOOST_CHECK_EQUAL( fRawStack.getSize(), 2 );
}

BOOST_AUTO_TEST_CASE( setRawTableFieldTest01 )
{
	BOOST_CHECK_THROW( fRawStack.setRawTableField( -1 ), Exception::IndexError );
}

BOOST_AUTO_TEST_CASE( setRawTableFieldTest02 )
{
	BOOST_REQUIRE_NO_THROW( fRawStack.pushNil());
	BOOST_REQUIRE_NO_THROW( fRawStack.pushNil());
	BOOST_CHECK_THROW( fRawStack.setRawTableField( -1 ), Exception::TypeError );
}

BOOST_AUTO_TEST_CASE( setRawTableFieldTest03 )
{
	BOOST_REQUIRE_NO_THROW( fRawStack.newTable( 0, 0 ));
	BOOST_REQUIRE_NO_THROW( fRawStack.pushNil());
	BOOST_REQUIRE_NO_THROW( fRawStack.pushNil());
	BOOST_CHECK_THROW( fRawStack.setRawTableField( -3 ), Exception::TypeError );
}

BOOST_AUTO_TEST_CASE( setRawTableFieldTest04 )
{
	BOOST_REQUIRE_NO_THROW( fRawStack.newTable( 1, 2 )); 
	BOOST_REQUIRE_NO_THROW( fRawStack.pushNumber( 23 ));
	BOOST_REQUIRE_NO_THROW( fRawStack.setRawTableField( -2, 1 ));
	BOOST_REQUIRE_NO_THROW( fRawStack.pop());
	BOOST_CHECK_NO_THROW( fRawStack.getRawTableField( -1, 1 ));
	BOOST_CHECK_EQUAL( fRawStack.toNumber(), 23 );
	BOOST_CHECK_EQUAL( fRawStack.getSize(), 2 );
}

BOOST_AUTO_TEST_CASE( setRawTableFieldTest05 )
{
	BOOST_CHECK_THROW( fRawStack.setRawTableField( -1, 1 ), Exception::IndexError );
}

BOOST_AUTO_TEST_CASE( setRawTableFieldTest06 )
{
	BOOST_REQUIRE_NO_THROW( fRawStack.pushNil());
	BOOST_REQUIRE_NO_THROW( fRawStack.pushNil());
	BOOST_CHECK_THROW( fRawStack.setRawTableField( -1, 1 ), Exception::TypeError );
}

BOOST_AUTO_TEST_CASE( setRawTableFieldTest07 )
{
	BOOST_REQUIRE_NO_THROW( fRawStack.newTable( 0, 0 ));
	BOOST_REQUIRE_NO_THROW( fRawStack.pushNil());
	BOOST_CHECK_THROW( fRawStack.setRawTableField( -2, -3 ), Exception::KeyError );
}

BOOST_AUTO_TEST_CASE( setRawTableFieldTest08 )
{
	BOOST_REQUIRE_NO_THROW( fRawStack.newTable( 1, 2 )); 
	BOOST_REQUIRE_NO_THROW( fRawStack.pushNumber( 23 ));
	BOOST_REQUIRE_NO_THROW( fRawStack.setRawTableField( -2, "asd" ));
	BOOST_REQUIRE_NO_THROW( fRawStack.pop());
	BOOST_CHECK_NO_THROW( fRawStack.getRawTableField( -1, "asd" ));
	BOOST_CHECK_EQUAL( fRawStack.toNumber(), 23 );
	BOOST_CHECK_EQUAL( fRawStack.getSize(), 2 );
}

BOOST_AUTO_TEST_CASE( setRawTableFieldTest09 )
{
	BOOST_CHECK_THROW( fRawStack.setRawTableField( -1, "a" ), Exception::IndexError );
}

BOOST_AUTO_TEST_CASE( setRawTableFieldTest10 )
{
	BOOST_REQUIRE_NO_THROW( fRawStack.pushNil());
	BOOST_REQUIRE_NO_THROW( fRawStack.pushNil());
	BOOST_CHECK_THROW( fRawStack.setRawTableField( -1, "a" ), Exception::TypeError );
}

BOOST_AUTO_TEST_CASE( setRawTableFieldTest11 )
{
	BOOST_REQUIRE_NO_THROW( fRawStack.newTable( 0, 0 ));
	BOOST_REQUIRE_NO_THROW( fRawStack.pushNil());
	BOOST_CHECK_THROW( fRawStack.setRawTableField( -2, "a" ), Exception::KeyError );
}
//TODO meta



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
	BOOST_CHECK_NO_THROW( fRawStack.copy( -3 ));
	BOOST_CHECK_EQUAL( fRawStack.getSize(), 5 );
	BOOST_CHECK_EQUAL( fRawStack.toNumber( -4 ), 32 );
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
	BOOST_REQUIRE_NO_THROW( fRawStack.pushString( "test" ));
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
	BOOST_CHECK( fRawStack.getType( -2 ) == NIL );
	BOOST_CHECK_EQUAL( fRawStack.toString(), "test" );
}

BOOST_AUTO_TEST_CASE( eraseTest01 )
{
	BOOST_REQUIRE_NO_THROW( fRawStack.pushNumber( 64 ));
	BOOST_CHECK_NO_THROW( fRawStack.erase( -1 ));
	BOOST_CHECK( fRawStack.getType() == NIL );
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
	BOOST_CHECK_THROW( fRawStack.pop( 4 ), Exception::StackError );
	BOOST_CHECK_EQUAL( fRawStack.getSize(), 3 );
}

BOOST_AUTO_TEST_CASE( popTest03 )
{
	BOOST_CHECK_THROW( fRawStack.pop( -4 ), Exception::StackError );
	BOOST_CHECK_THROW( fRawStack.pop( 4 ), Exception::StackError );
	BOOST_CHECK_EQUAL( fRawStack.getSize(), 0 );
}

BOOST_AUTO_TEST_CASE( popTest04 )
{
	BOOST_CHECK_NO_THROW( fRawStack.pop( 0 ));
}



BOOST_AUTO_TEST_CASE( clearTest00 )
{
	BOOST_REQUIRE_NO_THROW( fRawStack.pushNumber( 64 ));
	BOOST_REQUIRE_NO_THROW( fRawStack.pushString( "asd" ));
	BOOST_REQUIRE_NO_THROW( fRawStack.pushString( "test" ));
	BOOST_CHECK_NO_THROW( fRawStack.clear());
	BOOST_CHECK_EQUAL( fRawStack.getSize(), 0 );
}

BOOST_AUTO_TEST_CASE( clearTest01 )
{
	BOOST_CHECK_NO_THROW( fRawStack.clear());
	BOOST_CHECK_EQUAL( fRawStack.getSize(), 0 );
}



BOOST_AUTO_TEST_CASE( replaceTest00 )
{
	BOOST_REQUIRE_NO_THROW( fRawStack.pushNumber( 64 ));
	BOOST_REQUIRE_NO_THROW( fRawStack.pushString( "asd" ));
	BOOST_REQUIRE_NO_THROW( fRawStack.pushString( "test" ));
	BOOST_CHECK_NO_THROW( fRawStack.replace( -1, 2 ));
	BOOST_CHECK_EQUAL( fRawStack.getSize(), 3 );
	BOOST_CHECK_EQUAL( fRawStack.toString( -2 ), "test" );
	BOOST_CHECK_EQUAL( fRawStack.toString(), "test" );
}

BOOST_AUTO_TEST_CASE( replaceTest01 )
{
	BOOST_REQUIRE_NO_THROW( fRawStack.pushNumber( 64 ));
	BOOST_CHECK_NO_THROW( fRawStack.replace( -1, 1 ));
	BOOST_CHECK_EQUAL( fRawStack.getSize(), 1 );
	BOOST_CHECK_EQUAL( fRawStack.toNumber(), 64 );
}

BOOST_AUTO_TEST_CASE( replaceTest02 )
{
	BOOST_CHECK_THROW( fRawStack.replace( -1, 1 ), Exception::IndexError );
	BOOST_CHECK_THROW( fRawStack.replace( 0, 0 ), Exception::IndexError );
	BOOST_CHECK_THROW( fRawStack.replace( 1, 0 ), Exception::IndexError );
}

BOOST_AUTO_TEST_CASE( replaceTest03 )
{
	BOOST_REQUIRE_NO_THROW( fRawStack.pushNumber( 64 ));
	BOOST_CHECK_THROW( fRawStack.replace( -1, 2 ), Exception::IndexError );
	BOOST_CHECK_EQUAL( fRawStack.getSize(), 1 );
	BOOST_CHECK_EQUAL( fRawStack.toNumber(), 64 );
}



BOOST_AUTO_TEST_CASE( moveTest00 )
{
	BOOST_REQUIRE_NO_THROW( fRawStack.pushNumber( 64 ));
	BOOST_REQUIRE_NO_THROW( fRawStack.pushString( "asd" ));
	BOOST_REQUIRE_NO_THROW( fRawStack.pushString( "test" ));
	BOOST_CHECK_NO_THROW( fRawStack.move( -1, 2 ));
	BOOST_CHECK_EQUAL( fRawStack.getSize(), 2 );
	BOOST_CHECK_EQUAL( fRawStack.toString(), "test" );
}

BOOST_AUTO_TEST_CASE( moveTest01 )
{
	BOOST_REQUIRE_NO_THROW( fRawStack.pushNumber( 64 ));
	BOOST_CHECK_NO_THROW( fRawStack.move( -1, 1 ));
	BOOST_CHECK_EQUAL( fRawStack.getSize(), 1 );
	BOOST_CHECK_EQUAL( fRawStack.toNumber(), 64 );
}

BOOST_AUTO_TEST_CASE( moveTest02 )
{
	BOOST_CHECK_THROW( fRawStack.move( -1, 1 ), Exception::IndexError );
	BOOST_CHECK_THROW( fRawStack.move( 0, 0 ), Exception::IndexError );
	BOOST_CHECK_THROW( fRawStack.move( 1, 0 ), Exception::IndexError );
}

BOOST_AUTO_TEST_CASE( moveTest03 )
{
	BOOST_REQUIRE_NO_THROW( fRawStack.pushNumber( 64 ));
	BOOST_CHECK_THROW( fRawStack.move( -1, 2 ), Exception::IndexError );
	BOOST_CHECK_EQUAL( fRawStack.getSize(), 1 );
	BOOST_CHECK_EQUAL( fRawStack.toNumber(), 64 );
}



BOOST_AUTO_TEST_CASE( swapTest00 )
{
	BOOST_REQUIRE_NO_THROW( fRawStack.pushNumber( 64 ));
	BOOST_REQUIRE_NO_THROW( fRawStack.pushString( "asd" ));
	BOOST_REQUIRE_NO_THROW( fRawStack.pushString( "test" ));
	BOOST_CHECK_NO_THROW( fRawStack.swap( -1, 1 ));
	BOOST_CHECK_EQUAL( fRawStack.getSize(), 3 );
	BOOST_CHECK_EQUAL( fRawStack.toNumber( -1 ), 64 );
	BOOST_CHECK_EQUAL( fRawStack.toString( 1 ), "test" );
}

BOOST_AUTO_TEST_CASE( swapTest01 )
{
	BOOST_REQUIRE_NO_THROW( fRawStack.pushNumber( 64 ));
	BOOST_CHECK_NO_THROW( fRawStack.swap( -1, 1 ));
	BOOST_CHECK_EQUAL( fRawStack.getSize(), 1 );
	BOOST_CHECK_EQUAL( fRawStack.toNumber(), 64 );
}

BOOST_AUTO_TEST_CASE( swapTest02 )
{
	BOOST_CHECK_THROW( fRawStack.swap( -1, 1 ), Exception::IndexError );
	BOOST_CHECK_THROW( fRawStack.swap( 0, 0 ), Exception::IndexError );
	BOOST_CHECK_THROW( fRawStack.swap( 1, 0 ), Exception::IndexError );
}

BOOST_AUTO_TEST_CASE( swapTest03 )
{
	BOOST_REQUIRE_NO_THROW( fRawStack.pushNumber( 64 ));
	BOOST_CHECK_THROW( fRawStack.swap( -1, 2 ), Exception::IndexError );
	BOOST_CHECK_EQUAL( fRawStack.getSize(), 1 );
	BOOST_CHECK_EQUAL( fRawStack.toNumber(), 64 );
}



//TODO iterate is a subject to more tests
BOOST_AUTO_TEST_CASE( iterateTest00 )
{
	BOOST_REQUIRE_NO_THROW( fRawStack.doFile( "test.lua" ));
	BOOST_REQUIRE_NO_THROW( fRawStack.getGlobal( "testTable" ));
	BOOST_REQUIRE_NO_THROW( fRawStack.pushNil());
	BOOST_CHECK_NO_THROW( fRawStack.iterate( -2 ));
	BOOST_CHECK( fRawStack.getType() != NIL );
}

BOOST_AUTO_TEST_CASE( iterateTest01 )
{
	BOOST_REQUIRE_NO_THROW( fRawStack.doFile( "test.lua" ));
	BOOST_REQUIRE_NO_THROW( fRawStack.getGlobal( "simpleTable" ));
	BOOST_REQUIRE_NO_THROW( fRawStack.pushNil());
	while( fRawStack.iterate( -2 ))
	{
		if( fRawStack.getType() == NUMBER )
		{
			BOOST_CHECK_EQUAL( fRawStack.toNumber(), 5 );
		}
		else if( fRawStack.getType() == STRING )
		{
			BOOST_CHECK_EQUAL( fRawStack.toString(), "blabla" );
		}
		else
		{
			BOOST_CHECK( false );
		}
		BOOST_REQUIRE_NO_THROW( fRawStack.pop());
	}
	BOOST_CHECK_EQUAL( fRawStack.getSize(), 2 );
}

BOOST_AUTO_TEST_CASE( iterateTest02 )
{
	BOOST_CHECK_THROW( fRawStack.iterate( -2 ), Exception::IndexError );
	BOOST_CHECK_EQUAL( fRawStack.getSize(), 0 );
}



BOOST_AUTO_TEST_CASE( isValidTest00 )
{
	BOOST_REQUIRE_NO_THROW( fRawStack.pushNumber( 64 ));
	BOOST_REQUIRE_NO_THROW( fRawStack.pushString( "asd" ));
	BOOST_REQUIRE_NO_THROW( fRawStack.pushString( "test" ));
	BOOST_CHECK( fRawStack.isValid());
	BOOST_CHECK( fRawStack.isValid( -2 ));
	BOOST_CHECK( fRawStack.isValid( 1 ));
	BOOST_CHECK( fRawStack.isValid( 3 ));
	BOOST_CHECK( !fRawStack.isValid( 0 ));
	BOOST_CHECK( !fRawStack.isValid( 4 ));
	BOOST_CHECK( !fRawStack.isValid( -5 ));
	BOOST_CHECK_EQUAL( fRawStack.getSize(), 3 );
}



BOOST_AUTO_TEST_CASE( getRelativeIndexTest00 )
{
	BOOST_REQUIRE_NO_THROW( fRawStack.pushNumber( 64 ));
	BOOST_REQUIRE_NO_THROW( fRawStack.pushString( "asd" ));
	BOOST_REQUIRE_NO_THROW( fRawStack.pushString( "test" ));
	BOOST_CHECK_EQUAL( fRawStack.getRelativeIndex( 1 ), -3 );
	BOOST_CHECK_EQUAL( fRawStack.getRelativeIndex( 3 ), -1 );
	BOOST_CHECK_THROW( fRawStack.getRelativeIndex( 4 ), Exception::IndexError );
	BOOST_CHECK_THROW( fRawStack.getRelativeIndex( 0 ), Exception::IndexError );
	BOOST_CHECK_EQUAL( fRawStack.getSize(), 3 );
}



BOOST_AUTO_TEST_CASE( getAbsoluteIndexTest00 )
{
	BOOST_REQUIRE_NO_THROW( fRawStack.pushNumber( 64 ));
	BOOST_REQUIRE_NO_THROW( fRawStack.pushString( "asd" ));
	BOOST_REQUIRE_NO_THROW( fRawStack.pushString( "test" ));
	BOOST_CHECK_EQUAL( fRawStack.getAbsoluteIndex( -1 ), 3 );
	BOOST_CHECK_EQUAL( fRawStack.getAbsoluteIndex( -3 ), 1 );
	BOOST_CHECK_EQUAL( fRawStack.getAbsoluteIndex( 3 ), 3 );
	BOOST_CHECK_EQUAL( fRawStack.getAbsoluteIndex( 1 ), 1 );
	BOOST_CHECK_THROW( fRawStack.getAbsoluteIndex( 4 ), Exception::IndexError );
	BOOST_CHECK_THROW( fRawStack.getAbsoluteIndex( 0 ), Exception::IndexError );
	BOOST_CHECK_EQUAL( fRawStack.getSize(), 3 );
}



BOOST_AUTO_TEST_CASE( getSizeTest00 )
{
	BOOST_REQUIRE_NO_THROW( fRawStack.pushNumber( 64 ));
	BOOST_REQUIRE_NO_THROW( fRawStack.pushString( "asd" ));
	BOOST_REQUIRE_NO_THROW( fRawStack.pushString( "test" ));
	BOOST_CHECK_EQUAL( fRawStack.getSize(), 3 );
	BOOST_REQUIRE_NO_THROW( fRawStack.pop());
	BOOST_CHECK_EQUAL( fRawStack.getSize(), 2 );
	BOOST_REQUIRE_NO_THROW( fRawStack.pop( 2 ));
	BOOST_CHECK_EQUAL( fRawStack.getSize(), 0 );
}



BOOST_AUTO_TEST_CASE( getLuaStateTest00 )
{
	BOOST_CHECK( fRawStack.getLuaState() != nullptr );
}

BOOST_AUTO_TEST_SUITE_END();

}
