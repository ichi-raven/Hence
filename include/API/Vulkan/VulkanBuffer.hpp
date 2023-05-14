/*****************************************************************//**
 * @file   VulkanBuffer.hpp
 * @brief  VulkanBuffer�N���X�̃w�b�_�t�@�C��
 * 
 * @author ichi-raven
 * @date   November 2022
 *********************************************************************/
#ifndef HENCE_API_VULKAN_VULKANBUFFER_HPP_
#define HENCE_API_VULKAN_VULKANBUFFER_HPP_

#include "../../Utility/ArrayProxy.hpp"
#include "../../Utility/Result.hpp"

#include "VulkanDevice.hpp"

#include <vulkan/vulkan.hpp>

namespace Hence
{
	/**
	 * @brief  Buffer�C���^�t�F�[�X��Vulkan�����N���X
	 */
	class VulkanBuffer
	{
	public:

		VulkanBuffer(VulkanDevice* pVulkanDevice, VkBuffer buffer, VkDeviceMemory memory, VkDeviceSize size, VkDeviceSize offset) noexcept;

		~VulkanBuffer() noexcept;

		VulkanBuffer(VulkanBuffer&& other) noexcept;

		VulkanBuffer& operator=(VulkanBuffer&& other) noexcept;

		/**
		 * @brief �o�b�t�@�Ƀf�[�^����������(�X�e�[�W���O�y�уR�}���h���s�R�X�g��������)
		 * @tparam DataType �������ރf�[�^�̌^
		 * @param data �������ރf�[�^��ArrayProxy(�z��/array/vector/initializer_list)
		 */
		template <typename DataType>
		Result writeData(const ArrayProxy<DataType> data) noexcept
		{
			return writeBuffer(data.data(), data.size());
		}

		VkBuffer getVkBuffer() noexcept;

		VkDeviceMemory getVkDeviceMemory() noexcept;

		VkDeviceSize getDeviceMemorySize() const noexcept;
		
		VkDeviceSize getDeviceMemoryOffset() const noexcept;

	private:

		inline Result writeBuffer(void* ptr, std::size_t size) noexcept;

		VulkanDevice*	mpDevice;

		VkBuffer		mBuffer;
		VkDeviceMemory  mMemory;
		VkDeviceSize	mSize;
		VkDeviceSize	mOffset;
	};
}

#endif