#ifndef HENCE_API_VULKAN_VULKANGRAPHICSPIPELINE_HPP_
#define HENCE_API_VULKAN_VULKANGRAPHICSPIPELINE_HPP_

#include <vulkan/vulkan.hpp>

#include "../../Info/ShaderStage.hpp"
#include "../../Info/GraphicsPipelineInfo.hpp"

#include "../../Utility/Result.hpp"

namespace Hence
{

	class VulkanDevice;
	class VulkanRenderPass;
	class VulkanBindLayout;
	class VulkanShader;

	template<typename T>
	concept VulkanShaderType = std::same_as<T, VulkanShader>;

	class VulkanGraphicsPipeline
	{
	public:

		template <VulkanShaderType... VulkanShaderTypes>
		VulkanGraphicsPipeline(VulkanDevice& device, const GraphicsPipelineInfo& gpi, VulkanRenderPass& renderpass, VulkanBindLayout& bindLayout, VulkanShaderTypes... shaders) noexcept
			: mDevice(device)
		{
			std::vector<std::tuple<std::string_view, ShaderStage, VkShaderModule>> modules
			{
				std::make_tuple(shaders.getEntryPoint(), shaders.getgetVkShaderStage(), shaders.getVkShaderModule())...
			};

		}

		~VulkanGraphicsPipeline() noexcept;

		VkPipeline getVkPipeline() noexcept;

	private:

		inline Result createPipeline(const GraphicsPipelineInfo& gpi, VkRenderPass& renderpass, VulkanBindLayout& bindlayout, const std::vector<std::tuple<std::string_view, ShaderStage, VkShaderModule>>& shaderStages) noexcept;

		VulkanDevice& mDevice;

		VkPipeline mPipeline;
	};
}

#endif