/*****************************************************************//**
 * @file   BufferInfo.cpp
 * @brief  BufferInfoç\ë¢ëÃÇÃé¿ëï
 * 
 * @author ichi-raven
 * @date   November 2022
 *********************************************************************/

#include "../../include/Info/BufferInfo.hpp"

namespace Hence
{
	BufferInfo::BufferInfo()
		: memorySize(0)
		, usage(BufferUsageBit::Uniform)
		, hostVisible(false)
	{}

	BufferInfo::BufferInfo(size_t memorySize, BufferUsage usage, bool isHostVisible)
		: memorySize(memorySize), usage(usage), hostVisible(isHostVisible)
	{}

}
