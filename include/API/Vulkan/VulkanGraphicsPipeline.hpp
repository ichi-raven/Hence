/*****************************************************************//**
 * @file   VulkanGraphicsPipeline.hpp
 * @brief  VulkanGraphicsPipelineクラスのヘッダファイル
 * 
 * @author ichi-raven
 * @date   April 2023
 *********************************************************************/
#ifndef HENCE_API_VULKAN_VULKANGRAPHICSPIPELINE_HPP_
#define HENCE_API_VULKAN_VULKANGRAPHICSPIPELINE_HPP_

#include <vulkan/vulkan.hpp>

#include "../../Info/ShaderStage.hpp"
#include "../../Info/Format.hpp"
#include "../../Info/GraphicsPipelineInfo.hpp"

#include "../../Utility/Result.hpp"

#include "VulkanShader.hpp"

namespace Hence
{

	class VulkanDevice;
	class VulkanRenderPass;
	class VulkanBindLayout;

	template<typename T>
	concept VulkanShaderType = std::same_as<T, VulkanShader>;

	class VulkanGraphicsPipeline
	{
	public:

		template <VulkanShaderType... VulkanShaderTypes>
		VulkanGraphicsPipeline(VulkanDevice* pVulkanDevice, const GraphicsPipelineInfo& gpi, VulkanRenderPass& renderpass, VulkanBindLayout& bindLayout, VulkanShaderTypes&... shaders) noexcept
			: mpDevice(pVulkanDevice)
			, mPipelineLayout(VK_NULL_HANDLE)
			, mPipeline(VK_NULL_HANDLE)
		{
			assert(pVulkanDevice != nullptr || !"vulkan device is nullptr!");

			std::vector<std::tuple<std::string_view, ShaderStage, VkShaderModule>> modules
			{
				std::make_tuple(shaders.getEntryPoint(), shaders.getShaderStage(), shaders.getVkShaderModule())...
			};

			createPipeline(gpi, getInputVariables(shaders...), renderpass, bindLayout, modules);

		}

		~VulkanGraphicsPipeline() noexcept;

		VkPipeline getVkPipeline() noexcept;

		VkPipelineLayout getVkPipelineLayout() noexcept;

	private:

		Result createPipeline(const GraphicsPipelineInfo& gpi, const std::vector<Format>& inputVars, VulkanRenderPass& renderpass, VulkanBindLayout& bindlayout, const std::vector<std::tuple<std::string_view, ShaderStage, VkShaderModule>>& shaderStages) noexcept;

		template<VulkanShaderType Head, VulkanShaderType... Tails>
		const std::vector<Format>& getInputVariables(const Head& head, const Tails&... tails)
		{
			
			if (head.getShaderStage() == ShaderStage::Vertex)
			{
				return head.getInputVariables();
			}
			else
			{
				if constexpr (sizeof...(Tails) > 0)
				{
					getInputVariables(tails...);
				}
				else
				{
					assert(!"no vertex shader!");
					return head.getInputVariables();
				}
			}

			return head.getInputVariables();
		}

		VulkanDevice* mpDevice;

		VkPipelineLayout mPipelineLayout;
		VkPipeline mPipeline;
	};
}

#endif