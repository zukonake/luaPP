#include <luna/typedef.hpp>
#include <luna/element/userdata.hpp>

namespace Luna
{

Type Userdata::getType() const noexcept
{
	return USERDATA;
}

}
