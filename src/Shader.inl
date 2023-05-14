/*****************************************************************//**
 * @file   Shader.inl
 * @brief  Shaderクラスの実装展開ファイル
 * 
 * @author ichi-raven
 * @date   February 2023
 *********************************************************************/
#ifdef HENCE_SHADER_HPP_

namespace Hence
{
	template<typename API>
	Shader<API>::Shader() noexcept
	{

	}

	template<typename API>
	Shader<API>::Shader(Device<API>& device, std::string_view path) noexcept
		//: mAPIDevice(device.getInternalAPIDevice())
		: mImpl(std::make_optional<Impl>(&device.getInternalAPIDevice(), path))
	{
		
	}

	template<typename API>
	Shader<API>::~Shader() noexcept
	{

	}

	template<typename API>
	Shader<API>::Impl& Shader<API>::getInternalImpl() noexcept
	{
		assert(mImpl || !"invalid shader! (construct with device first!)");

		return *mImpl;
	}
}

#endif