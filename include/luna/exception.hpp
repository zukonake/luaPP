/**
 * @file luna/exeception.hpp
 * Copyleft zukonake
 * Distributed under GNU General Public License Version 3
 */

#pragma once

#include <stdexcept>

/**
 * Contains Luna exceptions.
 */

namespace Luna::Exception
{

/**
 * Thrown when file can't be opened.
 */

class FileError : public std::runtime_error
{
public:
	using std::runtime_error::runtime_error;
};

/**
 * Thrown when Luna fails to allocate memory.
 */

class AllocationError : public std::runtime_error
{
public:
	using std::runtime_error::runtime_error;
};

/**
 * Thrown when there is Lua C API error.
 */

class LuaError : public std::runtime_error
{
public:
	using std::runtime_error::runtime_error;
};

/**
 * Thrown when there is a syntax error in a lua script.
 */

class SyntaxError : public LuaError
{
public:
	using LuaError::LuaError;
};

/**
 * Thrown when there is an error concerning State
 */

class StateError : public std::runtime_error
{
public:
	using std::runtime_error::runtime_error;
};

/**
 * Thrown when there is an error concerning Stack or RawStack.
 */

class StackError : public StateError
{
public:
	using StateError::StateError;
};

/**
 * Thrown when an invalid index is accessed on Stack or RawStack.
 */

class IndexError : public StackError
{
public:
	using StackError::StackError;
};

/**
 * Thrown when a stack value contains unexpected type.
 */

class TypeError : public StackError
{
public:
	using StackError::StackError;
};

}
