/* luna/auxiliary.hpp
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

namespace Luna::Auxiliary
{

std::string getTypeName( const Type &type ) noexcept;
void *allocate( void *ud, void *ptr, std::size_t osize, std::size_t nsize );
int panic( lua_State *L );

}
