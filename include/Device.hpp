#ifndef HENCE_DEVICE_HPP_
#define HENCE_DEVICE_HPP_

#include "API.hpp"
#include "Utility/Macro.hpp"

namespace Hence
{
    template<typename API>
    class Device
    {
    public:
        using APIDevice = APITrait<API>::Device;

        Device();

        ~Device();

        NONCOPYABLE(Device)

        void initialize();

        void destroy();

        APIDevice& getInternalDevice();

    private:

        static APIDevice mAPIDeviceInstance;
    };
}

#endif
