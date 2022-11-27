/*****************************************************************//**
 * @file   Result.cpp
 * @brief  ResultƒNƒ‰ƒX‚ÌŽÀ‘•
 * 
 * @author ichi-raven
 * @date   November 2022
 *********************************************************************/

#include "../../include/Utility/Result.hpp"

namespace Hence
{
	Result::Result() noexcept
		: succeeded(true)
		, nativeResult(0)
	{}

	Result::Result(const std::int32_t nativeError) noexcept
		: succeeded(false)
		, nativeResult(nativeError)
	{}

	Result::operator bool() const noexcept
	{
		return succeeded;
	}

	bool Result::operator!() const noexcept
	{
		return !static_cast<bool>(*this);
	}

}
