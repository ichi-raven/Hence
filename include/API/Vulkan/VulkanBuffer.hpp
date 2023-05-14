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

#include "VulkanDevice.hpp"

#include <vulkan/vulkan.hpp>

namespace Hence
{
	/**
	 * @brief  BufferインタフェースのVulkan実装クラス
	 */
	class VulkanBuffer
	{
	public:

		VulkanBuffer(VulkanDevice* pVulkanDevice, VkBuffer buffer, VkDeviceMemory memory, VkDeviceSize size, VkDeviceSize offset) noexcept;

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