/* rawStackFixture.hpp
 * Copyleft zukonake
 * Distributed under GNU General Public License Version 3
 */

#pragma once

#include <luna/rawStack.hpp>
#include <luna/state.hpp>

namespace Luna::Test
{

struct RawStackFixture
{
	RawStackFixture() :
		mState(),
		fRawStack( dynamic_cast< RawStack & >( mState ))
	{

	}
private:
	State mState;
public:
	RawStack &fRawStack;
};

}
