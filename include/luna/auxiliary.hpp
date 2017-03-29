/**
 * @file luna/auxiliary.hpp
 * Copyleft zukonake
 * Distributed under GNU General Public License Version 3
 */

#pragma once

#include <cstdint>
#include <cstddef>
#include <string>
//
#include <lua.hpp>
//
#include <luna/typedef.hpp>

/**
 * Contains auxiliary functions.
 */
namespace Luna::Auxiliary
{

/**
 * Converts Lua C API type to Type.
 */
Type convertType( const LuaType &luaType ) noexcept;

/** 
 * Returns a type name for Type.
 */
std::string getTypeName( Type const &type ) noexcept;

/**
 * Default allocate function for State.
 *
 * @param ud UserData pointer.
 * @param ptr Allocated pointer.
 * @param osize Original size.
 * @param nsize New size.
 *
 * @return Allocated pointer.
 */
void *allocate( void *ud, void *ptr, std::size_t osize, std::size_t nsize );

/**
 * Default panic function for State.
 *
 * @return Success in reporting error.
 */
int panic( LuaState L );

}
