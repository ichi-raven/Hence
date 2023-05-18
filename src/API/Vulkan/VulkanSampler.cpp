/*****************************************************************//**
 * @file   VulkanSampler.cpp
 * @brief  VulkanSamplerクラスのソースファイル
 *
 * @author ichi-raven
 * @date   February 2023
 *********************************************************************/

#include "../../../include/API/Vulkan/VulkanSampler.hpp"

#include "../../../include/API/Vulkan/VulkanDevice.hpp"

#include "../../../include/API/Vulkan/Utility/Macro.hpp"

#include "../../../include/Utility/Logger.hpp"


namespace Hence
{
	VulkanSampler::VulkanSampler(VulkanDevice* pVulkanDevice, SamplerInfo samplerInfo) noexcept
		: mpDevice(pVulkanDevice)
	{
		assert(pVulkanDevice != nullptr || !"vulkan device is nullptr!");
		// TODO

		VkSamplerCreateInfo sci
		{
			.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO,
			.pNext = nullptr,
			.magFilter = VK_FILTER_LINEAR,
			.minFilter = VK_FILTER_LINEAR,
			.addressModeU = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE,
			.addressModeV = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE,
			.addressModeW = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE,
			.maxAnisotropy = 1.f,
			.borderColor = VK_BORDER_COLOR_FLOAT_OPAQUE_WHITE
		};

		if (VK_FAILED(res, vkCreateSampler(mpDevice->getDevice(), &sci, nullptr, &mSampler)))
		{
			Logger::error("failed to create VkSampler!(native result : {})", static_cast<std::int32_t>(res));
			return;
		}
	}

	VulkanSampler::~VulkanSampler() noexcept
	{
		vkDestroySampler(mpDevice->getDevice(), mSampler, nullptr);
	}

	VkSampler VulkanSampler::getVkSampler() noexcept
	{
		return mSampler;
	}
}
