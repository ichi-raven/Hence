/*****************************************************************//**
 * @file   ImageUsage.hpp
 * @brief  ImageUsage�N���X�y�т��̕\���Ɋւ���񋓌^�E���Ԍ^���`����w�b�_�t�@�C��
 * 
 * @author ichi-raven
 * @date   November 2022
 *********************************************************************/
#ifndef HENCE_INFO_IMAGEUSAGE_HPP_
#define HENCE_INFO_IMAGEUSAGE_HPP_

#include <cstdint>
#include <utility>
#include <type_traits>

namespace Hence
{
	/**
	 * @brief  �摜���\�[�X�̎g�p���@�������r�b�g�t���O
	 */
	enum class ImageUsageBit : std::int32_t
	{
		// �]����
		TransferSRC = 0x00000001,
		// �]����
		TransferDST = 0x00000002,
		// �V�F�[�_���\�[�X
		Sampled = 0x00000004,
		// �C�ӂ̃^�C�~���O�ł�RW������
		Storage = 0x00000008,
		// �J���[�^�[�Q�b�g�Ƃ��Ă̕`���
		ColorAttachment = 0x00000010,
		// �f�v�X�X�e���V���^�[�Q�b�g�Ƃ��Ă̕`���
		DepthStencilAttachment = 0x00000020,
		//// 
		//TransientAttachment = 0x00000040,
		//// 
		//InputAttachment = 0x00000080,
	};

	/**
	 * @brief  ImageUsageBit�̃r�b�g�a�ɂ�镡���p�r�̕\���p�N���X(���ڎg�p���邱�Ƃ͂Ȃ�)
	 */
	struct ImageUsageFlag
	{
		/**
		 * @brief  �_���a�p���Z�q�I�[�o�[���[�h
		 */
		ImageUsageFlag operator| (UsageFlag other) const noexcept;

		/**
		 * @brief  �_���a�p���Z�q�I�[�o�[���[�h(UsageBit��)
		 */
		ImageUsageFlag operator|(UsageBit bit) const noexcept;

		const std::int32_t result{};
	};

	/**
	 * @brief  ImageUsageBit���m�̉��Z�q�I�[�o�[���[�h
	 */
	extern ImageUsageFlag operator|(ImageUsageBit L, ImageUsageBit R) noexcept;

	/**
	 * @brief  ImageUsageFlag�pUsageBits�Ƃ̉��Z�q�I�[�o�[���[�h
	 */
	extern ImageUsageFlag operator|(ImageUsageBit L, ImageUsageFlag R) noexcept;

	/**
	 * @brief  UsageFlag�����UsageBit���܂Ƃ߂Ď�舵���^(���ڍ\�z����K�v�͂Ȃ�)
	 */
	struct ImageUsage
	{
		/**
		 * @brief  ImageUsageBit����\�z����R���X�g���N�^
		 * @param bit ImageUsageBit�^�̒l
		 */
		ImageUsage(ImageUsageBit bit) noexcept;

		/**
		 * @brief  ImageUsageFlag����\�z����R���X�g���N�^
		 * @param flag ImageUsageFlag�^�̒l
		 */
		ImageUsage(ImageUsageFlag flag) noexcept;

		/**
		 * @brief  ������Z�q�I�[�o�[���[�h(ImageUsageBit�^)
		 * @param bit ImageUsageBit�^�̒l
		 */
		ImageUsageFlag operator=(ImageUsageBit bit) noexcept;

		/**
		 * @brief  ������Z�q�I�[�o�[���[�h(ImageUsageFlag�^)
		 * @param flag ImageUsageFlag�^�̒l
		 */
		ImageUsageFlag operator=(ImageUsageFlag flag) noexcept;

		//! �ŏI�I��Usage���
		const std::int32_t usage{};
	};
}

#endif
