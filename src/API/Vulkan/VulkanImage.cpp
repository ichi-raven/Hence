/*****************************************************************//**
 * @file   VulkanImage.cpp
 * @brief  VulkanImageƒNƒ‰ƒX‚ÌŽÀ‘•
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

	//VulkanImage& VulkanImage::operator=(VulkanImage&& other) noexcept
	//{
	//	mImage		= std::move(other.mImage);
	//	mMemory		= std::move(other.mMemory);
	//	mImageView	= std::move(other.mImageView);

	//	return *this;
	//}

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
