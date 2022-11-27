/*****************************************************************//**
 * @file   Result.hpp
 * @brief  Result�N���X�̃w�b�_�t�@�C��
 * 
 * @author ichi-raven
 * @date   November 2022
 *********************************************************************/

#ifndef HENCE_UTILITY_RESULT_HPP_
#define HENCE_UTILITY_RESULT_HPP_

#include <cstdint>

namespace Hence
{
	/**
	 * @brief  ���s���ʂ�\���^
	 */
	struct Result
	{
		/**
		 * @brief  �f�t�H���g�R���X�g���N�^�C��������
		 */
		Result() noexcept;

		/**
		 * @brief  �G���[ID�R���X�g���N�^�C���s����
		 * @param nativeError API�̃G���[ID(���O�̃G���[�Ȃ�0)
		 */
		Result(const std::int32_t nativeError) noexcept;

		/**
		 * @brief  bool�^�ϊ��I�[�o�[���[�h
		 */
		explicit operator bool() const  noexcept;

		/**
		 * @brief  �_���ے艉�Z�q�I�[�o�[���[�h
		 */
		bool operator!() const noexcept;

		Result operator=(Result other) noexcept;

		//! �����������ǂ���
		const bool	succeeded;
		//! �l�C�e�B�uAPI�̃G���[ID�C���������ꍇ��������API�ɂ��G���[�łȂ��ꍇ��0
		const std::int32_t	nativeResult;
	};
}


#endif