#ifndef TYPEDEF_HPP
#define TYPEDEF_HPP

#include <cstdint>
#include <string>
//
#include <lua5.2/lua.hpp>

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
