/*****************************************************************//**
 * @file   VulkanBuffer.cpp
 * @brief  VulkanBufferƒNƒ‰ƒX‚ÌŽÀ‘•
 * 
 * @author ichi-raven
 * @date   November 2022
 *********************************************************************/

#include "../../../include/API/Vulkan/VulkanBuffer.hpp"



namespace Hence
{
	VulkanBuffer::VulkanBuffer(VkBuffer buffer, VkDeviceMemory memory, VkDeviceSize size, VkDeviceSize offset) noexcept
		: mBuffer(buffer)
		, mMemory(memory)
		, mSize(size)
		, mOffset(offset)
	{

	}

	VulkanBuffer::~VulkanBuffer() noexcept
	{

	}

	VkBuffer VulkanBuffer::getVkBuffer() noexcept
	{
		return mBuffer;
	}

	VkDeviceMemory VulkanBuffer::getVkDeviceMemory() noexcept
	{
		return mMemory;
	}

	VkDeviceSize VulkanBuffer::getDeviceMemorySize() const noexcept
	{
		return mSize;
	}

	VkDeviceSize VulkanBuffer::getDeviceMemoryOffset() const noexcept
	{
		return mOffset;
	}
}
