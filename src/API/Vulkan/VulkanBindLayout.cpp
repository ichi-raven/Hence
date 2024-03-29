/*****************************************************************//**
 * @file   VulkanBindLayout.cpp
 * @brief  VulkanBindLayouotクラスの実装
 *
 * @author ichi-raven
 * @date   January 2023
 *********************************************************************/

#include "../../../include/API/Vulkan/VulkanBindLayout.hpp"
#include "../../../include/API/Vulkan/VulkanShader.hpp"
#include "../../../include/API/Vulkan/VulkanDevice.hpp"

#include "../../../include/API/Vulkan/Utility/Macro.hpp"

#include "../../../include/Utility/Logger.hpp"

namespace Hence
{

	VulkanBindLayout::VulkanBindLayout(VulkanDevice* pVulkanDevice, const std::map<std::pair<uint8_t, uint8_t>, ResourceType>& bindingLayoutTable) noexcept
		: mpDevice(pVulkanDevice)
	{
		assert(pVulkanDevice != nullptr || !"vulkan device is nullptr!");

		std::vector<std::vector<VkDescriptorSetLayoutBinding>> allBindings;
		allBindings.reserve(8);
		{  // HACK
			std::uint32_t nowSet = UINT32_MAX;

			for (const auto& [sb, srt] : bindingLayoutTable)
			{
				if (sb.first != nowSet)
				{
					allBindings.emplace_back();
					nowSet = sb.first;
				}

				auto&& b = allBindings.back().emplace_back();
				b.binding = sb.second;
				b.descriptorCount = 1;
				switch (srt)
				{
				case ResourceType::UniformBuffer:
					b.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
					break;

				case ResourceType::StorageBuffer:
					b.descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER;
					break;

				case ResourceType::CombinedImageSampler:
					b.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
					break;

				case ResourceType::Sampler:
					assert(!"not supported");
					break;
				}

				b.pImmutableSamplers = nullptr;
				b.stageFlags = VK_SHADER_STAGE_ALL;
			}
		}


		for (auto& binding : allBindings)
		{
			mBindingNums.emplace_back(static_cast<std::uint32_t>(binding.size()));
		}


		VkDescriptorSetLayoutCreateInfo descLayoutci{};
		descLayoutci.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
		descLayoutci.pNext = nullptr;
		for (auto& bindings : allBindings)
		{
			descLayoutci.bindingCount = static_cast<uint32_t>(bindings.size());
			descLayoutci.pBindings = bindings.data();

			mDescriptorSetLayouts.emplace_back();

			if (VK_FAILED(res, vkCreateDescriptorSetLayout(mpDevice->getDevice(), &descLayoutci, nullptr, &mDescriptorSetLayouts.back())))
			{
				Logger::error("failed to create descriptor set layout! (native error : {}", static_cast<std::int32_t>(res));
				return;
			}
		}
	}

	VulkanBindLayout::~VulkanBindLayout()
	{
		for (auto& dsl : mDescriptorSetLayouts)
		{
			vkDestroyDescriptorSetLayout(mpDevice->getDevice(), dsl, nullptr);
		}
	}

	const std::vector<VkDescriptorSetLayout>& VulkanBindLayout::getDescriptorSetLayouts() noexcept
	{
		return mDescriptorSetLayouts;
	}

	const std::vector<std::uint32_t>& VulkanBindLayout::getBindingNums() noexcept
	{
		return mBindingNums;
	}

}
