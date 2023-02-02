#ifndef HENCE_API_VULKAN_VULKANSHADER_HPP_
#define HENCE_API_VULKAN_VULKANSHADER_HPP_

#include <vulkan/vulkan.hpp>

#include "../../Utility/Result.hpp"

#include <map>

namespace Hence
{
	class VulkanDevice;

	class VulkanShader
	{
	public:

		VulkanShader(VulkanDevice& vulkanDevice, std::string_view path) noexcept;

		const VkPipelineShaderStageCreateInfo& getShaderStageCreateInfo() const noexcept;

		const std::map<std::uint8_t, 

	private:
		inline Result createShaderModule();

		std::vector<char> mFileData;

	};
}

#endif