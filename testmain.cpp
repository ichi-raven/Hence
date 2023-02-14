/*****************************************************************//**
 * @file   testmain.cpp
 * @brief  �e�X�g�pmain�֐��t�@�C��(���C�u�����Ƃ��ăr���h����ꍇ�͏��O����)
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

	Hence::ImageInfo ii;
	ii.setSRTex2D(128, 128, true);

	Hence::Image image(vramAllocator, ii);

	Hence::Shader vs(device, "testShaders/vert.spv");
	Hence::Shader fs(device, "testShaders/vert.spv");

	return 0;
}
