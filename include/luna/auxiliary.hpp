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

constexpr uint8_t lunaVersionMajor = 2;
constexpr uint8_t lunaVersionMinor = 0;
constexpr uint8_t lunaVersionPatch = 0;

Type convertType( const LuaType &luaType ) noexcept;
std::string getTypeName( Type const &type ) noexcept;
void *allocate( void *ud, void *ptr, std::size_t osize, std::size_t nsize );
int panic( lua_State *L );

}
