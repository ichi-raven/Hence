/*****************************************************************//**
 * @file   HelperFunctions.cpp
 * @brief  VulkanópÉwÉãÉpä÷êîÇÃíËã`
 * 
 * @author ichi-raven
 * @date   December 2022
 *********************************************************************/

#include "../../../../include/API/Vulkan/Utility/HelperFunctions.hpp"

namespace Hence
{
	Result setImageMemoryBarrier(VkCommandBuffer command, VkImage image, VkImageLayout oldLayout, VkImageLayout newLayout, VkImageAspectFlags aspectFlags) noexcept
	{
        VkImageMemoryBarrier imb{};
        imb.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
        imb.oldLayout = oldLayout;
        imb.newLayout = newLayout;
        imb.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
        imb.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
        imb.subresourceRange = { aspectFlags, 0, 1, 0, 1 };
        imb.image = image;

        // final stage that write to resource in pipelines
        VkPipelineStageFlags srcStage = VK_PIPELINE_STAGE_ALL_COMMANDS_BIT;
        // next state that write to resource in pipelines
        VkPipelineStageFlags dstStage = VK_PIPELINE_STAGE_ALL_COMMANDS_BIT;

        switch (oldLayout)
        {
        case VK_IMAGE_LAYOUT_UNDEFINED:
            imb.srcAccessMask = 0;
            break;
        case VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL:
            imb.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
            srcStage = VK_PIPELINE_STAGE_TRANSFER_BIT;
            break;
        case VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL:
            imb.srcAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
            break;
        }

        switch (newLayout)
        {
        case VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL:
            imb.dstAccessMask = VK_ACCESS_TRANSFER_READ_BIT;
            dstStage = VK_PIPELINE_STAGE_TRANSFER_BIT;
            break;
        case VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL:
            imb.dstAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
            dstStage = VK_PIPELINE_STAGE_TRANSFER_BIT;
            break;
        case VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL:
            imb.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;
            dstStage = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT;
            break;
        }

        vkCmdPipelineBarrier(command, srcStage, dstStage, 0,
            0,  // memoryBarrierCount
            nullptr,
            0,  // bufferMemoryBarrierCount
            nullptr,
            1,  // imageMemoryBarrierCount
            &imb);

        return Result();
	}
}
