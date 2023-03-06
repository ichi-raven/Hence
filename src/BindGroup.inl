/*****************************************************************//**
 * @file   BindGroup.inl
 * @brief  BindGroupクラスの実装分離ファイル
 * 
 * @author ichi-raven
 * @date   November 2022
 *********************************************************************/
#ifdef HENCE_BINDGROUP_HPP_

namespace Hence
{
	template<typename API>
	BindGroup<API>::BindGroup(Device<API>& device, BindLayout<API>& layout) noexcept
		: mAPIDevice(device.getInternalAPIDevice())
		, mImpl(mAPIDevice, layout.getInternalImpl())
	{
		
	}

	template<typename API>
	BindGroup<API>::~BindGroup() noexcept
	{

	}

	template<typename API>
	Result BindGroup<API>::bind(uint8_t set, uint8_t binding, Buffer<API>& buffer) noexcept
	{
		mImpl.bind(set, binding, buffer.getInternalImpl());
	}

	template<typename API>
	Result BindGroup<API>::bind(uint8_t set, uint8_t binding, Image<API>& image) noexcept
	{
		mImpl.bind(set, binding, image.getInternalImpl());
	}

	template<typename API>
	const BindGroup<API>::template Impl& BindGroup<API>::getInternalImpl() const noexcept
	{
		return mImpl;
	}

}

#endif
