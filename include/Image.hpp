#ifndef HENCE_IMAGE_HPP_
#define HENCE_IMAGE_HPP_

#include "API.hpp"
#include "Utility/Macro.hpp"

namespace Hence
{
    template<typename API>
    class Device;

    // destructできない構造が必要
    template<typename API>
    class Image
    {
    public:

        using Impl = APITrait<API>::BufferImpl;

        Image(Device<API>& device, Impl& impl);
        ~Image();

        NONCOPYABLE(Image)

    private:
        using APIDevice = APITrait<API>::Device;

        APIDevice& mDevice;
        Impl mImpl;
    };
}

#endif
