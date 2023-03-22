/*****************************************************************//**
 * @file   testmain.cpp
 * @brief  �e�X�g�pmain�֐��t�@�C��(���C�u�����Ƃ��ăr���h����ꍇ�͏��O����)
 * 
 * @author ichi-raven
 * @date   November 2022
 *********************************************************************/

#include "include/Hence.hpp"

#include <iostream>

struct Vertex
{
	float pos[3];
};

using namespace Hence;

int main()
{
	Device<Vulkan> device;

	Window window(device, WindowInfo(640, 480, 4, "testWindow"));

	VRAMAllocator vramAllocator(device);

	{
		BufferInfo bi;
		bi.setVertexBuffer<Vertex>(10);

		Buffer buffer(vramAllocator, bi);
	}

	{
		ImageInfo ii;
		ii.setSRTex2D(128, 128, true);

		Image image(vramAllocator, ii);
	}

	Shader vs(device, "testShaders/vert.spv");
	Shader fs(device, "testShaders/frag.spv");

	BindLayout bl(device, vs, fs);
	BindGroup bg(device, bl);

	return 0;
}
