/*****************************************************************//**
 * @file   ColorComponent.hpp
 * @brief  ColorComponent�N���X�̃w�b�_�t�@�C���N���X�y�т��̕\���Ɋւ���񋓌^�E���Ԍ^���`����w�b�_�t�@�C��
 * 
 * @author ichi-raven
 * @date   March 2023
 *********************************************************************/
#ifndef HENCE_INFO_COLORCOMPONENT_HPP_
#define HENCE_INFO_COLORCOMPONENT_HPP_

#include <cstdint>
#include <utility>
#include <type_traits>

namespace Hence
{
	/**
	 * @brief  �g�p����F�`���l���������r�b�g�t���O
	 */
	enum class ColorComponentBit : std::int32_t
	{
		R = 0x00000001,
		G = 0x00000002,
		B = 0x00000004,
		A = 0x00000008,
	};

	/**
	 * @brief  ColorComponentBit�̃r�b�g�a�ɂ�镡���p�r�̕\���p�N���X(���ڎg�p���邱�Ƃ͂Ȃ�)
	 */
	struct ColorComponentFlag
	{
		ColorComponentFlag(const std::int32_t res);

		/**
		 * @brief  �_���a�p���Z�q�I�[�o�[���[�h
		 */
		ColorComponentFlag operator| (ColorComponentFlag other) const noexcept;

		/**
		 * @brief  �_���a�p���Z�q�I�[�o�[���[�h(UsageBit��)
		 */
		ColorComponentFlag operator|(ColorComponentBit bit) const noexcept;

		const std::int32_t result{};
	};

	/**
	 * @brief  ColorComponentBit���m�̉��Z�q�I�[�o�[���[�h
	 */
	extern ColorComponentFlag operator|(ColorComponentBit L, ColorComponentBit R) noexcept;

	/**
	 * @brief  ColorComponentFlag�pUsageBits�Ƃ̉��Z�q�I�[�o�[���[�h
	 */
	extern ColorComponentFlag operator|(ColorComponentBit L, ColorComponentFlag R) noexcept;

	/**
	 * @brief  UsageFlag�����UsageBit���܂Ƃ߂Ď�舵���^(���ڍ\�z����K�v�͂Ȃ�)
	 */
	struct ColorComponent
	{
		/**
		 * @brief  ColorComponentBit����\�z����R���X�g���N�^
		 * @param bit ColorComponentBit�^�̒l
		 */
		ColorComponent(ColorComponentBit bit) noexcept;

		/**
		 * @brief  ColorComponentFlag����\�z����R���X�g���N�^
		 * @param flag ColorComponentFlag�^�̒l
		 */
		ColorComponent(ColorComponentFlag flag) noexcept;

		/**
		 * @brief  ������Z�q�I�[�o�[���[�h(ColorComponentBit�^)
		 * @param bit ColorComponentBit�^�̒l
		 */
		ColorComponentFlag operator=(ColorComponentBit bit) noexcept;

		/**
		 * @brief  ������Z�q�I�[�o�[���[�h(ColorComponentFlag�^)
		 * @param flag ColorComponentFlag�^�̒l
		 */
		ColorComponentFlag operator=(ColorComponentFlag flag) noexcept;

		/**
		 * @brief  ����usage���܂�ł��邩���肷��
		 * @param  check �܂�ł��邩���肷��ColorComponentBit
		 * @return �܂�ł����true
		 */
		bool contains(ColorComponentBit checkBit) const noexcept;

		//! �ŏI�I�Ȓl
		std::int32_t bitFlag{};
	};
}

#endif
