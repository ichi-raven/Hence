/*****************************************************************//**
 * @file   Usage.cpp
 * @brief  UsageƒNƒ‰ƒX‹y‚Ñ‚»‚Ì•\Œ»‚ÉŠÖ‚·‚é—ñ‹“Œ^E’†ŠÔŒ^‚ÌÀ‘•
 * 
 * @author ichi-raven
 * @date   November 2022
 *********************************************************************/

#include "../include/Usage.hpp"

namespace Hence
{
	UsageFlag UsageFlag::operator|(UsageFlag other) const noexcept
	{
		return UsageFlag{ result | other.result };
	}

	UsageFlag UsageFlag::operator|(UsageBit bit) const noexcept
	{
		return UsageFlag{ result | static_cast<std::underlying_type_t<UsageBit>>(bit) };
	}

	UsageFlag operator|(UsageBit L, UsageBit R) noexcept
	{
		return UsageFlag{ static_cast<std::underlying_type_t<UsageBit>>(L) | static_cast<std::underlying_type_t<UsageBit>>(R) };
	}

	UsageFlag operator|(UsageBit L, UsageFlag R) noexcept
	{
		return UsageFlag{ static_cast<std::underlying_type_t<UsageBit>>(L) | R.result };
	}

	Usage::Usage(UsageBit bit) noexcept
		: usage(static_cast<std::underlying_type_t<UsageBit>>(bit))
	{

	}

	Usage::Usage(UsageFlag flag)
		: usage(flag.result)
	{

	}
}
