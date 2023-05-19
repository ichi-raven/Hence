/*****************************************************************//**
 * @file   VulkanSemaphore.hpp
 * @brief  VulkanSemaphoreクラスのヘッダファイル
 * 
 * @author ichi-raven
 * @date   April 2023
 *********************************************************************/
#ifndef HENCE_API_VULKAN_VULKANSEMAPHORE_HPP_
#define HENCE_API_VULKAN_VULKANSEMAPHORE_HPP_

#include "VulkanDevice.hpp"

namespace Hence
{
	class VulkanSemaphore
	{
	public:
		VulkanSemaphore(VulkanDevice* pVulkanDevice) noexcept;

		~VulkanSemaphore() noexcept;

		VulkanSemaphore(VulkanSemaphore&& other) noexcept;

		VulkanSemaphore& operator=(VulkanSemaphore&& other) noexcept;

		VkSemaphore getVkSemaphore() noexcept;

	private:
		VulkanDevice* mpDevice;

		VkSemaphore mSemaphore;
	};
}

#endif
