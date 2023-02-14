/*****************************************************************//**
 * @file   VulkanImage.hpp
 * @brief  VulkanImageクラスのヘッダファイル
 * 
 * @author ichi-raven
 * @date   November 2022
 *********************************************************************/
#ifndef HENCE_API_VULKAN_VULKANIMAGE_HPP_
#define HENCE_API_VULKAN_VULKANIMAGE_HPP_

#include "../../Utility/ArrayProxy.hpp"
#include "../../Utility/Result.hpp"

#include "VulkanDevice.hpp"

#include <vulkan/vulkan.hpp>

namespace Hence
{
	class VulkanImage
	{
	public:

		VulkanImage(VulkanDevice& vulkanDevice, VkImage image, VkDeviceMemory memory, VkImageView view, VkExtent3D extent, std::uint32_t sizeOfChannel) noexcept;

		~VulkanImage() noexcept;

		VulkanImage(VulkanImage&& other) noexcept;

		VulkanImage& operator=(VulkanImage&& other) noexcept;

		template <typename DataType>
		Result writeData(const ArrayProxy<DataType> data) noexcept
		{
			return writeImage(data.data(), data.size());
		}

		VkImage getVkImage() noexcept;

		VkDeviceMemory getVkDeviceMemory() noexcept;

		VkImageView getVkImageView() noexcept;

	private:

		Result writeImage(void* ptr, std::uint32_t size);

		VulkanDevice& mDevice;

		VkImage mImage;
		VkDeviceMemory mMemory;
		VkImageView mImageView;
		VkExtent3D mExtent;
		std::uint32_t mSizeOfChannel;
	};
}

#endif