/*****************************************************************//**
 * @file   VRAMAllocator.inl
 * @brief  VRAMAllocatorクラスの実装分離ファイル
 * 
 * @author ichi-raven
 * @date   November 2022
 *********************************************************************/
#ifdef HENCE_VRAMALLOCATOR_HPP_

namespace Hence
{
	template<typename API>
	VRAMAllocator<API>::VRAMAllocator() noexcept
	{

	}

	template<typename API>
	VRAMAllocator<API>::VRAMAllocator(Device<API>& device) noexcept
		//: mAPIDevice(device.getInternalAPIDevice())
		: mImpl(std::make_optional<Impl>(&device.getInternalAPIDevice()))
	{}

	template<typename API>
	VRAMAllocator<API>::~VRAMAllocator() noexcept
	{}

	template<typename API>
	VRAMAllocator<API>::template Impl& VRAMAllocator<API>::getInternalImpl()
	{
		assert(mImpl || !"invalid VRAMAllocator! (construct with device first!)");

		return *mImpl;
	}

	template<typename API>
	Buffer<API>& VRAMAllocator<API>::allocate(const BufferInfo& bci) noexcept
	{
		assert(mImpl || !"invalid VRAMAllocator! (construct with device first!)");

		mImpl->allocate(bci);
	}

	template<typename API>
	Image<API>& VRAMAllocator<API>::allocate(const ImageInfo& ici) noexcept
	{
		assert(mImpl || !"invalid VRAMAllocator! (construct with device first!)");

		mImpl->allocate(ici);
	}

	template<typename API>
	void VRAMAllocator<API>::deallocate(Buffer<API>& buffer) noexcept
	{
		assert(mImpl || !"invalid VRAMAllocator! (construct with device first!)");

		mImpl->deallocate(buffer);
	}

	template<typename API>
	void VRAMAllocator<API>::deallocate(Image<API>& image) noexcept
	{
		assert(mImpl || !"invalid VRAMAllocator! (construct with device first!)");

		mImpl->deallocate(image);
	}
}

#endif
