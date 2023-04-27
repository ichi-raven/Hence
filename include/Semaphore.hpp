/*****************************************************************//**
 * @file   Semaphore.hpp
 * @brief  Semaphore�N���X�̃w�b�_�t�@�C��
 * 
 * @author ichi-raven
 * @date   April 2023
 *********************************************************************/
#ifndef HENCE_SEMAPHORE_HPP_
#define HENCE_SEMAPHORE_HPP_

#include "API.hpp"
#include "Utility/Macro.hpp"

namespace Hence
{
	// �O���錾
	template<typename API>
	class Device;

	template<typename API>
	class Semaphore
	{
	public:
		// ���������^(��ʂɃ��[�U���g�p����K�v�͂Ȃ�)
		using Impl = APITrait<API>::SemaphoreImpl;

		Semaphore(Device<API>& device);

		~Semaphore();

		NONCOPYABLE(Semaphore)

	private:
		using APIDevice = APITrait<API>::Device;

		APIDevice& mDevice;
		Impl mImpl;
	};
}

#endif
