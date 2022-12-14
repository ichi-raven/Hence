/*****************************************************************//**
 * @file   BufferUsage.cpp
 * @brief  BufferUsageNXyΡ»Μ\»ΙΦ·ιρ^EΤ^Μΐ
 *
 * @author ichi-raven
 * @date   November 2022
 *********************************************************************/

#include "../../include/Info/BufferUsage.hpp"

namespace Hence
{
	BufferUsageFlag::BufferUsageFlag(const std::int32_t res)
		:result(res)
	{}

	BufferUsageFlag BufferUsageFlag::operator|(BufferUsageFlag other) const noexcept
	{
		return BufferUsageFlag{ result | other.result };
	}

	BufferUsageFlag BufferUsageFlag::operator|(BufferUsageBit bit) const noexcept
	{
		return BufferUsageFlag{ result | static_cast<std::underlying_type_t<BufferUsageBit>>(bit) };
	}

	BufferUsageFlag operator|(BufferUsageBit L, BufferUsageBit R) noexcept
	{
		return BufferUsageFlag{ static_cast<std::underlying_type_t<BufferUsageBit>>(L) | static_cast<std::underlying_type_t<BufferUsageBit>>(R) };
	}

	BufferUsageFlag operator|(BufferUsageBit L, BufferUsageFlag R) noexcept
	{
		return BufferUsageFlag{ static_cast<std::underlying_type_t<BufferUsageBit>>(L) | R.result };
	}

	BufferUsage::BufferUsage(BufferUsageBit bit) noexcept
		: usage(static_cast<std::underlying_type_t<BufferUsageBit>>(bit))
	{

	}

	BufferUsage::BufferUsage(BufferUsageFlag flag) noexcept
		: usage(flag.result)
	{

	}

	BufferUsageFlag BufferUsage::operator=(BufferUsageBit bit) noexcept
	{
		usage = static_cast<std::underlying_type_t<BufferUsageBit>>(bit);
		return BufferUsageFlag(usage);
	}

	BufferUsageFlag BufferUsage::operator=(BufferUsageFlag flag) noexcept
	{
		usage = flag.result;
		return BufferUsageFlag(usage);
	}

	bool BufferUsage::contains(BufferUsageBit checkUsageBit) const noexcept
	{
		return usage & static_cast<std::uint32_t>(checkUsageBit);
	}
}
