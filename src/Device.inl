/*****************************************************************//**
 * @file   Device.inl
 * @brief  Device�N���X�̎��������t�@�C��
 * 
 * @author ichi-raven
 * @date   November 2022
 *********************************************************************/

#ifdef HENCE_DEVICE_HPP_

#include "../include/API.hpp"

namespace Hence
{
	template<typename API>
	Device::Device()
	{

	}

	template<typename API>
	Device::~Device()
	{

	}

	template<typename API>
	Device::initialize()
	{

	}

	template<typename API>
	Device::destroy()
	{

	}

	template<typename API>
	Device::APIDevice& Device::getInternalDevice()
	{
		return mAPIDeviceInstance;
	}
}

#endif