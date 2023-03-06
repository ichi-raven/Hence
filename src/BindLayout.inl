/*****************************************************************//**
 * @file   BindLayout.inl
 * @brief  BindLayoutクラスの実装展開ファイル
 * 
 * @author ichi-raven
 * @date   February 2023
 *********************************************************************/
#ifdef HENCE_BINDLAYOUT_HPP_

namespace Hence
{
	template<typename API>
	template<typename... ShaderType>
	BindLayout<API>::BindLayout(Device<API>& device, ShaderType&... shaders)
		: mAPIDevice(device.getInternalAPIDevice())
		, mImpl(mAPIDevice, shaders.getInternalImpl()...)
	{
		
	}


	template<typename API>
	BindLayout<API>::~BindLayout()
	{

	}

	template<typename API>
	BindLayout<API>::Impl& BindLayout<API>::getInternalImpl() noexcept
	{
		return mImpl;
	}
}

#endif
