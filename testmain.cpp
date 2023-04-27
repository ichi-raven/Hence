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
	constexpr std::uint32_t kWidth				= 640;
	constexpr std::uint32_t kHeight				= 480;
	constexpr std::uint32_t kFrameBufferCount	= 3;
	constexpr std::string_view kWindowName		= "testWindow";
	constexpr bool kVSyncEnable					= true;
	constexpr bool kFullScreen					= false;

	Device<Vulkan> device;

	Window window(device, WindowInfo
		{
			.width			= kWidth,
			.height			= kHeight,
			.frameCount		= kFrameBufferCount,
			.windowName		= kWindowName,
			.vsync			= kVSyncEnable,
			.fullScreen		= kFullScreen
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

	GraphicsPipeline gp(device, GraphicsPipelineInfo
		{
			.colorBlendingState
			{
				.logicOp = std::nullopt,
				.attachments = std::vector<ColorBlendAttachment>(3,
					ColorBlendAttachment
					{
						.blendEnable = false,
						.srcColor = BlendFactor::One,
						.dstColor = BlendFactor::Zero,
						.colorBlendOp = BlendOp::Add,
						.srcAlpha = BlendFactor::One,
						.dstAlpha = BlendFactor::Zero,
						.alphaBlendOp = BlendOp::Add,
						.colorWriteMask = {ColorComponent{ColorComponentBit::R | ColorComponentBit::G | ColorComponentBit::B | ColorComponentBit::A}},
					}),
				.blendConstants = {0},
			},
			.depthStencilState
			{
				.depthTestEnable = true,
				.depthWriteEnable = true,
				.depthCompareOp = CompareOp::Less,
				.stencilTestEnable = false
			},
			.multiSampleState
			{
				.rasterizationSamples = SampleCount(SampleCountFlag::b1),
			},
			.rasterizerState
			{
				.depthClampEnable = false,
				.polygonMode = PolygonMode::Fill,
				.cullMode = CullMode::None,
				.frontFace = FrontFace::CCW,
				.lineWidth = 1.f,
			},
			.topology{Topology::TriangleList},
			.viewport = std::nullopt,
			.scissor = std::nullopt
		},
		rp,
		bl,
		vs, fs);

	Command command(device, kFrameBufferCount);

	ColorClearValue ccv = std::array<std::uint32_t, 4>{ 0, 0, 0, 0 };
	DepthClearValue dcv
	{
		.depth		= 1.0,
		.stencil	= 0u
	};

	command.begin(rp, ccv, dcv);

	command.setGraphicsPipeline(gp);

	command.end();

	while (true)
	{
		command.execute();

		window.present();
	}

	return 0;
}
