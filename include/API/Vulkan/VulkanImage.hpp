/*****************************************************************//**
 * @file   VulkanImage.hpp
 * @brief  VulkanImageクラスのヘッダファイル
 * 
 * @author ichi-raven
 * @date   November 2022
 *********************************************************************/
#ifndef HENCE_API_VULKAN_VULKANIMAGE_HPP_
#define HENCE_API_VULKAN_VULKANIMAGE_HPP_

#include <vulkan/vulkan.hpp>

namespace Hence
{
	class VulkanImage
	{
	public:

		VulkanImage(VkImage image, VkDeviceMemory memory, VkImageView view);

		~VulkanImage();

		//VulkanImage& operator=(VulkanImage&& other) noexcept;

		VkImage getVkImage() noexcept;

		VkDeviceMemory getVkDeviceMemory() noexcept;

		VkImageView getVkImageView() noexcept;

	private:

		VkImage mImage;
		VkDeviceMemory mMemory;
		VkImageView mImageView;
	};
}

#endif