/*****************************************************************//**
 * @file   BindLayout.hpp
 * @brief  BindLayoutクラスのヘッダファイル
 * 
 * @author ichi-raven
 * @date   December 2022
 *********************************************************************/
#ifndef HENCE_BINDLAYOUT_HPP_
#define HENCE_BINDLAYOUT_HPP_

#include "API.hpp"

namespace Hence
{
	template<typename API>
	class Shader;

	template<typename API>
	class BindLayout
	{
	public:
		using Impl = APITrait<API>::BindLayoutImpl;

		template<typename... ShaderType>
		BindLayout(Device<API>& device, ShaderType&... shaders);

		~BindLayout();

		// いったんおいとく
		//BindLayout(const std::map<std::pair<uint8_t, uint8_t>, ResourceType>& bindingLayoutTable);

		NONCOPYABLE(BindLayout)

		Impl& getInternalImpl() noexcept;

	private:
		using APIDevice = APITrait<API>::Device;

		//! デバイスの内部実装
		APIDevice& mAPIDevice;
		//! 内部実装
		Impl mImpl;


	};
}

#include "../src/BindLayout.inl"

#endif
