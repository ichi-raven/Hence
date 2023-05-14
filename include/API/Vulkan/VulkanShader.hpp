#ifndef HENCE_API_VULKAN_VULKANSHADER_HPP_
#define HENCE_API_VULKAN_VULKANSHADER_HPP_

#include <vulkan/vulkan.hpp>

#include "../../Utility/Result.hpp"

#include "../../../include/Info/ResourceType.hpp"
#include "../../../include/Info/ShaderStage.hpp"
#include "../../../include/Info/Format.hpp"

#include <map>

namespace Hence
{
	class VulkanDevice;

	class VulkanShader
	{
	public:

		VulkanShader(VulkanDevice* pVulkanDevice, std::string_view path) noexcept;

		~VulkanShader() noexcept;

		//const VkPipelineShaderStageCreateInfo& getShaderStageCreateInfo() const noexcept;

		const std::map<std::pair<uint8_t, uint8_t>, ResourceType>& getResourceLayoutTable() const noexcept;

		const std::vector<Format>& getInputVariables() const noexcept;

		const std::vector<Format>& getOutputVariables() const noexcept;

		std::string_view getEntryPoint() const noexcept;

		VkShaderModule getVkShaderModule() noexcept;

		ShaderStage getShaderStage() const noexcept;

	private:
		inline Result loadShaderReflection() noexcept;

		VulkanDevice* mpDevice;

		std::vector<char> mFileData;

		std::string mEntryPoint;
		std::map<std::pair<uint8_t, uint8_t>, ResourceType> mResourceLayoutTable;
		std::vector<Format> mInputVariables;
		std::vector<Format> mOutputVariables;

		ShaderStage mShaderStage;
		VkShaderModule mShaderModule;
		//VkPipelineShaderStageCreateInfo mShaderStageCreateInfo;
	};
}

#endif