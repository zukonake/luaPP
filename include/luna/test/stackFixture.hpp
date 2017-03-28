/* luna/test/stackFixture.hpp
 * Copyleft zukonake
 * Distributed under GNU General Public License Version 3
 */

#pragma once

#include <luna/stack.hpp>
#include <luna/state.hpp>

namespace Luna::Test
{

struct StackFixture
{
	StackFixture() :
		mState(),
		fStack( dynamic_cast< Stack & >( mState ))
	{

	}
private:
	State mState;
public:
	Stack &fStack;
};

}
