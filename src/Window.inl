/*****************************************************************//**
 * @file   Window.inl
 * @brief  Windowクラスの実装分離ファイル
 * 
 * @author ichi-raven
 * @date   November 2022
 *********************************************************************/
#ifdef HENCE_WINDOW_HPP_

#include "../include/Semaphore.hpp"

namespace Hence
{
	template<typename API>
	Window<API>::Window() noexcept
	{

	}

	template<typename API>
	Window<API>::Window(Device<API>& device, const WindowInfo& windowInfo) noexcept
		//: mAPIDevice(device.getInternalAPIDevice())
		: mImpl(std::make_optional<Impl>(&device.getInternalAPIDevice(), windowInfo))
	{

	}

	template<typename API>
	Window<API>::~Window() noexcept
	{

	}

	template<typename API>
	void Window<API>::updateInput() noexcept 
	{
		assert(mImpl || !"invalid window! (construct with device first!)");

		mImpl->updateInput();
	}


	template<typename API>
	bool Window<API>::getKey(const Key key) const noexcept
	{
		assert(mImpl || !"invalid window! (construct with device first!)");

		return mImpl->getKey(key);
	}


	template<typename API>
	std::pair<double, double> Window<API>::getMousePos() const noexcept
	{
		assert(mImpl || !"invalid window! (construct with device first!)");

		return mImpl->getMousePos();
	}


	template<typename API>
	bool Window<API>::focused() const noexcept
	{
		assert(mImpl || !"invalid window! (construct with device first!)");

		return mImpl->focused();
	}

	template<typename API>
	std::uint32_t Window<API>::acquireNextImage(Semaphore<API>& signalSemaphore) noexcept
	{
		assert(mImpl || !"invalid window! (construct with device first!)");

		return mImpl->acquireNextImage(signalSemaphore.getInternalImpl());
	}

	template<typename API>
	Result Window<API>::present(const std::uint32_t frameBufferIndex, Semaphore<API>& waitSemaphore) noexcept
	{
		assert(mImpl || !"invalid window! (construct with device first!)");

		return mImpl->present(frameBufferIndex, waitSemaphore.getInternalImpl());
	}

	template<typename API>
	Window<API>::template Impl& Window<API>::getInternalImpl() noexcept
	{
		assert(mImpl || !"invalid window! (construct with device first!)");

		return *mImpl;
	}
}

#endif
