/*****************************************************************//**
 * @file   SamplerInfo.hpp
 * @brief  SamplerInfo構造体のヘッダファイル
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
