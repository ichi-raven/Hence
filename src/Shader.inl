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
	Shader<API>::Shader(Device<API>& device, std::string_view path)
		: mAPIDevice(device.getInternalAPIDevice())
		, mImpl(mAPIDevice, path)
	{
		
	}

	template<typename API>
	Shader<API>::~Shader()
	{

	}

	template<typename API>
	Shader<API>::Impl& Shader<API>::getInternalImpl()
	{

	}
}

#endif