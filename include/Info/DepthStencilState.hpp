/*****************************************************************//**
 * @file   DepthStencilState.hpp
 * @brief  DepthStencilState構造体のヘッダファイル
 * 
 * @author ichi-raven
 * @date   March 2023
 *********************************************************************/
#ifndef HENCE_INFO_DEPTHSTENCILSTATE_HPP_
#define HENCE_INFO_DEPTHSTENCILSTATE_HPP_

namespace Hence
{
	enum class CompareOp
	{
		Never			= 0,
		Less			= 1,
		Equal			= 2,
		LessOrEqual		= 3,
		Greater			= 4,
		NotEqual		= 5,
		GreaterOrEqual	= 6,
		Always			= 7,
	};

	enum class StencilOp
	{
		Keep				= 0,
		Zero				= 1,
		Replace				= 2,
		IncrementAndClamp	= 3,
		DecrementAndClamp	= 4,
		Invert				= 5,
		IncrementAndWrap	= 6,
		DecrementAndWrap	= 7,
	};

	struct StencilOpState
	{
		StencilOp		failOp;
		StencilOp		passOp;
		StencilOp		depthFailOp;
		CompareOp		compareOp;
		std::uint32_t	compareMask;
		std::uint32_t	writeMask;
		std::uint32_t	reference;
	};

	struct DepthStencilState
	{
		bool depthTestEnable;
		bool depthWriteEnable;
		CompareOp depthCompareOp;
		bool depthBoundsTestEnable;
		bool stencilTestEnable;
		float minDepthBounds;
		float maxDepthBounds;
		StencilOpState front;
		StencilOpState back;
	};
}

#endif
