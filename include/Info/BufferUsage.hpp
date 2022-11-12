/*****************************************************************//**
 * @file   BufferUsage.hpp
 * @brief  BufferUsage�N���X�y�т��̕\���Ɋւ���񋓌^�E���Ԍ^���`����w�b�_�t�@�C��
 * 
 * @author ichi-raven
 * @date   November 2022
 *********************************************************************/
#ifndef HENCE_INFO_BUFFERUSAGE_HPP_
#define HENCE_INFO_BUFFERUSAGE_HPP_

#include <cstdint>
#include <utility>
#include <type_traits>

namespace Hence
{
	/**
 * @brief  �摜���\�[�X�̎g�p���@�������r�b�g�t���O
 */
	enum class BufferUsageBit : std::int32_t
	{
		Vertex,
		Index,
		Uniform,
	};

	/**
	 * @brief  BufferUsageBit�̃r�b�g�a�ɂ�镡���p�r�̕\���p�N���X(���ڎg�p���邱�Ƃ͂Ȃ�)
	 */
	struct BufferUsageFlag
	{
		/**
		 * @brief  �_���a�p���Z�q�I�[�o�[���[�h
		 */
		BufferUsageFlag operator| (UsageFlag other) const noexcept;

		/**
		 * @brief  �_���a�p���Z�q�I�[�o�[���[�h(UsageBit��)
		 */
		BufferUsageFlag operator|(UsageBit bit) const noexcept;

		const std::int32_t result{};
	};

	/**
	 * @brief  BufferUsageBit���m�̉��Z�q�I�[�o�[���[�h
	 */
	extern BufferUsageFlag operator|(BufferUsageBit L, BufferUsageBit R) noexcept;

	/**
	 * @brief  BufferUsageFlag�pUsageBits�Ƃ̉��Z�q�I�[�o�[���[�h
	 */
	extern BufferUsageFlag operator|(BufferUsageBit L, BufferUsageFlag R) noexcept;

	/**
	 * @brief  UsageFlag�����UsageBit���܂Ƃ߂Ď�舵���^(���ڍ\�z����K�v�͂Ȃ�)
	 */
	struct BufferUsage
	{
		/**
		 * @brief  BufferUsageBit����\�z����R���X�g���N�^
		 * @param bit BufferUsageBit�^�̒l
		 */
		BufferUsage(BufferUsageBit bit) noexcept;

		/**
		 * @brief  BufferUsageFlag����\�z����R���X�g���N�^
		 * @param flag BufferUsageFlag�^�̒l
		 */
		BufferUsage(BufferUsageFlag flag) noexcept;

		/**
		 * @brief  ������Z�q�I�[�o�[���[�h(BufferUsageBit�^)
		 * @param bit BufferUsageBit�^�̒l
		 */
		BufferUsageFlag operator=(BufferUsageBit bit) noexcept;

		/**
		 * @brief  ������Z�q�I�[�o�[���[�h(BufferUsageFlag�^)
		 * @param flag BufferUsageFlag�^�̒l
		 */
		BufferUsageFlag operator=(BufferUsageFlag flag) noexcept;

		//! �ŏI�I��Usage���
		const std::int32_t usage{};
	};
}

#endif