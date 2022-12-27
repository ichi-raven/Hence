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
#include "Utility/ArrayProxy.hpp"

namespace Hence
{
	template<typename API>
	class Shader;

	template<typename API>
	class BindLayout
	{
	public:
		using Impl = APITrait<API>::BindLayoutImpl;

		BindLayout(const Shader<API>& shader);

		BindLayout(ArrayProxy<uint8_t> bufferBinding, ArrayProxy<uint8_t> imageBinding, ArrayProxy<uint8_t> samplerBinding);

		NONCOPYABLE(BindLayout);

		Impl& getInternalImpl();

	private:
		using APIDevice = APITrait<API>::Device;

		//! デバイスの内部実装
		APIDevice& mAPIDevice;
		//! 内部実装
		Impl mImpl;


	};
}

#endif
