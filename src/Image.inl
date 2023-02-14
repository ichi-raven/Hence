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
	Image<API>::Image(VRAMAllocator<API>& VRAMAllocator, const ImageInfo& imageInfo) noexcept
		: mAPIVRAMAllocator(VRAMAllocator.getInternalImpl())
	{
		auto&& either = mAPIVRAMAllocator.allocate(imageInfo);
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

	}
}

#endif