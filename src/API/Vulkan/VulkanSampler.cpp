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
	VulkanSampler::VulkanSampler(VulkanDevice& vulkanDevice, SamplerInfo samplerInfo) noexcept
		: mVulkanDevice(vulkanDevice)
	{

		// TODO

		VkSamplerCreateInfo sci{};
		sci.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
		sci.pNext = nullptr;
		sci.minFilter = VK_FILTER_LINEAR;
		sci.magFilter = VK_FILTER_LINEAR;
		sci.addressModeU = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
		sci.addressModeV = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
		sci.addressModeW = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
		sci.maxAnisotropy = 1.f;
		sci.borderColor = VK_BORDER_COLOR_FLOAT_OPAQUE_WHITE;
		
		if (VK_FAILED(res, vkCreateSampler(mVulkanDevice.getDevice(), &sci, nullptr, &mSampler)))
		{
			Logger::error("failed to create VkSampler!(native result : {})", static_cast<std::int32_t>(res));
			return;
		}
	}

	VulkanSampler::~VulkanSampler() noexcept
	{

	}

	VkSampler VulkanSampler::getVkSampler() noexcept
	{
		return mSampler;
	}
}
