//2016-luaPP zukonake

#ifndef LPP_TYPEDEF_HPP
#define LPP_TYPEDEF_HPP

#include <cstdint>
#include <string>

namespace LPP
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
