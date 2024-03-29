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

		VulkanImage(VulkanDevice* pVulkanDevice, VkImage image, VkDeviceMemory memory, VkImageView view, VkFormat format, const VkExtent3D& extent) noexcept;

		~VulkanImage() noexcept;

		VulkanImage(VulkanImage&& other) noexcept;

		VulkanImage& operator=(VulkanImage&& other) noexcept;

		template <typename DataType>
		Result writeImage(const ArrayProxy<DataType> data) noexcept
		{
			return writeImage(reinterpret_cast<const void*>(data.data()), data.size());
		}

		VkImage getVkImage() noexcept;

		VkDeviceMemory getVkDeviceMemory() noexcept;

		VkImageView getVkImageView() noexcept;

		const VkExtent3D& getVkExtent() noexcept;

		VkFormat getVkFormat() const noexcept;

	private:

		Result writeImage(const void* ptr, std::uint32_t size);

		VulkanDevice* mpDevice;

		VkImage mImage;
		VkDeviceMemory mMemory;
		VkImageView mImageView;
		VkExtent3D mExtent;
		VkFormat mFormat;
		std::uint32_t mSizeOfChannel;
	};
}

#endif