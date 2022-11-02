#pragma once

#include "API.hpp"
#include "Utility/Macro.hpp"

namespace Hence
{
	template<typename API>
	class Device;

	template<typename API>
	class Buffer;

	template<typename API>
	class Image;

	template<typename API>
	//requires VRAMAllocatorConcept<APITrait<API>::VRAMAllocatorImpl>
	class VRAMAllocator
	{
	public:

		using Impl = APITrait<API>::VRAMAllocatorImpl;

		VRAMAllocator(Device<API>& device);

		~VRAMAllocator();

		NONCOPYABLE(VRAMAllocator)

		Buffer<API>& allocate(const BufferCreateInfo& bci);
		Image<API>& allocate(const ImageCreateInfo& ici);

		void deallocate(Buffer<API>& buffer);
		void deallocate(Image<API>& image);

	private:
		using APIDevice = APITrait<API>::Device;

		APIDevice& mAPIDevice;
		Impl mImpl;
	};

}
