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

#include "../../Utility/Macro.hpp"

namespace Hence
{
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
		VulkanBuffer allocate(BufferInfo bi) noexcept;
		
		VulkanImage allocate(ImageInfo ii) noexcept;

		void deallocate(VulkanBuffer& vulkanBuffer) noexcept;

		void deallocate(VulkanImage& vulkanImage) noexcept;

	private:
		VulkanDevice& mDevice;


	};
}

#endif