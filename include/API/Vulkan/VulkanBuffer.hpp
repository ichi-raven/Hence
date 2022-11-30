/*****************************************************************//**
 * @file   VulkanBuffer.hpp
 * @brief  VulkanBuffer�N���X�̃w�b�_�t�@�C��
 * 
 * @author ichi-raven
 * @date   November 2022
 *********************************************************************/
#ifndef HENCE_API_VULKAN_VULKANBUFFER_HPP_
#define HENCE_API_VULKAN_VULKANBUFFER_HPP_

#include "../../Utility/Macro.hpp"

#include <vulkan/vulkan.hpp>

namespace Hence
{
	/**
	 * @brief  Buffer�C���^�t�F�[�X��Vulkan�����N���X
	 */
	class VulkanBuffer
	{
	public:

		VulkanBuffer(VkBuffer buffer, VkDeviceMemory memory, VkDeviceSize size, VkDeviceSize offset) noexcept;

		~VulkanBuffer() noexcept;

		//VulkanBuffer& operator=(const VulkanBuffer& other) noexcept;

		//VulkanBuffer& operator=(VulkanBuffer&& other) noexcept;

		VkBuffer getVkBuffer() noexcept;

		VkDeviceMemory getVkDeviceMemory() noexcept;

		VkDeviceSize getDeviceMemorySize() const noexcept;
		
		VkDeviceSize getDeviceMemoryOffset() const noexcept;

	private:

		VkBuffer		mBuffer;
		VkDeviceMemory  mMemory;
		VkDeviceSize	mSize;
		VkDeviceSize	mOffset;
	};
}

#endif