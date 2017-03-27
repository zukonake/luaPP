/* luna/exeception.hpp
 * Copyleft zukonake
 * Distributed under GNU General Public License Version 3
 */

#pragma once

#include <stdexcept>

namespace Luna::Exception
{

class FileError : public std::runtime_error
{
public:
	using std::runtime_error::runtime_error;
};

class LuaError : public std::runtime_error
{
public:
	using std::runtime_error::runtime_error;
};

class SyntaxError : public LuaError
{
public:
	using LuaError::LuaError;
};

class StateError : public std::runtime_error
{
public:
	using std::runtime_error::runtime_error;
};

class AllocationError : public std::runtime_error
{
public:
	using std::runtime_error::runtime_error;
};

class StackError : public std::runtime_error
{
public:
	using std::runtime_error::runtime_error;
};

class IndexError : public StackError
{
public:
	using StackError::StackError;
};

class TypeError : public StackError
{
public:
	using StackError::StackError;
};

}
