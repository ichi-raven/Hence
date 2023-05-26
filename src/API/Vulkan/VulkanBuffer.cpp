/*****************************************************************//**
 * @file   VulkanBuffer.cpp
 * @brief  VulkanBufferƒNƒ‰ƒX‚ÌŽÀ‘•
 * 
 * @author ichi-raven
 * @date   November 2022
 *********************************************************************/

#include "../../../include/Utility/Logger.hpp"

#include "../../../include/API/Vulkan/VulkanBuffer.hpp"
#include "../../../include/API/Vulkan/Utility/Macro.hpp"

#include <cstdlib>

namespace Hence
{
	VulkanBuffer::VulkanBuffer(VulkanDevice* pVulkanDevice, VkBuffer buffer, VkDeviceMemory memory, VkDeviceSize size, VkDeviceSize offset) noexcept
		: mpDevice(pVulkanDevice)
		, mBuffer(buffer)
		, mMemory(memory)
		, mSize(size)
		, mOffset(offset)
	{
		assert(pVulkanDevice != nullptr || !"vulkan device is nullptr!");
	}

	VulkanBuffer::~VulkanBuffer() noexcept
	{
		mBuffer = VK_NULL_HANDLE;
		mMemory = VK_NULL_HANDLE;
	}

	VulkanBuffer::VulkanBuffer(VulkanBuffer&& other) noexcept
		: mpDevice(other.mpDevice)
	{
		mBuffer = std::move(other.mBuffer);
		mMemory = std::move(other.mMemory);
		mSize	= std::move(other.mSize);
		mOffset = std::move(other.mOffset);

		other.mBuffer = VK_NULL_HANDLE;
		other.mMemory = VK_NULL_HANDLE;
	}

	VulkanBuffer& VulkanBuffer::operator=(VulkanBuffer&& other) noexcept
	{
		mBuffer		= std::move(other.mBuffer);
		mMemory		= std::move(other.mMemory);
		mSize		= std::move(other.mSize);
		mOffset		= std::move(other.mOffset);

		other.mBuffer = VK_NULL_HANDLE;
		other.mMemory = VK_NULL_HANDLE;

		return *this;
	}

	Result VulkanBuffer::writeBuffer(const void* ptr, std::size_t size) noexcept
	{
		void* mappedMemory = nullptr;
		const auto vkDevice = mpDevice->getDevice();

		if (VK_FAILED(res, vkMapMemory(vkDevice, mMemory, mOffset, mSize, 0, &mappedMemory)))
		{
			Logger::error("failed to map buffer device memory!");
			return Result(static_cast<std::int32_t>(res));
		}

		std::memcpy(mappedMemory, ptr, mSize);
		vkUnmapMemory(vkDevice, mMemory);

		return Result();
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
