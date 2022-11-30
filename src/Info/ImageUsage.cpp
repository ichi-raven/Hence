/*****************************************************************//**
 * @file   ImageUsage.cpp
 * @brief  ImageUsageÉNÉâÉXãyÇ—ÇªÇÃï\åªÇ…ä÷Ç∑ÇÈóÒãìå^ÅEíÜä‘å^ÇÃé¿ëï
 * 
 * @author ichi-raven
 * @date   November 2022
 *********************************************************************/

#include "../../include/Info/ImageUsage.hpp"

namespace Hence
{
	ImageUsageFlag::ImageUsageFlag(const std::int32_t res)
		: result(res)
	{}

	ImageUsageFlag ImageUsageFlag::operator|(ImageUsageFlag other) const noexcept
	{
		return ImageUsageFlag{ result | other.result };
	}

	ImageUsageFlag ImageUsageFlag::operator|(ImageUsageBit bit) const noexcept
	{
		return ImageUsageFlag{ result | static_cast<std::underlying_type_t<ImageUsageBit>>(bit) };
	}

	ImageUsageFlag operator|(ImageUsageBit L, ImageUsageBit R) noexcept
	{
		return ImageUsageFlag{ static_cast<std::underlying_type_t<ImageUsageBit>>(L) | static_cast<std::underlying_type_t<ImageUsageBit>>(R) };
	}

	ImageUsageFlag operator|(ImageUsageBit L, ImageUsageFlag R) noexcept
	{
		return ImageUsageFlag{ static_cast<std::underlying_type_t<ImageUsageBit>>(L) | R.result };
	}

	ImageUsage::ImageUsage(ImageUsageBit bit) noexcept
		: usage(static_cast<std::underlying_type_t<ImageUsageBit>>(bit))
	{}

	ImageUsage::ImageUsage(ImageUsageFlag flag) noexcept
		: usage(flag.result)
	{}

	ImageUsageFlag ImageUsage::operator=(ImageUsageBit bit) noexcept
	{
		usage = static_cast<std::underlying_type_t<ImageUsageBit>>(bit);
		return ImageUsageFlag(usage);
	}

	ImageUsageFlag ImageUsage::operator=(ImageUsageFlag flag) noexcept
	{
		usage = flag.result;
		return ImageUsageFlag(usage);
	}

	bool ImageUsage::contains(ImageUsageBit checkUsageBit) const noexcept
	{
		return usage & static_cast<std::uint32_t>(checkUsageBit);
	}

}
