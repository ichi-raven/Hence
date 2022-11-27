/*****************************************************************//**
 * @file   VulkanVRAMAllocator.hpp
 * @brief  VulkanVRAMAllocator�N���X�̃w�b�_�t�@�C��
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
	class VulkanBuffer;
	class VulkanImage;

	/**
	 * @brief  VRAMAllocator��Vulkan����
	 */
	class VulkanVRAMAllocator
	{
	public:

		/**
		 * @brief  �R���X�g���N�^
		 * @param vulkanDevice Vulkan��Device�N���X
		 */
		VulkanVRAMAllocator(VulkanDevice& vulkanDevice) noexcept;

		/**
		 * @brief  �f�X�g���N�^
		 */
		~VulkanVRAMAllocator() noexcept;

		// �R�s�[�s��
		NONCOPYABLE(VulkanVRAMAllocator);

		/**
		 * @brief  �o�b�t�@�̊��蓖�Ă��s��
		 */
		Either<VulkanBuffer, Result> allocate(BufferInfo bufferInfo) noexcept;
		
		Either<VulkanImage, Result> allocate(ImageInfo imageInfo) noexcept;

		void deallocate(VulkanBuffer& vulkanBuffer) noexcept;

		void deallocate(VulkanImage& vulkanImage) noexcept;

	private:
		std::uint32_t getMemoryTypeIndex(std::uint32_t requestBits, VkMemoryPropertyFlags requestProps) const;

		Result setImageMemoryBarrier(VkCommandBuffer command, VkImage image, VkImageLayout oldLayout,
			VkImageLayout newLayout,
			VkImageAspectFlags aspectFlags);


		VulkanDevice& mDevice;

	};
}

#endif