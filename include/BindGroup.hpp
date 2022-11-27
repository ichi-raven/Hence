/*****************************************************************//**
 * @file   BindGroup.hpp
 * @brief  BindGroup�N���X�̃w�b�_�t�@�C��
 *
 * @author ichi-raven
 * @date   November 2022
 *********************************************************************/

#ifndef HENCE_BINDGROUP_HPP_
#define HENCE_BINDGROUP_HPP_

#include "API.hpp"
#include "Utility/Macro.hpp"
#include "Utility/Result.hpp"


#include "Device.hpp"
#include "Buffer.hpp"
#include "Image.hpp"
#include "Shader.hpp"

namespace Hence
{
	/**
	 * @brief �V�F�[�_���ŎQ�Ƃ���VRAM���\�[�X�̕R�Â�������
	 * @tparam API �o�b�N�G���h�Ɏg�p����API�^(API.hpp���Œ�`����Ă���)
	 */
	template<typename API>
	class BindGroup
	{
	public:
		// ���������^(��ʂɃ��[�U���g�p����K�v�͂Ȃ�)
		using Impl = APITrait<API>::BindGroupImpl;

		/**
		 * @brief  �R���X�g���N�^
		 *
		 * @param device ��Ƃ���f�o�C�X
		 * @param shader ���̃V�F�[�_�̃��C�A�E�g����R�Â��郊�\�[�X�^�����肷��
		 */
		BindGroup(Device<API>& device, const Shader<API>& shader) noexcept;

		/**
		 * @brief  �f�X�g���N�^
		 *
		 */
		~BindGroup() noexcept;

		// �R�s�[�s��
		NONCOPYABLE(BindGroup)

		/**
		 * @brief  �o�b�t�@���w�肵���X���b�g�ɕR�Â���
		 *
		 * @param slot �X���b�g(�V�F�[�_����bind�̒l)
		 * @param buffer �R�Â���o�b�t�@
		 * @return ����
		 */
		Result bind(uint8_t slot, const Buffer<API>& buffer) noexcept;

		/**
		 * @brief  �摜�f�[�^���w�肵���X���b�g�ɕR�Â���
		 *
		 * @param slot �X���b�g(�V�F�[�_����bind�̒l)
		 * @param image �R�Â���摜�f�[�^
		 * @return ����
		 */
		Result bind(uint8_t slot, const Image<API>& image) noexcept;

		/** 
		 * @brief  ���������擾
		 * @warning ��ʂɃ��[�U���g�p����K�v�͂Ȃ�
		 *  
		 * @return API���Ƃ̓�������
		 */
		const Impl& getInternalImpl() const;

	private:
		using APIDevice = APITrait<API>::Device;

		//! �f�o�C�X�̓�������
		APIDevice& mAPIDevice;
		//! ��������
		Impl mImpl;
	};
}

#include "../src/BindGroup.inl"

#endif
