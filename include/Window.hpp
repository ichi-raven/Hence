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
#include "Utility/Result.hpp"
#include "Info/WindowInfo.hpp"

namespace Hence
{
	template<typename API>
	class Semaphore;

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

		Window() noexcept;

		/**
		 * @brief  �R���X�g���N�^
		 *
		 * @param device ��Ƃ���f�o�C�X
		 * @param WindowInfo �E�B���h�E�̐ݒ�
		 */
		Window(Device<API>& device, const WindowInfo& info) noexcept;

		/**
		 * @brief  �f�X�g���N�^
		 */
		~Window() noexcept;

		// �R�s�[�s��
		NONCOPYABLE(Window)

		/**
		 * @brief  ���͂��X�V����
		 */
		void updateInput() noexcept;

		/**
		 * @brief  ���̃E�B���h�E���t�H�[�J�X����Ă��邩
		 * @return �t�H�[�J�X����Ă����true
		 */
		bool focused() const noexcept;

		/** 
		 * @brief ���p�\�ȃt���[���o�b�t�@�̃C���f�b�N�X��Ԃ�(���̃t���[���o�b�t�@���g��)
		 *  
		 * @return ���̃t���[���o�b�t�@�̃C���f�b�N�X
		 */
		std::uint32_t acquireNextImage(Semaphore<API>& signalSemaphore) noexcept;

		/**
		 * @brief  �`�悪���������t���[���o�b�t�@���E�B���h�E�ɕ\������
		 * @param frameBufferIndex �`��ΏۂƂ����t���[���o�b�t�@�̃C���f�b�N�X(acquireNextImage�Ŏ擾�ł������)
		 * @param waitSemaphore ���̃t���[���o�b�t�@�ɕ`����s���Ă���R�}���h�̏I����ʒm����Z�}�t�H(�`�揈�����I����Ă��Ȃ��̂ɕ\���͂ł��Ȃ�)
		 * @return �\���ɐ����������ǂ���
		*/
		Result present(const std::uint32_t frameBufferIndex, Semaphore<API>& waitSemaphore) noexcept;

		/**
		 * @brief  ���������擾
		 * @warning ��ʂɃ��[�U���g�p����K�v�͂Ȃ�
		 *
		 * @return API���Ƃ̓�������
		 */
		Impl& getInternalImpl() noexcept;

	private:
		//using APIDevice = APITrait<API>::Device;

		//! �f�o�C�X�̓�������
		//APIDevice& mAPIDevice;
		//! ��������
		std::optional<Impl> mImpl;
	};
}

#include "../src/Window.inl"

#endif