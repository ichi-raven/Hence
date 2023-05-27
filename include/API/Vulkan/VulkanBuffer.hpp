/*****************************************************************//**
 * @file   VulkanBuffer.hpp
 * @brief  VulkanBufferクラスのヘッダファイル
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
	 * @brief  BufferインタフェースのVulkan実装クラス
	 */
	class VulkanBuffer
	{
	public:

		VulkanBuffer(VulkanDevice* pVulkanDevice, VkBuffer buffer, VkDeviceMemory memory, VkDeviceSize size, VkDeviceSize offset, VkDescriptorType descriptorType) noexcept;

		~VulkanBuffer() noexcept;

		VulkanBuffer(VulkanBuffer&& other) noexcept;

		VulkanBuffer& operator=(VulkanBuffer&& other) noexcept;

		/**
		 * @brief バッファにデータを書き込む(ステージング及びコマンド実行コストがかかる)
		 * @tparam DataType 書き込むデータの型
		 * @param data 書き込むデータのArrayProxy(配列/array/vector/initializer_list)
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