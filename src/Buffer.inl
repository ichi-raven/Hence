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
	Buffer<API>::Buffer(VRAMAllocator<API>& VRAMAllocator, const BufferInfo& bufferInfo)
		: mAPIVRAMAllocator(VRAMAllocator.getInternalImpl())
	{
		auto&& either = mAPIVRAMAllocator.allocate();
		if (!either)
		{
			Logger::error("failed to allocate buffer!");
			return;
		}

		mImpl = either.get();
	}

	template<typename API>
	Buffer<API>::~Buffer()
	{
		mAPIVRAMAllocator.deallocate(mImpl);
	}

	template<typename API>
	template <typename DataType>
	Result Buffer<API>::writeData(const ArrayProxy<DataType> data)
	{
		mImpl.writeData(data);
	}

}

#endif
