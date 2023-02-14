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
	Buffer<API>::Buffer(VRAMAllocator<API>& VRAMAllocator, const BufferInfo& bufferInfo) noexcept
		: mAPIVRAMAllocator(VRAMAllocator.getInternalImpl())
		//, mImpl(mAPIVRAMAllocator.allocate(bufferInfo).get())
	{
		auto&& either = mAPIVRAMAllocator.allocate(bufferInfo);
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
		mAPIVRAMAllocator.deallocate(*mImpl);
	}

	template<typename API>
	Buffer<API>::Buffer(Buffer&& other) noexcept
		: mAPIVRAMAllocator(other.mAPIVRAMAllocator)
		, mImpl(std::move(other.mImpl))
	{
		other.mImpl.reset();
	}

	template<typename API>
	Buffer<API>& Buffer<API>::operator=(Buffer&& other) noexcept
	{
		mAPIVRAMAllocator = other.mAPIVRAMAllocator;

		mAPIVRAMAllocator.deallocate(*mImpl);
		mImpl = std::move(other.mImpl);
		other.mImpl.reset();
	}

	template<typename API>
	template <typename DataType>
	Result Buffer<API>::writeData(const ArrayProxy<DataType> data)
	{
		mImpl->writeData(data);
	}

}

#endif
