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
		: APIerrorID(0)
	{}

	Result::Result(const int APIerror) noexcept
		: APIerrorID(APIerror)
	{}

	explicit Result::operator bool() noexcept
	{
		return succeeded();
	}

	inline bool Result::succeeded() noexcept
	{
		return APIerrorID == 0;
	}

	inline bool Result::failed() noexcept
	{
		return !succeeded();
	}
}
