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

	Window window(device, WindowInfo
		{ .width = 640,
			.height = 480,
			.frameCount = 3,
			.windowName = "testWindow",
			.vsync = true,
			.fullScreen = false
		});

	VRAMAllocator vramAllocator(device);

	Buffer buffer(vramAllocator, BufferInfo
		{
			.memorySize = 10,
			.usage{BufferUsageBit::Vertex},
			.hostVisible = true,
		});

	Image image(vramAllocator, ImageInfo
		{
			.width = 128,
			.height = 128,
			.depth = 1,
			.sizeOfChannel = 4,
			.format = Format::R8G8B8A8Unorm,
			.dimension = Dimension::two,
			.usage{ImageUsageBit::Sampled},
			.hostVisible = true,
		});


	Shader vs(device, "testShaders/vert.spv");
	Shader fs(device, "testShaders/frag.spv");

	BindLayout bl(device, vs, fs);
	BindGroup bg(device, bl);

	RenderPass rp(device, window);

	return 0;
}
