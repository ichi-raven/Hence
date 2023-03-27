/*****************************************************************//**
 * @file   BufferInfo.hpp
 * @brief  BufferInfo構造体のヘッダファイル
 *
 * @author ichi-raven
 * @date   November 2022
 *********************************************************************/
#ifndef HENCE_INFO_BUFFERINFO_HPP_
#define HENCE_INFO_BUFFERINFO_HPP_

#include "BufferUsage.hpp"

namespace Hence
{
	/**
	 * @brief  Buffer作成時情報
	 */
	struct BufferInfo
	{

		// 集成体初期化を想定

		//BufferInfo();

		//BufferInfo(size_t bufferMemorySize, BufferUsage usage, bool isHostVisible);

		template <typename VertexType>
		inline void setVertexBuffer(size_t vertexCount)
		{
			memorySize = vertexCount * sizeof(VertexType);
			usage = BufferUsageBit::Vertex;
			hostVisible = true;
		}

		template <typename IndexType>
		inline void setIndexBuffer(size_t indexCount)
		{
			memorySize = indexCount * sizeof(IndexType);
			usage = BufferUsageBit::Index;
			hostVisible = true;
		}

		template <typename UniformType>
		inline void setUniformBuffer(size_t count = 1, bool isHostVisible = true)
		{
			memorySize = count * sizeof(UniformType);
			usage = BufferUsageBit::Uniform;
			hostVisible = isHostVisible;
		}

		//! バッファ全体のサイズ
		size_t memorySize;
		//! バッファの使用方法
		BufferUsage usage;
		//! CPUからのデータの読み書きが必要ならtrue
		bool hostVisible;

	};

}
#endif
