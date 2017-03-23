#include <luna/typedef.hpp>
#include <luna/element/nil.hpp>

namespace Luna
{

Type Nil::getType() const noexcept
{
	return NIL;
}

}
