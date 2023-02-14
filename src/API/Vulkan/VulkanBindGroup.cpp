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

#include "../../../include/API/Vulkan/VulkanDevice.hpp"
#include "../../../include/API/Vulkan/Utility/Macro.hpp"

#include "../../../include/Utility/Result.hpp"
#include "../../../include/Utility/Logger.hpp"


namespace Hence
{
    VulkanBindGroup::VulkanBindGroup(VulkanDevice& vulkanDevice, VulkanBindLayout& vulkanBindLayout) noexcept
        : mDevice(vulkanDevice)
        , mChanged(true)
    {
        const auto& layouts = vulkanBindLayout.getDescriptorSetLayouts();

        VkDescriptorSetAllocateInfo dsai{};

        dsai.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
        dsai.pNext = nullptr;
        dsai.descriptorPool = mDevice.getDescriptorPool();
        dsai.descriptorSetCount = static_cast<std::uint32_t>(layouts.size());
        dsai.pSetLayouts = layouts.data();

        mDescriptorSets.resize(layouts.size());

        const auto& bindingNums = vulkanBindLayout.getBindingNums();

        for (const auto& bindingNum : bindingNums)
        {
            mWriteDescriptorSets.emplace_back().resize(bindingNum);
        }

        if (VK_FAILED(res, vkAllocateDescriptorSets(vulkanDevice.getDevice(), &dsai, mDescriptorSets.data())))
        {
            Logger::error("failed to allocate descriptor set! (native result : {})", static_cast<std::int32_t>(res));
        }

    }

    VulkanBindGroup::~VulkanBindGroup()
    {
        vkFreeDescriptorSets(mDevice.getDevice(), mDevice.getDescriptorPool(), static_cast<std::uint32_t>(mDescriptorSets.size()), mDescriptorSets.data());
    }

    void VulkanBindGroup::bind(std::uint32_t set, std::uint32_t binding, VulkanBuffer& buffer) noexcept
    {
        VkDescriptorBufferInfo dbi{};
        dbi.buffer = buffer.getVkBuffer();
        dbi.offset = 0;
        dbi.range = VK_WHOLE_SIZE;

        VkWriteDescriptorSet wdi{};

        wdi.sType                   = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
        wdi.pNext                   = nullptr;
        wdi.dstBinding              = binding;
        wdi.dstArrayElement         = 0;
        wdi.descriptorCount         = 1;
        wdi.descriptorType          = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
        wdi.pBufferInfo             = &dbi;
        wdi.dstSet                  = mDescriptorSets[set];

        mWriteDescriptorSets[set][binding] = wdi;

        mChanged = true;
    }

    void VulkanBindGroup::bind(std::uint32_t set, std::uint32_t binding, VulkanImage& image) noexcept
    {
        VkDescriptorImageInfo dii{};
        dii.imageView   = image.getVkImageView();
        dii.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;

        VkWriteDescriptorSet wdi{};
        wdi.sType               = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
        wdi.dstBinding          = binding;
        wdi.dstArrayElement     = 0;
        wdi.descriptorCount     = 1;
        wdi.descriptorType      = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
        wdi.pImageInfo          = &dii;
        wdi.dstSet              = mDescriptorSets[set];

        mWriteDescriptorSets[set][binding] = wdi;

        mChanged = true;
    }


    const std::vector<VkDescriptorSet>& VulkanBindGroup::getDescriptorSet() noexcept
    {
        if (mChanged)
        {
            for (const auto& wds : mWriteDescriptorSets)
            {
                vkUpdateDescriptorSets(mDevice.getDevice(),
                    static_cast<uint32_t>(wds.size()),
                    wds.data(), 0, nullptr);
            }

            mChanged = false;
        }

        return mDescriptorSets;
    }

}
