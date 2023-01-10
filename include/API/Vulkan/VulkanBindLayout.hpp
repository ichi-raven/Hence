/*****************************************************************//**
 * @file   VulkanBindLayout.hpp
 * @brief  VulkanBindLayoutクラスのヘッダファイル
 * 
 * @author ichi-raven
 * @date   December 2022
 *********************************************************************/
#ifndef HENCE_API_VULKAN_VULKANBINDLAYOUT_HPP_
#define HENCE_API_VULKAN_VULKANBINDLAYOUT_HPP_

#include "../../Utility/ArrayProxy.hpp"

#include <vulkan/vulkan.hpp>

namespace Hence
{
	class VulkanShader;

	class VulkanBindLayout
	{
	public:

		VulkanBindLayout(const VulkanShader& shader) noexcept;

		VulkanBindLayout(const ArrayProxy<uint8_t> bufferBinding, const ArrayProxy<uint8_t> imageBinding, const ArrayProxy<uint8_t> samplerBinding) noexcept;

		VkDescriptorSetLayout getDescriptorSetLayout() noexcept;

	private:

		VkDescriptorSetLayout mDescriptorSetLayout;
	};
}

#endif
