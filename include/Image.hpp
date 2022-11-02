#ifndef HENCE_IMAGE_HPP_
#define HENCE_IMAGE_HPP_

#include "API.hpp"
#include "Utility/Macro.hpp"

namespace Hence
{
    template<typename API>
    class Device;

    // destruct�ł��Ȃ��\�����K�v
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
