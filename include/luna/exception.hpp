/* luna/exeception.hpp
 * Copyleft zukonake
 * Distributed under GNU General Public License Version 3
 */

#pragma once

#include <stdexcept>

/**
 * Namespace containing Luna exceptions.
 */

namespace Luna::Exception
{

/**
 * Exception thrown when file can't be opened.
 */

class FileError : public std::runtime_error
{
public:
	using std::runtime_error::runtime_error;
};

/**
 * Exception thrown when Luna fails to allocate memory.
 */

class AllocationError : public std::runtime_error
{
public:
	using std::runtime_error::runtime_error;
};

/**
 * Exception thrown when there is Lua C API error.
 */

class LuaError : public std::runtime_error
{
public:
	using std::runtime_error::runtime_error;
};

/**
 * Exception thrown when there is a syntax error in a lua script.
 */

class SyntaxError : public LuaError
{
public:
	using LuaError::LuaError;
};

/**
 * Exception thrown when there is an error concerning Luna::State
 */

class StateError : public std::runtime_error
{
public:
	using std::runtime_error::runtime_error;
};

/**
 * Exception thrown when there is an error concerning Luna::Stack or Luna::RawStack.
 */

class StackError : public StateError
{
public:
	using StateError::StateError;
};

/**
 * Exception thrown when an invalid index is accessed on Luna::Stack or Luna::RawStack.
 */

class IndexError : public StackError
{
public:
	using StackError::StackError;
};

/**
 * Exception thrown when a stack value contains unexpected type.
 */

class TypeError : public StackError
{
public:
	using StackError::StackError;
};

}
