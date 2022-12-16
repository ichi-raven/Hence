/*****************************************************************//**
 * @file   SamplerInfo.hpp
 * @brief  SamplerInfo�\���̂̃w�b�_�t�@�C��
 * 
 * @author ichi-raven
 * @date   November 2022
 *********************************************************************/
#ifndef HENCE_INFO_SAMPLERINFO_HPP_
#define HENCE_INFO_SAMPLERINFO_HPP_

#include "Filter.hpp"
#include "AddressMode.hpp"

namespace Hence
{
	struct SamplerInfo
	{
		SamplerInfo();

		~SamplerInfo();


		Filter minFilter;
		Filter magFilter;
		AddressMode addressModeU;
		AddressMode addressModeV;
		AddressMode addressModeW;
		BorderColor borderColor;
		float maxAnisotropy;
	};
}

#endif