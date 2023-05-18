/*****************************************************************//**
 * @file   VulkanBindGroup.hpp
 * @brief  VulkanBindGroupクラスのヘッダファイル
 * 
 * @author ichi-raven
 * @date   February 2023
 *********************************************************************/
#ifndef HENCE_API_VULKAN_VULKANBINDGROUP_HPP_
#define HENCE_API_VULKAN_VULKANBINDGROUP_HPP_

#include <vulkan/vulkan.hpp>

#include <variant>

namespace Hence
{
	class VulkanDevice;
	class VulkanBindLayout;
	class VulkanBuffer;
	class VulkanImage;
	class VulkanSampler;

	class VulkanBindGroup
	{
	public:

		VulkanBindGroup(VulkanDevice* pVulkanDevice, VulkanBindLayout& vulkanBindLayout) noexcept;

		~VulkanBindGroup();

		void bind(std::uint32_t set, std::uint32_t binding, VulkanBuffer& buffer) noexcept;

		void bind(std::uint32_t set, std::uint32_t binding, VulkanImage& image, VulkanSampler& sampler) noexcept;

		const std::vector<VkDescriptorSet>& getDescriptorSets() noexcept;

	private:
		
		using DescriptorInfo		= std::variant<VkDescriptorBufferInfo, VkDescriptorImageInfo>; 

		VulkanDevice* mpDevice;

		bool mChanged;
		std::vector<std::vector<DescriptorInfo>>		mDescriptorSetInfos;
		std::vector<std::vector<VkWriteDescriptorSet>>	mWriteDescriptorSets;
		std::vector<VkDescriptorSet>					mDescriptorSets;
	};
}

#endif