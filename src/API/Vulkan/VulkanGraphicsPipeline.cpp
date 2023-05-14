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
#include "../../../include/API/Vulkan/VulkanRenderPass.hpp"

#include "../../../include/API/Vulkan/Utility/HelperFunctions.hpp"
#include "../../../include/API/Vulkan/Utility/Macro.hpp"
#include "../../../include/Utility/Logger.hpp"
#include "../../../include/Utility/Macro.hpp"

namespace Hence
{

	VulkanGraphicsPipeline::~VulkanGraphicsPipeline() noexcept
	{
		vkDestroyPipelineLayout(mpDevice->getDevice(), mPipelineLayout, nullptr);
		vkDestroyPipeline(mpDevice->getDevice(), mPipeline, nullptr);
	}

	VkPipeline VulkanGraphicsPipeline::getVkPipeline() noexcept
	{
		return mPipeline;
	}

	VkPipelineLayout VulkanGraphicsPipeline::getVkPipelineLayout() noexcept
	{
		return mPipelineLayout;
	}


	Result VulkanGraphicsPipeline::createPipeline(const GraphicsPipelineInfo& gpi, const std::vector<Format>& inputVars, VulkanRenderPass& renderpass, VulkanBindLayout& bindlayout, const std::vector<std::tuple<std::string_view, ShaderStage, VkShaderModule>>& shaderStages) noexcept
	{
		VkVertexInputBindingDescription ib{ .binding = 0, .inputRate = VK_VERTEX_INPUT_RATE_VERTEX };

		VkPipelineVertexInputStateCreateInfo visci
		{
			.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO,
			.pNext = nullptr,
			.flags = 0,
			.vertexBindingDescriptionCount = inputVars.empty() ? 0u : 1u,
			.pVertexBindingDescriptions = inputVars.empty() ? nullptr : &ib,
			.vertexAttributeDescriptionCount = static_cast<std::uint32_t>(inputVars.size()),
			.pVertexAttributeDescriptions = nullptr
		};
		// pVertexAttributeDescriptions
		{
			std::vector<VkVertexInputAttributeDescription> ias;
			ias.reserve(inputVars.size());

			std::uint32_t nowOffset = 0;

			for (std::size_t i = 0; i < inputVars.size(); ++i)
			{
				// ç≈ìKâªÇµÇƒÇ≠ÇÍ
				const auto format = inputVars[i];
				auto& ia = ias.emplace_back();

				ia.binding = 0;
				ia.location = static_cast<std::uint32_t>(i);
				ia.format = static_cast<VkFormat>(format);
				ia.offset = nowOffset;

				nowOffset += getSizeOfFormat(format);
			}

			visci.pVertexAttributeDescriptions = ias.data();
		}

		VkPipelineInputAssemblyStateCreateInfo iaci
		{
			.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO,
			.pNext = nullptr,
			.flags = 0,
			.topology = static_cast<VkPrimitiveTopology>(gpi.topology),
			// TODO:ÇŸÇÒÇ∆Ç…??????
			.primitiveRestartEnable = false,
		};


		VkPipelineRasterizationStateCreateInfo rci{};
		{
			rci.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
			rci.pNext = nullptr;
			rci.flags = 0;

			rci.rasterizerDiscardEnable = gpi.rasterizerState.rasterizerDiscardEnable;
			rci.cullMode = static_cast<VkCullModeFlagBits>(gpi.rasterizerState.cullMode);
			rci.frontFace = static_cast<VkFrontFace>(gpi.rasterizerState.frontFace);
			rci.lineWidth = gpi.rasterizerState.lineWidth;
			rci.polygonMode = static_cast<VkPolygonMode>(gpi.rasterizerState.polygonMode);

			rci.depthClampEnable = !!gpi.rasterizerState.depthBias;
			if (rci.depthClampEnable)
			{
				rci.depthBiasConstantFactor = gpi.rasterizerState.depthBias->constantFactor;
				rci.depthBiasClamp = gpi.rasterizerState.depthBias->clamp;
				rci.depthBiasSlopeFactor = gpi.rasterizerState.depthBias->slopeFactor;
			}
		}

		VkPipelineMultisampleStateCreateInfo msci
		{
			.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO,
			.pNext = nullptr,
			.flags = 0,
			.rasterizationSamples = static_cast<VkSampleCountFlagBits>(gpi.multiSampleState.rasterizationSamples.flag),
			.sampleShadingEnable = static_cast<VkBool32>(gpi.multiSampleState.sampleShadingEnable),
			.minSampleShading = gpi.multiSampleState.minSampleShading,
			.pSampleMask = gpi.multiSampleState.sampleMasks.data(),
			.alphaToCoverageEnable = static_cast<VkBool32>(gpi.multiSampleState.alphaToCoverageEnable),
			.alphaToOneEnable = static_cast<VkBool32>(gpi.multiSampleState.alphaToOneEnable)
		};


		VkViewport viewport{};
		if (gpi.viewport)
		{
			viewport.x = gpi.viewport.value()[0][0];
			viewport.y = gpi.viewport.value()[0][1];
			viewport.minDepth = gpi.viewport.value()[0][2];

			viewport.width = gpi.viewport.value()[1][0];
			viewport.height = gpi.viewport.value()[1][1];
			viewport.maxDepth = gpi.viewport.value()[1][2];
		}
		else
		{
			const VkExtent3D& extent = renderpass.getVkExtent3D();
			viewport.x = 0;
			viewport.y = 0;
			viewport.width = static_cast<float>(extent.width);
			viewport.height = static_cast<float>(extent.height);
			viewport.minDepth = 0;
			viewport.maxDepth = static_cast<float>(extent.depth);
		}

		VkRect2D scissor{};

		if (gpi.scissor)
		{
			scissor.offset.x = static_cast<int32_t>(gpi.scissor.value()[0][0]);
			scissor.offset.y = static_cast<int32_t>(gpi.scissor.value()[0][1]);
			scissor.extent = { static_cast<uint32_t>(gpi.scissor.value()[1][0]),
							  static_cast<uint32_t>(gpi.scissor.value()[1][1]) };
		}
		else
		{
			const VkExtent3D& extent = renderpass.getVkExtent3D();

			scissor.offset = { 0, 0 };
			scissor.extent = { extent.width,
							   extent.height };
		}

		VkPipelineViewportStateCreateInfo vpsci
		{
			.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO,
			.pNext = nullptr,
			.flags = 0,
			.viewportCount = 1u,
			.pViewports = &viewport,
			.scissorCount = 1u,
			.pScissors = &scissor,
		};


		VkPipelineColorBlendStateCreateInfo cbci{};
		std::vector<VkPipelineColorBlendAttachmentState> attachments(gpi.colorBlendingState.attachments.size());
		{
			cbci.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
			cbci.pNext = nullptr;
			cbci.flags = 0;
			// ãÍì˜ÇÃçÙ
			std::memcpy(cbci.blendConstants, gpi.colorBlendingState.blendConstants.data(), sizeof(float) * 4);

			cbci.logicOpEnable = gpi.colorBlendingState.logicOp.has_value();
			if (cbci.logicOpEnable)
			{
				cbci.logicOp = static_cast<VkLogicOp>(*(gpi.colorBlendingState.logicOp));
			}

			cbci.attachmentCount = static_cast<std::uint32_t>(gpi.colorBlendingState.attachments.size());
			
			for (std::size_t i = 0; i < gpi.colorBlendingState.attachments.size(); ++i)
			{
				const auto& attachment = gpi.colorBlendingState.attachments[i];

				attachments[i].alphaBlendOp = static_cast<VkBlendOp>(attachment.alphaBlendOp);
				attachments[i].colorBlendOp = static_cast<VkBlendOp>(attachment.colorBlendOp);
				attachments[i].blendEnable = static_cast<VkBool32>(attachment.blendEnable);
				attachments[i].colorWriteMask = static_cast<VkColorComponentFlags>(attachment.colorWriteMask.bitFlag);
				attachments[i].srcColorBlendFactor = static_cast<VkBlendFactor>(attachment.srcColor);
				attachments[i].dstColorBlendFactor = static_cast<VkBlendFactor>(attachment.dstColor);
				attachments[i].srcAlphaBlendFactor = static_cast<VkBlendFactor>(attachment.srcAlpha);
				attachments[i].dstAlphaBlendFactor = static_cast<VkBlendFactor>(attachment.dstAlpha);
			}

			cbci.pAttachments = attachments.data();
		}

		VkPipelineDepthStencilStateCreateInfo dsci
		{
			.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO,
			.pNext = nullptr,
			.flags = 0,

			.depthTestEnable = static_cast<VkBool32>(gpi.depthStencilState.depthTestEnable),
			.depthWriteEnable = static_cast<VkBool32>(gpi.depthStencilState.depthWriteEnable),
			.depthCompareOp = static_cast<VkCompareOp>(gpi.depthStencilState.depthCompareOp),
			.depthBoundsTestEnable = static_cast<VkBool32>(gpi.depthStencilState.depthBoundsTestEnable),
			.stencilTestEnable = static_cast<VkBool32>(gpi.depthStencilState.stencilTestEnable),
			.front
			{
					.failOp = static_cast<VkStencilOp>(gpi.depthStencilState.front.failOp),
					.passOp = static_cast<VkStencilOp>(gpi.depthStencilState.front.passOp),
					.depthFailOp = static_cast<VkStencilOp>(gpi.depthStencilState.front.depthFailOp),
					.compareOp = static_cast<VkCompareOp>(gpi.depthStencilState.front.compareOp),
					.compareMask = gpi.depthStencilState.front.compareMask,
					.writeMask = gpi.depthStencilState.front.writeMask,
					.reference = gpi.depthStencilState.front.reference
			},
			.back
			{
					.failOp = static_cast<VkStencilOp>(gpi.depthStencilState.back.failOp),
					.passOp = static_cast<VkStencilOp>(gpi.depthStencilState.back.passOp),
					.depthFailOp = static_cast<VkStencilOp>(gpi.depthStencilState.back.depthFailOp),
					.compareOp = static_cast<VkCompareOp>(gpi.depthStencilState.back.compareOp),
					.compareMask = gpi.depthStencilState.back.compareMask,
					.writeMask = gpi.depthStencilState.back.writeMask,
					.reference = gpi.depthStencilState.back.reference
			},
			.minDepthBounds = gpi.depthStencilState.minDepthBounds,
			.maxDepthBounds = gpi.depthStencilState.maxDepthBounds,
		};

		std::vector<VkPipelineShaderStageCreateInfo> ssciVec;
		{
			ssciVec.reserve(shaderStages.size());

			for (const auto& stage : shaderStages)
			{
				auto& ssci = ssciVec.emplace_back();
				ssci.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
				ssci.pNext = nullptr;
				ssci.stage = static_cast<VkShaderStageFlagBits>(std::get<1>(stage));
				ssci.module = std::get<2>(stage);
				ssci.pName = std::get<0>(stage).data();
			}
		}

		{
			const auto& descriptorSetLayouts = bindlayout.getDescriptorSetLayouts();

			VkPipelineLayoutCreateInfo ci{};
			ci.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
			ci.setLayoutCount = static_cast<std::uint32_t>(descriptorSetLayouts.size());
			ci.pSetLayouts = descriptorSetLayouts.data();

			if (VK_FAILED(res, vkCreatePipelineLayout(mpDevice->getDevice(), &ci, nullptr, &mPipelineLayout)))
			{
				Logger::error("failed to create pipeline layout!");
				return Result(res);
			}
		}

		{  // graphics pipeline 

			VkGraphicsPipelineCreateInfo ci{};
			ci.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
			ci.stageCount = static_cast<uint32_t>(ssciVec.size());
			ci.pStages = ssciVec.data();
			ci.pInputAssemblyState = &iaci;
			ci.pVertexInputState = &visci;
			ci.pRasterizationState = &rci;
			ci.pDepthStencilState = &dsci;
			ci.pMultisampleState = &msci;
			ci.pViewportState = &vpsci;
			ci.pColorBlendState = &cbci;
			ci.pDynamicState = nullptr;
			ci.renderPass = renderpass.getVkRenderPass();
			ci.layout = mPipelineLayout;

			if (VK_FAILED(res, vkCreateGraphicsPipelines(mpDevice->getDevice(), VK_NULL_HANDLE, 1, &ci, nullptr, &mPipeline)))
			{
				Logger::error("failed to create graphics pipeline! (native result : {})", static_cast<std::int32_t>(res));
				return Result(res);
			}
		}

		return Result();
	}

}
