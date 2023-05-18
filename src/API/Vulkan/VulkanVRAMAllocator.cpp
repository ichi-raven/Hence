/*****************************************************************//**
 * @file   VulkanVRAMAllocator.cpp
 * @brief  VulkanVRAMAllocatorクラスの実装
 * 
 * @author ichi-raven
 * @date   November 2022
 *********************************************************************/

#include "../../../include/API/Vulkan/VulkanDevice.hpp"
#include "../../../include/API/Vulkan/VulkanVRAMAllocator.hpp"
#include "../../../include/API/Vulkan/VulkanBuffer.hpp"
#include "../../../include/API/Vulkan/VulkanImage.hpp"

#include "../../../include/API/Vulkan/Utility/Macro.hpp"
#include "../../../include/API/Vulkan/Utility/HelperFunctions.hpp"

#include "../../../include/Utility/Logger.hpp"

namespace Hence
{
	VulkanVRAMAllocator::VulkanVRAMAllocator(VulkanDevice* pVulkanDevice) noexcept
		: mpDevice(pVulkanDevice)
	{
        assert(pVulkanDevice != nullptr || !"vulkan device is nullptr!");
	}

	VulkanVRAMAllocator::~VulkanVRAMAllocator() noexcept
	{

	}

    Either<VulkanBuffer, Result> VulkanVRAMAllocator::allocate(BufferInfo bufferInfo) noexcept
    {
        // VkBuffer
        VkBuffer buffer = VK_NULL_HANDLE;
        {
            VkBufferCreateInfo ci{};
            ci.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
            ci.pNext = nullptr;

            ci.usage = static_cast<VkBufferUsageFlags>(bufferInfo.usage.usage);

            if (ci.usage == 0)
            {
                Logger::error("buffer usage is not descibed!");
                return Result(0);
            }

            if (bufferInfo.memorySize == 0)
            {
                Logger::error("cannot create empty size buffer!");
                return Result(0);
            }

            ci.size = bufferInfo.memorySize;

            if (VK_FAILED(res, vkCreateBuffer(mpDevice->getDevice(), &ci, nullptr, &buffer)))
            {
                return Either<VulkanBuffer, Result>(Result(res));
            }

        }

        // VkDeviceMemory
        VkDeviceMemory memory = VK_NULL_HANDLE;
        {
            VkMemoryPropertyFlagBits fb{};

            if (bufferInfo.hostVisible)
            {
                fb = static_cast<VkMemoryPropertyFlagBits>(
                    VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT |
                    VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);
            }
            else
            {
                fb = VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT;
            }

            VkMemoryRequirements reqs;
            vkGetBufferMemoryRequirements(mpDevice->getDevice(), buffer, &reqs);
            VkMemoryAllocateInfo ai{};
            ai.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
            ai.allocationSize = reqs.size;
            ai.memoryTypeIndex = mpDevice->getMemoryTypeIndex(reqs.memoryTypeBits, fb);

            // VRAM割り当て
            {
                if (VK_FAILED(res, vkAllocateMemory(mpDevice->getDevice(), &ai, nullptr, &memory)))
                {
                    Logger::error("failed to allocate VkDeviceMemory to the VkBuffer!");
                    return Either<VulkanBuffer, Result>(Result(static_cast<std::int32_t>(res)));
                }
            }

            // bufferと紐づけ
            if (VK_FAILED(res, vkBindBufferMemory(mpDevice->getDevice(), buffer, memory, 0)))
            {
                Logger::error("failed to bind VkDeviceMemory to the VkBuffer!");
                return Either<VulkanBuffer, Result>(Result(static_cast<std::int32_t>(res)));
            }
        }

        VkDeviceSize offset = 0;

        return Either<VulkanBuffer, Result>(VulkanBuffer(mpDevice, buffer, memory, static_cast<VkDeviceSize>(bufferInfo.memorySize), offset));
        //return VulkanBuffer(mDevice, buffer, memory, static_cast<VkDeviceSize>(bufferInfo.memorySize), offset);
    }

    Either<VulkanImage, Result> VulkanVRAMAllocator::allocate(ImageInfo imageInfo) noexcept
	{
        VkImageCreateInfo ci{};

        VkExtent3D extent
        {
            .width  = imageInfo.width,
            .height = imageInfo.height,
            .depth  = imageInfo.depth
        };

        // VkImage
        VkImage image = VK_NULL_HANDLE;
        {
            ci.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
            ci.pNext = nullptr;
            ci.format = static_cast<VkFormat>(imageInfo.format);

            switch (imageInfo.dimension)
            {
            case Dimension::two:
                ci.imageType = VK_IMAGE_TYPE_2D;
                ci.extent = { uint32_t(imageInfo.width), uint32_t(imageInfo.height), 1 };
                if (imageInfo.depth != 1)
                {
                    Logger::warn("invalid depth param is ignored");
                }
                break;
            case Dimension::three:
                ci.imageType = VK_IMAGE_TYPE_3D;
                ci.extent = { uint32_t(imageInfo.width), uint32_t(imageInfo.height), uint32_t(imageInfo.depth) };
                break;
            default:
                Logger::error("invalid dimention of image!");
                return Either<VulkanImage, Result>(Result(0));
                break;
            }

            ci.usage = static_cast<VkImageUsageFlags>(imageInfo.usage.usage);
            ci.usage |= VK_IMAGE_USAGE_TRANSFER_DST_BIT;

            ci.arrayLayers = 1;
            ci.mipLevels = 1;
            ci.samples = VK_SAMPLE_COUNT_1_BIT;
            ci.tiling = VK_IMAGE_TILING_OPTIMAL;
            ci.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;

            if (VK_FAILED(res, vkCreateImage(mpDevice->getDevice(), &ci, nullptr, &image)))
            {
                Logger::error("failed to create VkImage!");
                return Either<VulkanImage, Result>(Result(static_cast<std::int32_t>(res)));
            }
        }

        // VkDeviceMemory
        VkDeviceMemory memory = VK_NULL_HANDLE;
        {
            VkMemoryRequirements reqs;
            vkGetImageMemoryRequirements(mpDevice->getDevice(), image, &reqs);
            VkMemoryAllocateInfo ai{};
            ai.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
            ai.allocationSize = reqs.size;
            // メモリタイプ決定
            VkMemoryPropertyFlagBits fb;
            if (imageInfo.hostVisible)
            {
                fb = VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT;
            }
            else
            {
                fb = static_cast<VkMemoryPropertyFlagBits>(
                    VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT |
                    VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);
            }

            ai.memoryTypeIndex = mpDevice->getMemoryTypeIndex(reqs.memoryTypeBits, fb);
            // VRAM割り当て
            if (VK_FAILED(res, vkAllocateMemory(mpDevice->getDevice(), &ai, nullptr, &memory)))
            {
                Logger::error("failed to allocate VkDeviceMemory to the VkImage!");
                return Either<VulkanImage, Result>(Result(static_cast<std::int32_t>(res)));
            }

            // imageと紐づけ
            if (VK_FAILED(res, vkBindImageMemory(mpDevice->getDevice(), image, memory, 0)))
            {
                Logger::error("failed to bind VkDeviceMemory to the VkImage!");
                return Either<VulkanImage, Result>(Result(static_cast<std::int32_t>(res)));
            }
        }

        // VkImageView
        VkImageView imageView = VK_NULL_HANDLE;
        VkImageAspectFlags aspectFlag = VK_IMAGE_ASPECT_COLOR_BIT;
        {
            VkImageViewCreateInfo ci{};
            ci.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;

            switch (imageInfo.dimension)
            {
            case Dimension::two:
                ci.viewType = VK_IMAGE_VIEW_TYPE_2D;
                break;
            case Dimension::three:
                ci.viewType = VK_IMAGE_VIEW_TYPE_3D;
                break;
            default:
                Logger::error("invalid image dimension!");
                return Result(0);
                break;
            }

            ci.image = image;
            ci.format = static_cast<VkFormat>(imageInfo.format);
            ci.components = 
            {
                VK_COMPONENT_SWIZZLE_R,
                VK_COMPONENT_SWIZZLE_G,
                VK_COMPONENT_SWIZZLE_B,
                VK_COMPONENT_SWIZZLE_A,
            };

            if (imageInfo.usage.contains(ImageUsageBit::DepthStencilAttachment))
            {
                aspectFlag = VK_IMAGE_ASPECT_DEPTH_BIT | VK_IMAGE_ASPECT_STENCIL_BIT;
            }

            ci.subresourceRange = { aspectFlag, 0, 1, 0, 1 };

            if (VK_FAILED(res, vkCreateImageView(mpDevice->getDevice(), &ci, nullptr, &imageView)))
            {
                Logger::error("failed to create vkImageView!");
                return Either<VulkanImage, Result>(Result(res));
            }
        }

        // VkImageLayoutを設定
        {
            VkImageLayout layout = VK_IMAGE_LAYOUT_UNDEFINED;
            if (imageInfo.usage.contains(ImageUsageBit::Sampled))
            {
                layout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
            }

            if (imageInfo.usage.contains(ImageUsageBit::ColorAttachment))
            {
                layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
            }

            if (imageInfo.usage.contains(ImageUsageBit::DepthStencilAttachment))
            {
                layout = VK_IMAGE_LAYOUT_DEPTH_ATTACHMENT_OPTIMAL;
            }

            if (layout != VK_IMAGE_LAYOUT_UNDEFINED)
            {

                VkCommandBuffer command;
                {
                    VkCommandBufferAllocateInfo ai{};
                    ai.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
                    ai.commandBufferCount = 1;
                    ai.commandPool = mpDevice->getCommandPool();
                    ai.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
                    vkAllocateCommandBuffers(mpDevice->getDevice(), &ai, &command);
                }

                VkCommandBufferBeginInfo commandBI{};
                commandBI.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
                vkBeginCommandBuffer(command, &commandBI);
                
                if (FAILED(res, setImageMemoryBarrier(command, image, VK_IMAGE_LAYOUT_UNDEFINED, layout, aspectFlag)))
                {
                    return Either<VulkanImage, Result>(std::move(res));
                }
                
                vkEndCommandBuffer(command);

                VkSubmitInfo submitInfo{};
                submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
                submitInfo.commandBufferCount = 1;
                submitInfo.pCommandBuffers = &command;
                vkQueueSubmit(mpDevice->getDeviceQueue(), 1, &submitInfo, VK_NULL_HANDLE);

                // レイアウト遷移終了
                vkDeviceWaitIdle(mpDevice->getDevice());
                vkFreeCommandBuffers(mpDevice->getDevice(), mpDevice->getCommandPool(), 1, &command);
            }
            else
            {
                Logger::warn("undefined layout image was created");
            }
        }

        //VulkanImage rtn(mDevice, image, memory, imageView, extent, imageInfo.sizeOfChannel);

        return Either<VulkanImage, Result>(std::move(VulkanImage(mpDevice, image, memory, imageView, ci.format, extent, imageInfo.sizeOfChannel)));
	}

	void VulkanVRAMAllocator::deallocate(VulkanBuffer& vulkanBuffer) noexcept
	{
        const auto vkDevice = mpDevice->getDevice();

        vkQueueWaitIdle(mpDevice->getDeviceQueue());

        vkDestroyBuffer(vkDevice, vulkanBuffer.getVkBuffer(), nullptr);
        // !割り当て方法を変える場合はここに注意
        vkFreeMemory(vkDevice, vulkanBuffer.getVkDeviceMemory(), nullptr);
	}

	void VulkanVRAMAllocator::deallocate(VulkanImage& vulkanImage) noexcept
	{
        const auto vkDevice = mpDevice->getDevice();

        vkQueueWaitIdle(mpDevice->getDeviceQueue());

        vkDestroyImageView(vkDevice, vulkanImage.getVkImageView(), nullptr);
        vkDestroyImage(vkDevice, vulkanImage.getVkImage(), nullptr);
        // !割り当て方法を変える場合はここに注意
        vkFreeMemory(vkDevice, vulkanImage.getVkDeviceMemory(), nullptr);
	}
}


