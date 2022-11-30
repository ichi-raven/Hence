/*****************************************************************//**
 * @file   Device.inl
 * @brief  Deviceクラスの実装分離ファイル
 * 
 * @author ichi-raven
 * @date   November 2022
 *********************************************************************/

#ifdef HENCE_DEVICE_HPP_

#include "../include/Utility/Logger.hpp"

#include <cassert>

namespace Hence
{
	template<typename API>
	Device<API>::Device()
	{
		Logger::info("API Name : {}\ninitialize start...", APITrait<API>::APIName);

		mAPIDevice = std::optional<APIDevice>(APIDevice());
	}

	template<typename API>
	Device<API>::~Device()
	{
		mAPIDevice.reset();

		Logger::info("destroyed all device memory");
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
	Device<API>::template APIDevice& Device<API>::getInternalAPIDevice()
	{
		//assert(mAPIDevice || !"invalid device instance!");

		return *mAPIDevice;
	}
}

#endif