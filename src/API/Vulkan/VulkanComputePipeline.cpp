/*****************************************************************//**
 * @file   VulkanComputePipeline.cpp
 * @brief  VulkanComputePipelineƒNƒ‰ƒX‚ÌŽÀ‘•
 * 
 * @author ichi-raven
 * @date   May 2023
 *********************************************************************/

#include "../../../include/API/Vulkan/VulkanComputePipeline.hpp"
#include "../../../include/API/Vulkan/VulkanDevice.hpp"
#include "../../../include/API/Vulkan/VulkanShader.hpp"
#include "../../../include/API/Vulkan/VulkanBindLayout.hpp"

#include "../../../include/API/Vulkan/Utility/Macro.hpp"

#include "../../../include/Utility/Logger.hpp"

namespace Hence
{
	VulkanComputePipeline::VulkanComputePipeline(VulkanDevice* pVulkanDevice, VulkanBindLayout& bindLayout, VulkanShader& shader) noexcept
		: mpDevice(pVulkanDevice)
		, mPipelineLayout(VK_NULL_HANDLE)
		, mPipeline(VK_NULL_HANDLE)
	{
		assert(pVulkanDevice != nullptr || !"vulkan device is nullptr!");
	
		{
			VkPipelineLayoutCreateInfo ci
			{
				.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO,
				.pNext = nullptr,
				.flags = 0,
				.setLayoutCount = 1,
				.pSetLayouts = bindLayout.getDescriptorSetLayouts().data()
			};

			if (VK_FAILED(res, vkCreatePipelineLayout(mpDevice->getDevice(), &ci, nullptr, &mPipelineLayout)))
			{
				Logger::error("failed to create compute pipeline layout!");
				return;
			}
		}

		VkPipelineShaderStageCreateInfo pssci
		{
			.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
			.pNext = nullptr,
			.flags = 0,
			.stage = static_cast<VkShaderStageFlagBits>(shader.getShaderStage()),
			.module = shader.getVkShaderModule(),
			.pName = shader.getEntryPoint().data(),
			.pSpecializationInfo = nullptr
		};

		{
			VkComputePipelineCreateInfo ci
			{
				.sType = VK_STRUCTURE_TYPE_COMPUTE_PIPELINE_CREATE_INFO,
				.pNext = nullptr,
				.stage = pssci,
				.layout = mPipelineLayout
			};

			if (VK_FAILED(res, vkCreateComputePipelines(mpDevice->getDevice(), VK_NULL_HANDLE, 1, &ci, nullptr, &mPipeline)))
			{
				Logger::error("failed to create compute pipeline!");
				return;
			}
		}
	}

	VulkanComputePipeline::~VulkanComputePipeline() noexcept
	{
		if (mPipelineLayout != VK_NULL_HANDLE)
		{
			vkDestroyPipelineLayout(mpDevice->getDevice(), mPipelineLayout, nullptr);
		}

		if (mPipeline != VK_NULL_HANDLE)
		{
			vkDestroyPipeline(mpDevice->getDevice(), mPipeline, nullptr);
		}
	}

	VkPipeline VulkanComputePipeline::getVkPipeline() noexcept
	{
		return mPipeline;
	}

	VkPipelineLayout VulkanComputePipeline::getVkPipelineLayout() noexcept
	{
		return mPipelineLayout;
	}

}
