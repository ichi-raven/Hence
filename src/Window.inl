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
	Window<API>::Window(Device<API>& device, const WindowInfo& windowInfo)
		: mAPIDevice(device.getInternalAPIDevice())
		, mImpl(mAPIDevice, windowInfo)
	{

	}

	template<typename API>
	Window<API>::~Window()
	{

	}

	template<typename API>
	void Window<API>::updateInput()
	{
		mImpl.updateInput();
	}

	template<typename API>
	bool Window<API>::focused() const
	{
		return mImpl.focused();
	}

	template<typename API>
	const Window<API>::template Impl& Window<API>::getInternalImpl() const
	{
		return mImpl;
	}
}

#endif
