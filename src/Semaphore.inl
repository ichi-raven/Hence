/*****************************************************************//**
 * @file   Semaphore.inl
 * @brief  Semaphoreクラスの実装展開ファイル
 * 
 * @author ichi-raven
 * @date   April 2023
 *********************************************************************/
#ifdef HENCE_SEMAPHORE_HPP_

#include "../include/Device.hpp"

namespace Hence
{
	template<typename API>
	Semaphore<API>::Semaphore() noexcept
	{

	}

	template<typename API>
	Semaphore<API>::Semaphore(Device<API>& device) noexcept
		//: mAPIDevice(device.getInternalAPIDevice())
		: mImpl(std::make_optional<Impl>(&device.getInternalAPIDevice()))
	{

	}

	template<typename API>
	Semaphore<API>::~Semaphore() noexcept
	{

	}

	template<typename API>
	Semaphore<API>::Semaphore(Semaphore<API>&& src) noexcept
		//: mAPIDevice(src.mAPIDevice)
		: mImpl(std::move(src.mImpl))
	{

	}

	template<typename API>
	Semaphore<API>& Semaphore<API>::operator=(Semaphore<API>&& src) noexcept
	{
		//mAPIDevice = src.mAPIDevice;
		mImpl = std::move(src.mImpl);

		return *this;
	}

	template<typename API>
	Semaphore<API>::template Impl& Semaphore<API>::getInternalImpl() noexcept
	{
		assert(mImpl || !"invalid semaphore! (construct with device first!)");

		return *mImpl;
	}
}

#endif
