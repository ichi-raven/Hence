/*****************************************************************//**
 * @file   VulkanVRAMAllocator.hpp
 * @brief  VulkanVRAMAllocatorクラスのヘッダファイル
 * 
 * @author ichi-raven
 * @date   November 2022
 *********************************************************************/
#ifndef HENCE_API_VULKAN_VULKANVRAMALLOCATOR_HPP_
#define HENCE_API_VULKAN_VULKANVRAMALLOCATOR_HPP_


#include "../../Info/BufferInfo.hpp"
#include "../../Info/ImageInfo.hpp"

#include "../../Utility/Result.hpp"
#include "../../Utility/Either.hpp"
#include "../../Utility/Macro.hpp"

namespace Hence
{
	class VulkanDevice;
	class VulkanBuffer;
	class VulkanImage;

	/**
	 * @brief  VRAMAllocatorのVulkan実装
	 */
	class VulkanVRAMAllocator
	{
	public:

		/**
		 * @brief  コンストラクタ
		 * @param vulkanDevice VulkanのDeviceクラス
		 */
		VulkanVRAMAllocator(VulkanDevice* pVulkanDevice) noexcept;

		/**
		 * @brief  デストラクタ
		 */
		~VulkanVRAMAllocator() noexcept;

		// コピー不可
		NONCOPYABLE(VulkanVRAMAllocator)

		/**
		 * @brief  バッファの割り当てを行う
		 */
		Either<VulkanBuffer, Result> allocate(BufferInfo bufferInfo) noexcept;
		
		Either<VulkanImage, Result> allocate(ImageInfo imageInfo) noexcept;

		void deallocate(VulkanBuffer& vulkanBuffer) noexcept;

		void deallocate(VulkanImage& vulkanImage) noexcept;

	private:

		VulkanDevice* mpDevice;

	};
}

#endif