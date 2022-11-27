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
	VRAMAllocator<API>::VRAMAllocator(Device<API>& device) noexcept
		: mAPIDevice(device.getInternalDevice())
		, mImpl(Impl(mAPIDevice))
	{}

	template<typename API>
	VRAMAllocator<API>::~VRAMAllocator() noexcept
	{}

	template<typename API>
	Buffer<API>& VRAMAllocator<API>::allocate(const BufferInfo& bci) noexcept
	{
		mImpl.allocate(bci);
	}

	template<typename API>
	Image<API>& VRAMAllocator<API>::allocate(const ImageInfo& ici) noexcept
	{
		mImpl.allocate(ici);
	}

	template<typename API>
	void VRAMAllocator<API>::deallocate(Buffer<API>& buffer) noexcept
	{
		mImpl.deallocate(buffer);
	}

	template<typename API>
	void VRAMAllocator<API>::deallocate(Image<API>& image) noexcept
	{
		mImpl.deallocate(image);
	}
}

#endif
