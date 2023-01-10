#ifndef HENCE_API_VULKAN_VULKANSHADER_HPP_
#define HENCE_API_VULKAN_VULKANSHADER_HPP_

#include <vulkan/vulkan.hpp>

namespace Hence
{
	class VulkanShader
	{
	public:
		VulkanShader(VulkanDevice& vulkanDevice, std::string_view path)

	private:
		std::vector<char> mFileData;

	};
}

#endif