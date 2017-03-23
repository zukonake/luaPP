#include <luna/typedef.hpp>
#include <luna/element/lightUserdata.hpp>

namespace Luna
{

Type LightUserdata::getType() const noexcept
{
	return LIGHT_USERDATA;
}

}
