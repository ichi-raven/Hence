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
#include "../../Utility/Logger.hpp"

#include "../../../include/API/Vulkan/Utility/Macro.hpp"


#include "VulkanDevice.hpp"

#include <vulkan/vulkan.hpp>

#include <functional>

namespace Hence
{
	/**
	 * @brief  Buffer�C���^�t�F�[�X��Vulkan�����N���X
	 */
	class VulkanBuffer
	{
	public:

		VulkanBuffer(VulkanDevice* pVulkanDevice, VkBuffer buffer, VkDeviceMemory memory, VkDeviceSize size, VkDeviceSize offset, VkDescriptorType descriptorType) noexcept;

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
			return writeBuffer(reinterpret_cast<const void*>(data.data()), data.size());
		}

		template <typename DataType>
		Result readData(const std::function<void(DataType* ptr, std::size_t size)>& readFunc) noexcept
		{
			void* mappedMemory = nullptr;
			const auto vkDevice = mpDevice->getDevice();

			if (VK_FAILED(res, vkMapMemory(vkDevice, mMemory, mOffset, mSize, 0, &mappedMemory)))
			{
				Logger::error("failed to map buffer device memory!");
				return Result(static_cast<std::int32_t>(res));
			}

			readFunc(reinterpret_cast<DataType*>(mappedMemory), mSize / sizeof(DataType));
			
			vkUnmapMemory(vkDevice, mMemory);

			return Result();
		}

		VkBuffer getVkBuffer() noexcept;

		VkDeviceMemory getVkDeviceMemory() noexcept;

		VkDeviceSize getDeviceMemorySize() const noexcept;
		
		VkDeviceSize getDeviceMemoryOffset() const noexcept;

		VkDescriptorType getDescriptorType() const noexcept;

	private:

		Result writeBuffer(const void* ptr, std::size_t size) noexcept;

		VulkanDevice*	mpDevice;

		VkBuffer		mBuffer;
		VkDeviceMemory  mMemory;
		VkDeviceSize	mSize;
		VkDeviceSize	mOffset;

		VkDescriptorType mDescriptorType;
	};
}

#endif