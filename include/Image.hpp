#ifndef HENCE_IMAGE_HPP_
#define HENCE_IMAGE_HPP_

#include "API.hpp"
#include "Utility/Macro.hpp"

#include <optional>

namespace Hence
{
    template<typename API>
    class Device;

    // destructできない構造が必要
    template<typename API>
    class Image
    {
    public:

        using Impl = APITrait<API>::ImageImpl;

        Image(VRAMAllocator<API>& VRAMAllocator, const ImageInfo& imageInfo) noexcept;
        
        ~Image() noexcept;

        NONCOPYABLE(Image)

        Impl& getInternalImpl() noexcept;

    private:
        using APIVRAMAllocator = APITrait<API>::VRAMAllocatorImpl;

        APIVRAMAllocator& mAPIVRAMAllocator;
        std::optional<Impl> mImpl;
    };
}

#include "../src/Image.inl"

#endif
