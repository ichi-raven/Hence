/*****************************************************************//**
 * @file   VulkanComputePipeline.hpp
 * @brief  VulkanComputePipelineクラスのヘッダファイル
 * 
 * @author ichi-raven
 * @date   May 2023
 *********************************************************************/
#ifndef HENCE_API_VULKAN_VULKANCOMPUTEPIPELINE_HPP_
#define HENCE_API_VULKAN_VULKANCOMPUTEPIPELINE_HPP_

#include "../../Info/Format.hpp"
#include "../../Utility/Result.hpp"

#include <vulkan/vulkan.hpp>

namespace Hence
{
	class VulkanDevice;
	class VulkanShader;
	class VulkanBindLayout;

	class VulkanComputePipeline
	{
	public:

		VulkanComputePipeline(VulkanDevice* pVulkanDevice, VulkanBindLayout& bindLayout, VulkanShader& shader) noexcept;

		~VulkanComputePipeline() noexcept;

		VkPipeline getVkPipeline() noexcept;

		VkPipelineLayout getVkPipelineLayout() noexcept;

	private:

		VulkanDevice* mpDevice;

		VkPipelineLayout mPipelineLayout;
		VkPipeline mPipeline;
	};

}

#endif