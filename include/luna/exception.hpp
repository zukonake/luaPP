/**
 * @file luna/exeception.hpp
 * @copyright Copyleft zukonake
 * @license Distributed under GNU General Public License Version 3
 */

#pragma once

#include <stdexcept>

/**
 * Contains Luna exceptions.
 */
namespace Luna::Exception
{

//TODO
class NotImplementedError : public std::logic_error
{
	using std::logic_error::logic_error;
};

/**
 * Thrown when file can't be opened.
 */
class FileError : public std::runtime_error
{
	using std::runtime_error::runtime_error;
};

/**
 * Thrown when Luna fails to allocate memory.
 */
class AllocationError : public std::runtime_error
{
	using std::runtime_error::runtime_error;
};

/**
 * Thrown when there is Lua C API error.
 */
class LuaError : public std::runtime_error
{
	using std::runtime_error::runtime_error;
};

/**
 * Thrown when there is a syntax error in a lua script.
 */
class SyntaxError : public LuaError
{
	using LuaError::LuaError;
};

/**
 * Thrown when function returns an unexpected number of arguments
 */
class UnexpectedReturnError : public LuaError
{
	using LuaError::LuaError;
};

/**
 * Thrown when there is an error concerning State
 */
class StateError : public std::runtime_error
{
	using std::runtime_error::runtime_error;
};

/**
 * Thrown when there is an error concerning Stack or RawStack.
 */
class StackError : public StateError
{
	using StateError::StateError;
};

/**
 * Thrown when an invalid index is accessed on Stack or RawStack.
 */
class IndexError : public StackError
{
	using StackError::StackError;
};

/**
 * Thrown when a stack value contains unexpected type.
 */
class TypeError : public StackError
{
	using StackError::StackError;
};

/**
 * Thrown when a reserved name is used, for example when creating meta tables.
 */
class ReservedNameError : public StackError
{
	using StackError::StackError;
};

}
