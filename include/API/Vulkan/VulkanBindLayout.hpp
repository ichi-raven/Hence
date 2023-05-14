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

		VulkanBindLayout(VulkanDevice* pVulkanDevice, const std::map<std::pair<uint8_t, uint8_t>, ResourceType>& bindingLayoutTable ) noexcept;
		
		template<typename... ShaderType>
		VulkanBindLayout(VulkanDevice* pVulkanDevice, const ShaderType&... shaders) noexcept
			: VulkanBindLayout(pVulkanDevice, mergeAll(shaders...))
		{}

		~VulkanBindLayout();

		const std::vector<VkDescriptorSetLayout>& getDescriptorSetLayouts() noexcept;

		const std::vector<std::uint32_t>& getBindingNums() noexcept;

	private:

		template<typename Head, typename... Tails, typename = std::is_same<Head, VulkanShader>>
		std::map<std::pair<uint8_t, uint8_t>, ResourceType> mergeAll(const Head& head, const Tails&... tails) noexcept
		{
			if constexpr (sizeof...(Tails) == 0)
			{
				return head.getResourceLayoutTable();
			}
			else
			{
				static auto table = head.getResourceLayoutTable();
				table.merge(mergeAll<Tails...>(tails...));
				return table;
			}
		}

		VulkanDevice* mpDevice;

		std::vector<VkDescriptorSetLayout> mDescriptorSetLayouts;
		std::vector<std::uint32_t> mBindingNums;
	};
}

#endif
