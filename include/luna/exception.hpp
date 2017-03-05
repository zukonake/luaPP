/* luna/exeception.hpp
 * Copyleft zukonake
 * Distributed under GNU General Public License Version 3
 */

#pragma once

#include <stdexcept>

namespace Luna::Exception
{

using std::runtime_error;

class InvalidType : public runtime_error
{
public:
	using runtime_error::runtime_error;

	virtual ~InvalidType() = default;

	using runtime_error::operator=;
};

}
