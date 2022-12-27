/*****************************************************************//**
 * @file   VRAMAllocator.hpp
 * @brief  VRAMAllocator�N���X�̃w�b�_�t�@�C��
 * 
 * @author ichi-raven
 * @date   November 2022
 *********************************************************************/
#ifndef HENCE_VRAMALLOCATOR_HPP_
#define HENCE_VRAMALLOCATOR_HPP_

#include "API.hpp"
#include "Utility/Macro.hpp"
#include "Info/BufferInfo.hpp"
#include "Info/ImageInfo.hpp"

namespace Hence
{
	// �O���錾
	template<typename API>
	class Device;

	// �O���錾
	template<typename API>
	class Buffer;

	// �O���錾
	template<typename API>
	class Image;

	/**
	 * @brief  VRAM���\�[�X�̊��蓖�Ă��Ǘ�����N���X
	 * @tparam API �o�b�N�G���h�Ɏg�p����API�^(API.hpp���Œ�`����Ă���)
	 */
	template<typename API>
	//requires VRAMAllocatorConcept<APITrait<API>::VRAMAllocatorImpl>
	class VRAMAllocator
	{
	public:
		using Impl = APITrait<API>::VRAMAllocatorImpl;

		/**
		 * @brief  �R���X�g���N�^
		 * @param device ��Ƃ���f�o�C�X
		 */
		VRAMAllocator(Device<API>& device) noexcept;

		/**
		 * @brief  �f�X�g���N�^
		 */
		~VRAMAllocator() noexcept;

		// �R�s�[�s��
		NONCOPYABLE(VRAMAllocator);

		Impl& getInternalImpl();

		///**
		// * @brief  �o�b�t�@�̊��蓖�Ă��s��
		// * @param bci ���蓖�Ă�o�b�t�@�̏��
		// */
		//Buffer<API>& allocate(const BufferInfo& bci) noexcept;

		///**
		// * @brief  �摜�f�[�^�̊��蓖�Ă��s��
		// * @param ici ���蓖�Ă�摜�f�[�^�̏��
		// */
		//Image<API>& allocate(const ImageInfo& ici) noexcept;

		///**
		// * @brief  �o�b�t�@���������
		// * @param buffer �������o�b�t�@
		// */
		//void deallocate(Buffer<API>& buffer) noexcept;

		///**
		// * @brief  �摜�f�[�^���������
		// * @param image �������摜�f�[�^
		// */
		//void deallocate(Image<API>& image) noexcept;

	private:
		using APIDevice = APITrait<API>::Device;

		//! �f�o�C�X�̓�������
		APIDevice& mAPIDevice;
		//! ��������
		Impl mImpl;
	};

}

#include "../src/VRAMAllocator.inl"

#endif
