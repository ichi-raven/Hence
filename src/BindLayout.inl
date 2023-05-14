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
	BindLayout<API>::BindLayout() noexcept
	{
		
	}

	template<typename API>
	template<typename... ShaderType>
	BindLayout<API>::BindLayout(Device<API>& device, ShaderType&... shaders)
		//: mAPIDevice(device.getInternalAPIDevice())
		: mImpl(std::make_optional<Impl>(&device.getInternalAPIDevice(), shaders.getInternalImpl()...))
	{
		
	}


	template<typename API>
	BindLayout<API>::~BindLayout() noexcept
	{

	}

	template<typename API>
	BindLayout<API>::Impl& BindLayout<API>::getInternalImpl() noexcept
	{
		assert(mImpl || !"invalid object! (construct with device first!)");

		return *mImpl;
	}
}

#endif
