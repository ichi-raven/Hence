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
	BindGroup<API>::BindGroup() noexcept
	{

	}

	template<typename API>
	BindGroup<API>::BindGroup(Device<API>& device, BindLayout<API>& layout) noexcept
		: mImpl(std::make_optional<Impl>(&device.getInternalAPIDevice(), layout.getInternalImpl()))
	{
		
	}

	template<typename API>
	BindGroup<API>::~BindGroup() noexcept
	{

	}

	template<typename API>
	void BindGroup<API>::bind(std::uint8_t set, std::uint8_t binding, Buffer<API>& buffer) noexcept
	{
		assert(mImpl || !"invalid object! (construct with device first!)");

		mImpl->bind(set, binding, buffer.getInternalImpl());
	}

	template<typename API>
	void BindGroup<API>::bind(std::uint8_t set, std::uint8_t binding, Image<API>& image, Sampler<API>& sampler) noexcept
	{
		assert(mImpl || !"invalid object! (construct with device first!)");

		mImpl->bind(set, binding, image.getInternalImpl(), sampler.getInternalImpl());
	}

	template<typename API>
	BindGroup<API>::template Impl& BindGroup<API>::getInternalImpl() noexcept
	{
		assert(mImpl || !"invalid object! (construct with device first!)");

		return *mImpl;
	}

}

#endif
