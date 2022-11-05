/*****************************************************************//**
 * @file   Window.hpp
 * @brief  Window�N���X�̃w�b�_�t�@�C��
 * 
 * @author ichi-raven
 * @date   November 2022
 *********************************************************************/
#ifndef HENCE_WINDOW_HPP_
#define HENCE_WINDOW_HPP_

#include "API.hpp"
#include "Utility/Macro.hpp"

namespace Hence
{
	/**
	 * @brief  �E�B���h�E��\��
	 * @tparam API �o�b�N�G���h�Ɏg�p����API�^(API.hpp���Œ�`����Ă���)
	 */
	template<typename API>
	class Window
	{
	public:
		// ���������^(��ʂɃ��[�U���g�p����K�v�͂Ȃ�)
		using Impl = APITrait<API>::WindowImpl;

		/**
		 * @brief  �R���X�g���N�^
		 *
		 * @param device ��Ƃ���f�o�C�X
		 * @param WindowInfo �E�B���h�E�̐ݒ�
		 */
		Window(Device<API>& device, const WindowInfo& info);

		/**
		 * @brief  �f�X�g���N�^
		 */
		~Window();

		// �R�s�[�s��
		NONCOPYABLE(Window)

		/**
		 * @brief  ���͂��X�V����
		 */
		void updateInput();

		/**
		 * @brief  ���̃E�B���h�E���t�H�[�J�X����Ă��邩
		 * @return �t�H�[�J�X����Ă����true
		 */
		bool focused() const;

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

#endif