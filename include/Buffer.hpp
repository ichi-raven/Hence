#ifndef HENCE_BUFFER_HPP_
#define HENCE_BUFFER_HPP_

#include "API.hpp"
#include "Utility/Macro.hpp"

namespace Hense
{
    template<typename API>
    class Device;

    // destructÇ≈Ç´Ç»Ç¢ç\ë¢Ç™ïKóv
    template<typename API>
    class Buffer
    {
    public:

        using Impl = APITrait<API>::BufferImpl;

        Buffer(Device<API>& device, Impl& impl);
        ~Buffer();
        NONCOPYABLE(Buffer)

    private:
        using APIDevice = APITrait<API>::Device;

        APIDevice& mDevice;
        Impl mImpl;
    };
}

#endif
