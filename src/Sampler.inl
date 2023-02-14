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
	Sampler<API>::Sampler(Device<API> device, const SamplerInfo& samplerInfo)
		: mAPIDevice(device.getInternalAPIDevice())
		, mImpl(mAPIDevice, samplerInfo)
	{

	}

	template <typename API>
	Sampler<API>::~Sampler()
	{

	}

	template <typename API>
	const Sampler<API>::template Impl& Sampler<API>::getInternalImpl() const noexcept
	{
		return mImpl;
	}

}

#endif
