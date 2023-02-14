/*****************************************************************//**
 * @file   VulkanBindLayout.hpp
 * @brief  VulkanBindLayoutクラスのヘッダファイル
 * 
 * @author ichi-raven
 * @date   December 2022
 *********************************************************************/
#ifndef HENCE_API_VULKAN_VULKANBINDLAYOUT_HPP_
#define HENCE_API_VULKAN_VULKANBINDLAYOUT_HPP_

#include "../../Info/Format.hpp"

#include "../../Info/ResourceType.hpp"

#include <vulkan/vulkan.hpp>

#include <map>
#include <utility>

namespace Hence
{
	class VulkanDevice;

	class VulkanShader;

	class VulkanBindLayout
	{
	public:

		VulkanBindLayout(VulkanDevice& vulkanDevice, const std::map<std::pair<uint8_t, uint8_t>, ResourceType>& bindingLayoutTable ) noexcept;
		
		VulkanBindLayout(VulkanDevice& vulkanDevice, const VulkanShader& shader) noexcept;

		const std::vector<VkDescriptorSetLayout>& getDescriptorSetLayouts() noexcept;

		const std::vector<std::uint32_t>& getBindingNums() noexcept;

	private:
		std::vector<VkDescriptorSetLayout> mDescriptorSetLayouts;
		std::vector<std::uint32_t> mBindingNums;
	};
}

#endif
