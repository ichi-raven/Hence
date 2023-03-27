/*****************************************************************//**
 * @file   ColorComponent.cpp
 * @brief  ColorComponentÉNÉâÉXãyÇ—ÇªÇÃï\åªÇ…ä÷Ç∑ÇÈóÒãìå^ÅEíÜä‘å^ÇÃé¿ëï
 * 
 * @author ichi-raven
 * @date   March 2023
 *********************************************************************/

#include "../../include/Info/ColorComponent.hpp"

namespace Hence
{
	ColorComponentFlag::ColorComponentFlag(const std::int32_t res)
		:result(res)
	{}

	ColorComponentFlag ColorComponentFlag::operator|(ColorComponentFlag other) const noexcept
	{
		return ColorComponentFlag{ result | other.result };
	}

	ColorComponentFlag ColorComponentFlag::operator|(ColorComponentBit bit) const noexcept
	{
		return ColorComponentFlag{ result | static_cast<std::underlying_type_t<ColorComponentBit>>(bit) };
	}

	ColorComponentFlag operator|(ColorComponentBit L, ColorComponentBit R) noexcept
	{
		return ColorComponentFlag{ static_cast<std::underlying_type_t<ColorComponentBit>>(L) | static_cast<std::underlying_type_t<ColorComponentBit>>(R) };
	}

	ColorComponentFlag operator|(ColorComponentBit L, ColorComponentFlag R) noexcept
	{
		return ColorComponentFlag{ static_cast<std::underlying_type_t<ColorComponentBit>>(L) | R.result };
	}

	ColorComponent::ColorComponent(ColorComponentBit bit) noexcept
		: bitFlag(static_cast<std::underlying_type_t<ColorComponentBit>>(bit))
	{

	}

	ColorComponent::ColorComponent(ColorComponentFlag flag) noexcept
		: bitFlag(flag.result)
	{

	}

	ColorComponentFlag ColorComponent::operator=(ColorComponentBit bit) noexcept
	{
		bitFlag = static_cast<std::underlying_type_t<ColorComponentBit>>(bit);
		return ColorComponentFlag(bitFlag);
	}

	ColorComponentFlag ColorComponent::operator=(ColorComponentFlag flag) noexcept
	{
		bitFlag = flag.result;
		return ColorComponentFlag(bitFlag);
	}

	bool ColorComponent::contains(ColorComponentBit checkUsageBit) const noexcept
	{
		return bitFlag & static_cast<std::uint32_t>(checkUsageBit);
	}
}
