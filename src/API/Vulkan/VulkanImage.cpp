/*****************************************************************//**
 * @file   VulkanImage.cpp
 * @brief  VulkanImageƒNƒ‰ƒX‚ÌŽÀ‘•
 * 
 * @author ichi-raven
 * @date   November 2022
 *********************************************************************/

#include "../../../include/Utility/Logger.hpp"

#include "../../../include/API/Vulkan/VulkanImage.hpp"
#include "../../../include/API/Vulkan/Utility/Macro.hpp"
#include "../../../include/API/Vulkan/Utility/HelperFunctions.hpp"

namespace Hence
{
	VulkanImage::VulkanImage(VulkanDevice* pVulkanDevice, VkImage image, VkDeviceMemory memory, VkImageView imageView, VkFormat format, const VkExtent3D& extent, std::uint32_t sizeOfChannel) noexcept
		: mpDevice(pVulkanDevice)
        , mImage(image)
		, mMemory(memory)
		, mImageView(imageView)
        , mFormat(format)
        , mExtent(extent)
        , mSizeOfChannel(sizeOfChannel)
	{
        assert(pVulkanDevice != nullptr || !"vulkan device is nullptr!");
    }

	VulkanImage::~VulkanImage() noexcept
	{
        mImage      = VK_NULL_HANDLE;
        mMemory     = VK_NULL_HANDLE;
        mImageView  = VK_NULL_HANDLE;
	}

    VulkanImage::VulkanImage(VulkanImage&& other) noexcept
        : mpDevice(other.mpDevice)
    {
        mImage          = std::move(other.mImage);
        mMemory         = std::move(other.mMemory);
        mImageView      = std::move(other.mImageView);
        mFormat         = other.mFormat;
        mExtent         = other.mExtent;
        mSizeOfChannel  = other.mSizeOfChannel;

        other.mImage = VK_NULL_HANDLE;
        other.mMemory = VK_NULL_HANDLE;
        other.mImageView = VK_NULL_HANDLE;
    }

    VulkanImage& VulkanImage::operator=(VulkanImage&& other) noexcept
    {
        mImage          = std::move(other.mImage);
        mMemory         = std::move(other.mMemory);
        mImageView      = std::move(other.mImageView);
        mFormat         = other.mFormat;
        mExtent         = other.mExtent;
        mSizeOfChannel  = other.mSizeOfChannel;

        other.mImage = VK_NULL_HANDLE;
        other.mMemory = VK_NULL_HANDLE;
        other.mImageView = VK_NULL_HANDLE;

        return *this;
    }

	Result VulkanImage::writeImage(const void* ptr, std::uint32_t size)
	{
        const auto vkDevice = mpDevice->getDevice();

        // ‚±‚ê‚ð‚Ç‚¤‚â‚Á‚ÄŽó‚¯Žæ‚é‚©‚ª–â‘è

        const std::size_t imageSize = 
            static_cast<size_t>(mExtent.width) * mExtent.height * mExtent.depth * mSizeOfChannel;
        
        VkBuffer        stagingBuffer = VK_NULL_HANDLE;
        VkDeviceMemory  stagingMemory = VK_NULL_HANDLE;

        {
            
            VkBufferCreateInfo ci
            {
                .sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
                .pNext = nullptr,
                .flags = 0,
                .size  = imageSize,
                .usage = VK_BUFFER_USAGE_TRANSFER_SRC_BIT
            };

            if (VK_FAILED(res, vkCreateBuffer(vkDevice, &ci, nullptr, &stagingBuffer)))
            {
                Logger::error("failed to create staging buffer to copy image data!");
                return Result(static_cast<std::int32_t>(res));
            }
            

            {
                VkMemoryRequirements reqs
                {
                    .size           = imageSize,
                    .alignment      = 4,
                    .memoryTypeBits = 0 // temporary
                };

                vkGetBufferMemoryRequirements(vkDevice, stagingBuffer, &reqs);
                VkMemoryAllocateInfo ai
                {
                    .sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
                    .allocationSize = reqs.size,
                    .memoryTypeIndex = mpDevice->getMemoryTypeIndex(reqs.memoryTypeBits, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT)
                };

                if (VK_FAILED(res, vkAllocateMemory(vkDevice, &ai, nullptr, &stagingMemory)))
                {
                    Logger::error("failed to allocate staging buffer memory!");
                    return Result(static_cast<std::int32_t>(res));
                }
                

                if (VK_FAILED(res, vkBindBufferMemory(vkDevice, stagingBuffer, stagingMemory, 0)))
                {
                    Logger::error("failed to bind staging buffer memory!");
                    return Result(static_cast<std::int32_t>(res));
                }
            }

            void* pDst = nullptr;
            
            if (VK_FAILED(res, vkMapMemory(vkDevice, stagingMemory, 0, VK_WHOLE_SIZE, 0, &pDst)))
            {
                Logger::error("failed to map staging buffer memory!");
                return Result(static_cast<std::int32_t>(res));
            }
            else
            {
                std::memcpy(pDst, ptr, imageSize);
                vkUnmapMemory(vkDevice, stagingMemory);
            }

        }

        VkBufferImageCopy copyRegion{};
        copyRegion.imageExtent = 
        {
            static_cast<uint32_t>(mExtent.width),
            static_cast<uint32_t>(mExtent.height),
            static_cast<uint32_t>(mExtent.depth) 
        };

        copyRegion.imageSubresource = { VK_IMAGE_ASPECT_COLOR_BIT, 0, 0, 1 };
        VkCommandBuffer command;
        {
            VkCommandBufferAllocateInfo ai{};
            ai.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
            ai.commandBufferCount = 1;
            ai.commandPool = mpDevice->getCommandPool();
            ai.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
            vkAllocateCommandBuffers(vkDevice, &ai, &command);
        }

        VkCommandBufferBeginInfo commandBI{};
        commandBI.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
        vkBeginCommandBuffer(command, &commandBI);
        setImageMemoryBarrier(command, mImage, VK_IMAGE_LAYOUT_UNDEFINED,
            VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL);
        vkCmdCopyBufferToImage(command, stagingBuffer, mImage,
            VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, 1, &copyRegion);

        setImageMemoryBarrier(command, mImage,
            VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
            VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);
        vkEndCommandBuffer(command);

        VkSubmitInfo submitInfo
        {
            .sType = VK_STRUCTURE_TYPE_SUBMIT_INFO,
            .pNext = nullptr,
            .commandBufferCount = 1,
            .pCommandBuffers = &command
        };

        vkQueueSubmit(mpDevice->getDeviceQueue(), 1, &submitInfo, VK_NULL_HANDLE);

        // end copying
        vkDeviceWaitIdle(vkDevice);
        vkFreeCommandBuffers(vkDevice, mpDevice->getCommandPool(), 1, &command);

        // release staging buffer
        vkFreeMemory(vkDevice, stagingMemory, nullptr);
        vkDestroyBuffer(vkDevice, stagingBuffer, nullptr);


		return Result();
	}


	VkImage VulkanImage::getVkImage() noexcept
	{
		return mImage;
	}

	VkDeviceMemory VulkanImage::getVkDeviceMemory() noexcept
	{
		return mMemory;
	}

	VkImageView VulkanImage::getVkImageView() noexcept
	{
		return mImageView;
	}

    const VkExtent3D& VulkanImage::getVkExtent() noexcept
    {
        return mExtent;
    }

    VkFormat VulkanImage::getVkFormat() const noexcept
    {
        return mFormat;
    }

}
