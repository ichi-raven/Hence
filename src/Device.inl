/*****************************************************************//**
 * @file   Device.inl
 * @brief  Deviceクラスの実装分離ファイル
 * 
 * @author ichi-raven
 * @date   November 2022
 *********************************************************************/

#ifdef HENCE_DEVICE_HPP_

#include "../include/API.hpp"

#include <cassert>

namespace Hence
{
	template<typename API>
	Device::Device()
	{
		mAPIDeviceInstance = APIDevice();
	}

	template<typename API>
	Device::~Device()
	{
		mAPIDevice->~APIDevice();
		mAPIDevice = std::nullopt();
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
#ifdef DEBUG
		assert(mAPIDeviceInstance || !"invalid device instance!");
#endif
		return *mAPIDeviceInstance;
	}
}

#endif