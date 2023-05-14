/*****************************************************************//**
 * @file   Buffer.inl
 * @brief  Bufferクラスの実装展開ファイル
 * 
 * @author ichi-raven
 * @date   December 2022
 *********************************************************************/
#ifdef HENCE_BUFFER_HPP_

#include "../include/VRAMAllocator.hpp"

#include "../include/Utility/Either.hpp"

#include "../include/API.hpp"

namespace Hence
{
	template<typename API>
	Buffer<API>::Buffer() noexcept
		: mpAPIVRAMAllocator(nullptr)
	{

	}

	template<typename API>
	Buffer<API>::Buffer(VRAMAllocator<API>& VRAMAllocator, const BufferInfo& bufferInfo) noexcept
		: mpAPIVRAMAllocator(&VRAMAllocator.getInternalImpl())
		//, mImpl(mAPIVRAMAllocator.allocate(bufferInfo).get())
	{
		assert(mpAPIVRAMAllocator || !"invalid VRAMAllocator! (construct with VRAMAllocator first!)");

		auto&& either = mpAPIVRAMAllocator->allocate(bufferInfo);
		if (!either)
		{
			Logger::error("failed to allocate buffer!(result : {})", either.failed().nativeResult);
			return;
		}

		mImpl = std::make_optional(either.move());
	}

	template<typename API>
	Buffer<API>::~Buffer() noexcept
	{
		assert(mImpl || "invalid buffer! (allocate first!)");

		mpAPIVRAMAllocator->deallocate(*mImpl);
	}

	template<typename API>
	Buffer<API>::Buffer(Buffer&& other) noexcept
		: mpAPIVRAMAllocator(other.mpAPIVRAMAllocator)
		, mImpl(std::move(other.mImpl))
	{
		other.mImpl.reset();
	}

	template<typename API>
	Buffer<API>& Buffer<API>::operator=(Buffer&& other) noexcept
	{
		mpAPIVRAMAllocator = other.mpAPIVRAMAllocator;

		mpAPIVRAMAllocator->deallocate(*mImpl);
		mImpl = std::move(other.mImpl);
		other.mImpl.reset();
	}

	template<typename API>
	Buffer<API>::Impl& Buffer<API>::getInternalImpl() noexcept
	{
		assert(mImpl || "invalid buffer! (allocate first!)");

		return *mImpl;
	}

	template<typename API>
	template <typename DataType>
	Result Buffer<API>::writeData(const ArrayProxy<DataType> data)
	{
		assert(mImpl || "invalid buffer! (allocate first!)");

		mImpl->writeData(data);
	}

}

#endif
