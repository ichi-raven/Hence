/*****************************************************************//**
 * @file   Device.inl
 * @brief  Device�N���X�̎��������t�@�C��
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
		Logger::info("API Name : {}\n start initializing...", APITrait<API>::APIName);

		mAPIDevice.emplace();
	}

	template<typename API>
	Device<API>::~Device()
	{
		mAPIDevice.reset();

		Logger::info("destroying finished successfully");
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