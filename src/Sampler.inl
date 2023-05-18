/*****************************************************************//**
 * @file   Sampler.inl
 * @brief  Samplerクラスの実装展開ファイル
 * 
 * @author ichi-raven
 * @date   February 2023
 *********************************************************************/
#ifdef HENCE_SAMPLER_HPP_

#include "../include/Device.hpp"

namespace Hence
{
	template <typename API>
	Sampler<API>::Sampler() noexcept
	{

	}

	template <typename API>
	Sampler<API>::Sampler(Device<API>& device, const SamplerInfo& samplerInfo) noexcept
		//: mAPIDevice(device.getInternalAPIDevice())
		: mImpl(std::make_optional<Impl>(&device.getInternalAPIDevice(), samplerInfo))
	{

	}

	template <typename API>
	Sampler<API>::~Sampler() noexcept
	{

	}

	template <typename API>
	Sampler<API>::template Impl& Sampler<API>::getInternalImpl() noexcept
	{
		assert(mImpl || !"invalid sampler! (construct with device first!)");

		return *mImpl;
	}

}

#endif
