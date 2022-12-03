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
	VulkanImage::VulkanImage(VulkanDevice& vulkanDevice, VkImage image, VkDeviceMemory memory, VkImageView imageView, VkExtent3D extent, std::uint32_t sizeOfChannel)
		: mDevice(vulkanDevice)
        , mImage(image)
		, mMemory(memory)
		, mImageView(imageView)
        , mExtent(extent)
        , mSizeOfChannel(sizeOfChannel)
	{}

	VulkanImage::~VulkanImage()
	{

	}

	Result VulkanImage::writeImage(void* ptr, std::uint32_t size)
	{
        const auto vkDevice = mDevice.getDevice();

        size_t imageSize = mExtent.width * mExtent.height * mExtent.depth * ;
        
        VkBuffer        stagingBuffer = VK_NULL_HANDLE;
        VkDeviceMemory  stagingMemory = VK_NULL_HANDLE;
        {
            
            VkBufferCreateInfo ci{};
            ci.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
            ci.size = imageSize;
            ci.usage = VK_BUFFER_USAGE_TRANSFER_SRC_BIT;

            if (VK_FAILED(res, vkCreateBuffer(vkDevice, &ci, nullptr, &stagingBuffer)))
            {
                Logger::error("failed to create staging buffer to copy image data!");
                return Result(static_cast<std::int32_t>(res));
            }
            

            {
                VkMemoryRequirements reqs{};
                vkGetBufferMemoryRequirements(vkDevice, stagingBuffer, &reqs);
                VkMemoryAllocateInfo ai{};
                ai.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
                ai.allocationSize = reqs.size;
                ai.memoryTypeIndex = mDevice.getMemoryTypeIndex(reqs.memoryTypeBits, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT);

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

            void* p;
            
            if (VK_FAILED(res, vkMapMemory(vkDevice, stagingMemory, 0, VK_WHOLE_SIZE, 0, &ptr)))
            {
                Logger::error("failed to map staging buffer memory!");
                return Result(static_cast<std::int32_t>(res));
            }

            std::memcpy(p, ptr, imageSize);
            vkUnmapMemory(vkDevice, stagingMemory);
        }

        VkBufferImageCopy copyRegion{};
        copyRegion.imageExtent = { static_cast<uint32_t>(io.extent.width),
                                  static_cast<uint32_t>(io.extent.height),
                                  static_cast<uint32_t>(io.extent.depth) };
        copyRegion.imageSubresource = { VK_IMAGE_ASPECT_COLOR_BIT, 0, 0, 1 };
        VkCommandBuffer command;
        {
            VkCommandBufferAllocateInfo ai{};
            ai.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
            ai.commandBufferCount = 1;
            ai.commandPool = mDevice.getCommandPool();
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

        VkSubmitInfo submitInfo{};
        submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
        submitInfo.commandBufferCount = 1;
        submitInfo.pCommandBuffers = &command;
        vkQueueSubmit(mDevice.getDeviceQueue(), 1, &submitInfo, VK_NULL_HANDLE);

        // end copying
        vkDeviceWaitIdle(vkDevice);
        vkFreeCommandBuffers(vkDevice, mDevice.getCommandPool(), 1, &command);

        // release staging buffer
        vkFreeMemory(vkDevice, stagingMemory, nullptr);
        vkDestroyBuffer(vkDevice, stagingBuffer, nullptr);


		return Result();
	}

	//VulkanImage& VulkanImage::operator=(VulkanImage&& other) noexcept
	//{
	//	mImage		= std::move(other.mImage);
	//	mMemory		= std::move(other.mMemory);
	//	mImageView	= std::move(other.mImageView);

	//	return *this;
	//}

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
}
