/*****************************************************************//**
 * @file   Image.inl
 * @brief  Imageクラスの実装展開ファイル
 * 
 * @author ichi-raven
 * @date   February 2023
 *********************************************************************/
#ifdef HENCE_IMAGE_HPP_

namespace Hence
{
	template<typename API>
	Image<API>::Image() noexcept
		: mpAPIVRAMAllocator(nullptr)
	{

	}

	template<typename API>
	Image<API>::Image(VRAMAllocator<API>& VRAMAllocator, const ImageInfo& imageInfo) noexcept
		: mpAPIVRAMAllocator(&VRAMAllocator.getInternalImpl())
	{
		assert(mpAPIVRAMAllocator || !"invalid VRAMAllocator! (construct with VRAMAllocator first!)");

		auto&& either = mpAPIVRAMAllocator->allocate(imageInfo);
		if (!either)
		{
			Logger::error("failed to allocate image!");
			return;
		}

		mImpl = std::make_optional(either.move());
	}

	template<typename API>
	Image<API>::~Image() noexcept
	{
		assert(mImpl || !"invalid image! (construct with VRAMAllocator first!)");

		mpAPIVRAMAllocator->deallocate(*mImpl);
	}

	template<typename API>
	Image<API>::Impl& Image<API>::getInternalImpl() noexcept
	{
		assert(mImpl || "invalid image! (construct with VRAMAllocator first!");
		return *mImpl;
	}
}

#endif