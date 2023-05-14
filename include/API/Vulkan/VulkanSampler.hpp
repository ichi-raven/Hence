/*****************************************************************//**
 * @file   VulkanSampler.hpp
 * @brief  VulkanSamplerクラスのヘッダファイル
 * 
 * @author ichi-raven
 * @date   December 2022
 *********************************************************************/
#ifndef HENCE_API_VULKAN_VULKANSAMPLER_HPP_
#define HENCE_API_VULKAN_VULKANSAMPLER_HPP_

#include "../../Info/SamplerInfo.hpp"

#include <vulkan/vulkan.hpp>

namespace Hence
{
	class VulkanDevice;

	class VulkanSampler
	{
	public:
		
		VulkanSampler(VulkanDevice* pVulkanDevice, SamplerInfo samplerInfo) noexcept;
		
		~VulkanSampler() noexcept;

		VkSampler getVkSampler() noexcept;

	private:
		VulkanDevice* mpDevice;
		
		VkSampler mSampler;
	};
}

#endif
