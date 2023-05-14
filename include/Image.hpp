#ifndef HENCE_IMAGE_HPP_
#define HENCE_IMAGE_HPP_

#include "API.hpp"
#include "Utility/Macro.hpp"

#include <optional>

namespace Hence
{
    template<typename API>
    class Device;

    // destructÇ≈Ç´Ç»Ç¢ç\ë¢Ç™ïKóv
    template<typename API>
    class Image
    {
    public:

        using Impl = APITrait<API>::ImageImpl;

        Image() noexcept;

        Image(VRAMAllocator<API>& VRAMAllocator, const ImageInfo& imageInfo) noexcept;
        
        ~Image() noexcept;

        NONCOPYABLE(Image)

        Impl& getInternalImpl() noexcept;

    private:
        using APIVRAMAllocator = APITrait<API>::VRAMAllocatorImpl;

        APIVRAMAllocator* mpAPIVRAMAllocator;
        std::optional<Impl> mImpl;
    };
}

#include "../src/Image.inl"

#endif
