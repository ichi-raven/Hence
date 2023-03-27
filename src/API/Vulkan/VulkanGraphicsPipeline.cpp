/*****************************************************************//**
 * @file   VulkanGraphicsPipeline.cpp
 * @brief  VulkanGraphicsPipelineÉNÉâÉXÇÃé¿ëï
 *
 * @author ichi-raven
 * @date   March 2023
 *********************************************************************/

#include "../../../include/API/Vulkan/VulkanGraphicsPipeline.hpp"

#include "../../../include/API/Vulkan/VulkanDevice.hpp"
#include "../../../include/API/Vulkan/VulkanBindLayout.hpp"

#include "../../../include/API/Vulkan/Utility/Macro.hpp"
#include "../../../include/Utility/Logger.hpp"
#include "../../../include/Utility/Macro.hpp"

namespace Hence
{


	VulkanGraphicsPipeline::~VulkanGraphicsPipeline() noexcept
	{
		vkDestroyPipeline(mDevice.getDevice(), mPipeline, nullptr);
	}

	VkPipeline VulkanGraphicsPipeline::getVkPipeline() noexcept
	{
		return mPipeline;
	}

	inline Result VulkanGraphicsPipeline::createPipeline(const GraphicsPipelineInfo& gpi, VkRenderPass& renderpass, VulkanBindLayout& bindlayout, const std::vector<std::tuple<std::string_view, ShaderStage, VkShaderModule>>& shaderStages) noexcept
	{

		VkPipelineInputAssemblyStateCreateInfo iaci{};

		VkPipelineVertexInputStateCreateInfo visci{};

		VkPipelineRasterizationStateCreateInfo rci{};

		VkPipelineDepthStencilStateCreateInfo dsci{};

		VkPipelineMultisampleStateCreateInfo msci{};

		VkPipelineViewportStateCreateInfo vpsci{};

		VkPipelineColorBlendStateCreateInfo cbci{};
		{
			cbci.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
			cbci.blendConstants = gpi.colorBlendingState.blendConstants;
			cbci.logicOpEnable = gpi.colorBlendingState.logicOp.has_value();
			if (cbci.logicOpEnable)
			{
				cbci.logicOp = static_cast<VkLogicOp>(*(gpi.colorBlendingState.logicOp));
			}

			cbci.attachmentCount = static_cast<std::uint32_t>(gpi.colorBlendingState.attachments.size());
			// ãÍì˜ÇÃçÙ
			cbci.pAttachments = reinterpret_cast<const VkPipelineColorBlendAttachmentState*>(gpi.colorBlendingState.attachments.data());
		}


		std::vector<VkPipelineShaderStageCreateInfo> ssciVec;
		{
			ssciVec.reserve(shaderStages.size());

			for (const auto& stage : shaderStages)
			{
				auto& ssci	= ssciVec.emplace_back();
				ssci.sType	= VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
				ssci.pNext	= nullptr;
				ssci.stage	= static_cast<VkShaderStageFlagBits>(std::get<1>(stage));
				ssci.module = std::get<2>(stage);
				ssci.pName	= std::get<0>(stage).data();
			}
		}

		VkPipelineLayout pipelineLayout = VK_NULL_HANDLE;
		{
			const auto& descriptorSetLayouts = bindlayout.getDescriptorSetLayouts();

			VkPipelineLayoutCreateInfo ci{};
			ci.sType			= VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
			ci.setLayoutCount	= static_cast<std::uint32_t>(descriptorSetLayouts.size());
			ci.pSetLayouts		= descriptorSetLayouts.data();

			if (VK_FAILED(res, vkCreatePipelineLayout(mDevice.getDevice(), &ci, nullptr, &pipelineLayout)))
			{
				Logger::error("failed to create pipeline layout!");
				return Result(res);
			}			
		}

		{  // graphics pipeline 

			VkGraphicsPipelineCreateInfo ci{};
			ci.sType				= VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
			ci.stageCount			= static_cast<uint32_t>(ssciVec.size());
			ci.pStages				= ssciVec.data();
			ci.pInputAssemblyState	= &iaci;
			ci.pVertexInputState	= &visci;
			ci.pRasterizationState	= &rci;
			ci.pDepthStencilState	= &dsci;
			ci.pMultisampleState	= &msci;
			ci.pViewportState		= &vpsci;
			ci.pColorBlendState		= &cbci;
			ci.renderPass			= renderpass;
			ci.layout				= pipelineLayout;


			if (VK_FAILED(res, vkCreateGraphicsPipelines(mDevice.getDevice(), VK_NULL_HANDLE, 1, &ci, nullptr, &mPipeline)))
			{
				Logger::error("failed to create graphics pipeline!");
				return Result(res);
			}

		}
	}

}
