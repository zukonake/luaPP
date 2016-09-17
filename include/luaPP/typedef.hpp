//2016-luaPP zukonake

#ifndef TYPEDEF_HPP
#define TYPEDEF_HPP

#include <cstdint>
#include <string>

namespace LW
{
	typedef int16_t Index;
	typedef double NumberValue;
	typedef std::string StringValue;
	enum class LuaType
	{
		NIL,
		NUMBER,
		STRING,
		TABLE,
		FUNCTION
	};
}

#endif
