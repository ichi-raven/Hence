/*****************************************************************//**
 * @file   VulkanBindGroup.cpp
 * @brief  VulkanBindGroupƒNƒ‰ƒX‚ÌŽÀ‘•
 * 
 * @author ichi-raven
 * @date   February 2023
 *********************************************************************/

#include "../../../include/API/Vulkan/VulkanBindGroup.hpp"

#include "../../../include/API/Vulkan/VulkanBindLayout.hpp"
#include "../../../include/API/Vulkan/VulkanBuffer.hpp"
#include "../../../include/API/Vulkan/VulkanImage.hpp"
#include "../../../include/API/Vulkan/VulkanSampler.hpp"

#include "../../../include/API/Vulkan/VulkanDevice.hpp"
#include "../../../include/API/Vulkan/Utility/Macro.hpp"

#include "../../../include/Utility/Result.hpp"
#include "../../../include/Utility/Logger.hpp"


namespace Hence
{
    VulkanBindGroup::VulkanBindGroup(VulkanDevice* pVulkanDevice, VulkanBindLayout& vulkanBindLayout) noexcept
        : mpDevice(pVulkanDevice)
        , mChanged(true)
    {
        assert(pVulkanDevice != nullptr || !"vulkan device is nullptr!");

        const auto& layouts = vulkanBindLayout.getDescriptorSetLayouts();

        VkDescriptorSetAllocateInfo dsai
        {
            .sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO,
            .pNext = nullptr,
            .descriptorPool = mpDevice->getDescriptorPool(),
            .descriptorSetCount = static_cast<std::uint32_t>(layouts.size()),
            .pSetLayouts = layouts.data()
        };

        mDescriptorSets.resize(layouts.size());

        const auto& bindingNums = vulkanBindLayout.getBindingNums();

        for (const auto& bindingNum : bindingNums)
        {
            mDescriptorSetInfos.emplace_back().resize(bindingNum);
            mWriteDescriptorSets.emplace_back().resize(bindingNum);
        }

        if (VK_FAILED(res, vkAllocateDescriptorSets(mpDevice->getDevice(), &dsai, mDescriptorSets.data())))
        {
            Logger::error("failed to allocate descriptor set! (native result : {})", static_cast<std::int32_t>(res));
        }

    }

    VulkanBindGroup::~VulkanBindGroup()
    {
        vkFreeDescriptorSets(mpDevice->getDevice(), mpDevice->getDescriptorPool(), static_cast<std::uint32_t>(mDescriptorSets.size()), mDescriptorSets.data());
    }

    void VulkanBindGroup::bind(std::uint32_t set, std::uint32_t binding, VulkanBuffer& buffer) noexcept
    {
        VkDescriptorBufferInfo dbi
        {
            .buffer = buffer.getVkBuffer(),
            .offset = 0,
            .range = VK_WHOLE_SIZE
        };

        mDescriptorSetInfos[set][binding] = dbi;
        
        VkWriteDescriptorSet wdi
        {
            .sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET,
            .pNext = nullptr,
            .dstSet = mDescriptorSets[set],
            .dstBinding = binding,
            .dstArrayElement = 0,
            .descriptorCount = 1,
            .descriptorType = buffer.getDescriptorType(),
            .pBufferInfo = &std::get<0>(mDescriptorSetInfos[set][binding])
        };

        mWriteDescriptorSets[set][binding] = wdi;

        mChanged = true;
    }

    void VulkanBindGroup::bind(std::uint32_t set, std::uint32_t binding, VulkanImage& image, VulkanSampler& sampler) noexcept
    {
        VkDescriptorImageInfo dii
        {
            .sampler        = sampler.getVkSampler(),
            .imageView      = image.getVkImageView(),
            .imageLayout    = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL,
        };

        mDescriptorSetInfos[set][binding] = dii;
        
        VkWriteDescriptorSet wdi
        {
            .sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET,
            .pNext = nullptr,
            .dstSet = mDescriptorSets[set],
            .dstBinding = binding,
            .dstArrayElement = 0,
            .descriptorCount = 1,
            .descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,
            .pImageInfo = &std::get<1>(mDescriptorSetInfos[set][binding])
        };

        mWriteDescriptorSets[set][binding] = wdi;

        mChanged = true;
    }


    const std::vector<VkDescriptorSet>& VulkanBindGroup::getDescriptorSets() noexcept
    {
        if (mChanged)
        {
            for (const auto& wds : mWriteDescriptorSets)
            {
                vkUpdateDescriptorSets(mpDevice->getDevice(),
                    static_cast<uint32_t>(wds.size()),
                    wds.data(), 0, nullptr);
            }

            mChanged = false;
        }

        return mDescriptorSets;
    }

}
