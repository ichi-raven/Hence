/*****************************************************************//**
 * @file   ImageUsage.cpp
 * @brief  ImageUsage�N���X�y�т��̕\���Ɋւ���񋓌^�E���Ԍ^�̎���
 * 
 * @author ichi-raven
 * @date   November 2022
 *********************************************************************/

#include "../include/Info/ImageUsage.hpp"

namespace Hence
{
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
	{

	}

	ImageUsage::ImageUsage(ImageUsageFlag flag)
		: usage(flag.result)
	{

	}

	ImageUsageFlag operator=(ImageUsageBit bit) noexcept
	{
		usage = static_cast<std::underlying_type_t<BufferUsageBit>>(bit);
	}

	ImageUsageFlag operator=(ImageUsageFlag flag) noexcept
	{
		usage = flag.result;
	}
}
