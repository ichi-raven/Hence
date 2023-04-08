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
#include "BorderColor.hpp"

namespace Hence
{
	struct SamplerInfo
	{
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
