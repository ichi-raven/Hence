/*****************************************************************//**
 * @file   Device.inl
 * @brief  Deviceクラスの実装分離ファイル
 * 
 * @author ichi-raven
 * @date   November 2022
 *********************************************************************/

#ifdef HENCE_DEVICE_HPP_

#include "../include/API.hpp"

#include "../include/Utility/Logger.hpp"

#include <cassert>

namespace Hence
{
	template<typename API>
	Device::Device()
	{
		Logger::info("API Name : {}\ninitialize start...", APITrait<API>::APIName);

		if (!mAPIDeviceInstance)
		{
			mAPIDeviceInstance = APIDevice();
		}
	}

	template<typename API>
	Device::~Device()
	{
		if (mAPIDevice)
		{
			mAPIDevice->~APIDevice();
			mAPIDevice = std::nullopt();
		}

		Logger::info("destroyed all device data");
	}

	//template<typename API>
	//Device::initialize()
	//{

	//}

	//template<typename API>
	//Device::destroy()
	//{

	//}

	template<typename API>
	Device::APIDevice& Device::getInternalDevice()
	{
		assert(mAPIDeviceInstance || !"invalid device instance!");

		return *mAPIDeviceInstance;
	}
}

#endif