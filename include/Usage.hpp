/*****************************************************************//**
 * @file   Usage.hpp
 * @brief  Usage�N���X�y�т��̕\���Ɋւ���񋓌^�E���Ԍ^���`����w�b�_�t�@�C��
 * 
 * @author ichi-raven
 * @date   November 2022
 *********************************************************************/
#ifndef HENCE_USAGE_HPP_
#define HENCE_USAGE_HPP_

#include <cstdint>
#include <utility>

namespace Hence
{
	/**
	 * @brief  ���\�[�X�̎g�p���@�������r�b�g�t���O
	 */
	enum class UsageBit : std::int32_t
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
	 * @brief  UsageBit�̃r�b�g�a�ɂ�镡���p�r�̕\���p�N���X(���ڎg�p���邱�Ƃ͂Ȃ�)
	 */
	struct UsageFlag
	{
		UsageFlag operator| (UsageFlag other) const noexcept;

		UsageFlag operator|(UsageBit bit) const noexcept;

		const std::int32_t result{};
	};

	/**
	 * @brief  UsageBit���m�̉��Z�q�I�[�o�[���[�h
	 */
	extern UsageFlag operator|(UsageBit L, UsageBit R) noexcept;

	/**
	 * @brief  UsageFlag�pUsageBits�Ƃ̉��Z�q�I�[�o�[���[�h
	 */
	extern UsageFlag operator|(UsageBit L, UsageFlag R) noexcept;

	/**
	 * @brief  UsageFlag�����UsageBit���܂Ƃ߂Ď�舵���^(���ڍ\�z����K�v�͂Ȃ�)
	 */
	struct Usage
	{
		/**
		 * @brief  UsageBit����\�z����R���X�g���N�^
		 * @param bit UsageBit�^�̒l
		 */
		Usage(UsageBit bit) noexcept;

		/**
		 * @brief  UsageFlag����\�z����R���X�g���N�^
		 * @param flag UsageFlag�^�̒l
		 */
		Usage(UsageFlag flag) noexcept;

		//! �ŏI�I��Usage���
		const std::int32_t usage{};
	};
}

#endif
