/*****************************************************************//**
 * @file   VulkanImage.cpp
 * @brief  VulkanImageクラスの実装
 * 
 * @author ichi-raven
 * @date   November 2022
 *********************************************************************/
#include "../../../include/API/Vulkan/VulkanImage.hpp"

namespace Hence
{
	VulkanImage::VulkanImage(VkImage image, VkDeviceMemory memory, VkImageView imageView)
		: mImage(image)
		, mMemory(memory)
		, mImageView(imageView)
	{

	}

	VulkanImage::~VulkanImage()
	{

	}

	VkImage VulkanImage::getVkImage() noexcept
	{
		return mImage;
	}

	VkDeviceMemory VulkanImage::getVkDeviceMemory() noexcept
	{
		return mMemory;
	}

	VkImageView VulkanImage::getVkImageView() noexcept
	{
		return mImageView;
	}
}
