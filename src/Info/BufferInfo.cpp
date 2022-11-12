/*****************************************************************//**
 * @file   BufferInfo.cpp
 * @brief  BufferInfo�\���̂̎���
 * 
 * @author ichi-raven
 * @date   November 2022
 *********************************************************************/

#include "../../include/Info/BufferInfo.hpp"

namespace Hence
{
	BufferInfo::BufferInfo()
		: memorySize(0)
		, usage(BufferUsageBit::eUniform)
		, hostVisible(false)
	{}

	BufferInfo::BufferInfo(size_t memorySize, BufferUsage usage, bool isHostVisible)
		: memorySize(bufferSize), usage(usage), hostVisible(isHostVisible)
	{}

}
