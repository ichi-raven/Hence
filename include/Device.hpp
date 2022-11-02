/*****************************************************************//**
 * @file   Device.hpp
 * @brief  デバイスクラス，ここを起点としてライブラリの各機能を使用する
 * 
 * @author ichi-raven
 * @date   November 2022
 *********************************************************************/

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

#include "../src/Device.inl"

#endif
