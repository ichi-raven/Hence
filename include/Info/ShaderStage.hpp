/*****************************************************************//**
 * @file   ShaderStage.hpp
 * @brief  ShaderStage列挙型のヘッダファイル
 * 
 * @author ichi-raven
 * @date   February 2023
 *********************************************************************/
#ifndef HENCE_INCLUDE_INFO_SHADERSTAGE_HPP
#define HENCE_INCLUDE_INFO_SHADERSTAGE_HPP

namespace Hence
{
	enum class ShaderStage
	{
		Vertex,
		Fragment,
		Pixel = Fragment,

	};
}

#endif
