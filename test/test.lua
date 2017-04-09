sampleMetaTable = {}

function sampleMetaTable.toString( obj )
	return "Is this of workingz?"
end

testStuff =
{
	"asdasd"
}
setmetatable( testStuff, sampleMetaTable )

testString = "test"
function testFunction()
	return "test1", 123
end

simpleTable =
{
	5,
	asdf = "blabla",
}

testTable =
{
	25,
	"test",
	var = "test",
	var1 = "test2",
	var2 =
	{
		var0 = 1230,
		23
	},
	{
		"xD"
	}
}
