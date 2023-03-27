/*****************************************************************//**
 * @file   Window.inl
 * @brief  Windowクラスの実装分離ファイル
 * 
 * @author ichi-raven
 * @date   November 2022
 *********************************************************************/
#ifdef HENCE_WINDOW_HPP_

namespace Hence
{
	template<typename API>
	Window<API>::Window(Device<API>& device, const WindowInfo& windowInfo) noexcept
		: mAPIDevice(device.getInternalAPIDevice())
		, mImpl(mAPIDevice, windowInfo)
	{

	}

	template<typename API>
	Window<API>::~Window() noexcept
	{

	}

	template<typename API>
	void Window<API>::updateInput() noexcept 
	{
		mImpl.updateInput();
	}

	template<typename API>
	bool Window<API>::focused() const noexcept
	{
		return mImpl.focused();
	}

	template<typename API>
	Window<API>::template Impl& Window<API>::getInternalImpl() noexcept
	{
		return mImpl;
	}
}

#endif
