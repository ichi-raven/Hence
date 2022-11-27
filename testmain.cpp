/*****************************************************************//**
 * @file   testmain.cpp
 * @brief  テスト用main関数ファイル(ライブラリとしてビルドする場合は除外する)
 * 
 * @author ichi-raven
 * @date   November 2022
 *********************************************************************/

#include "include/Hence.hpp"

struct Vertex
{
	float pos[3];
};

int main()
{
	Hence::Device<Hence::Vulkan> device;

	Hence::VRAMAllocator vramAllocator(device);

	Hence::BufferInfo bi;
	bi.setVertexBuffer<Vertex>(10);

	Hence::Buffer buffer(vramAllocator, bi);

	return 0;
}
