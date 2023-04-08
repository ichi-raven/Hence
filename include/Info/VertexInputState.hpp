/*****************************************************************//**
 * @file   VertexInputState.hpp
 * @brief  VertexInputState構造体及び関連列挙型のヘッダファイル
 * 
 * @author ichi-raven
 * @date   April 2023
 *********************************************************************/
#ifndef HENCE_INFO_VERTEXINPUTSTATE_HPP_
#define HENCE_INFO_VERTEXINPUTSTATE_HPP_

#include "Format.hpp"

#include <vector>


namespace Hence
{
	enum class VertexInputRate
	{
		Vertex = 0,
		Instance = 1,
	};

	struct VertexInputBinding
	{
		std::uint32_t	binding;
		std::uint32_t	stride;
		VertexInputRate inputRate;
	};

	struct VertexInputAttribute
	{
		std::uint32_t	location;
		std::uint32_t	binding;
		Format			format;
		std::uint32_t	offset;
	};

	struct VertexInputState
	{
		std::vector<VertexInputBinding> vertexBindings;
		std::vector<VertexInputAttribute> vertexLayouts;
	};
};

#endif
