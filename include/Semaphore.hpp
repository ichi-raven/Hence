/*****************************************************************//**
 * @file   Semaphore.hpp
 * @brief  Semaphoreクラスのヘッダファイル
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
	// 前方宣言
	template<typename API>
	class Device;

	template<typename API>
	class Semaphore
	{
	public:
		// 内部実装型(一般にユーザが使用する必要はない)
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
