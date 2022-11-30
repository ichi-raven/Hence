/*****************************************************************//**
 * @file   VulkanBuffer.cpp
 * @brief  VulkanBufferクラスの実装
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

	//VulkanBuffer& VulkanBuffer::operator=(VulkanBuffer&& other) noexcept
	//{
	//	mBuffer		= std::move(other.mBuffer);
	//	mMemory		= std::move(other.mMemory);
	//	mSize		= std::move(other.mSize);
	//	mOffset		= std::move(other.mOffset);

	//	return *this;
	//}


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
