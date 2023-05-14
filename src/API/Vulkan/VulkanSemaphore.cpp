/*****************************************************************//**
 * @file   VulkanSemaphore.cpp
 * @brief  VulkanSemaphoreクラスのソースファイル
 * 
 * @author ichi-raven
 * @date   May 2023
 *********************************************************************/
#include "../../../include/API/Vulkan/VulkanSemaphore.hpp"
#include "../../../include/API/Vulkan/VulkanDevice.hpp"
#include "../../../include/API/Vulkan/Utility/Macro.hpp"

#include "../../../include/Utility/Logger.hpp"

namespace Hence
{
	VulkanSemaphore::VulkanSemaphore(VulkanDevice* pVulkanDevice) noexcept
		: mpDevice(pVulkanDevice)
	{
		assert(pVulkanDevice != nullptr || !"vulkan device is nullptr!");

		VkSemaphoreCreateInfo ci
		{
			.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO,
			.pNext = nullptr,
			.flags = 0
		};

		if (VK_FAILED(res, vkCreateSemaphore(mpDevice->getDevice(), &ci, nullptr, &mSemaphore)))
		{
			Logger::error("failed to create semaphore!");
		}
	}

	VulkanSemaphore::~VulkanSemaphore() noexcept
	{
		vkDestroySemaphore(mpDevice->getDevice(), mSemaphore, nullptr);
	}

	VkSemaphore VulkanSemaphore::getVkSemaphore() noexcept
	{
		return mSemaphore;
	}
}
