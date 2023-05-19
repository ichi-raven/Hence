/*****************************************************************//**
 * @file   testmain.cpp
 * @brief  テスト用main関数ファイル(ライブラリとしてビルドする場合は除外する)
 *
 * @author ichi-raven
 * @date   November 2022
 *********************************************************************/

#include "include/Hence.hpp"

#include <iostream>
#include <vector>

struct Vertex
{
	float pos[3];
};

template <typename T>
struct RGBA
{
	T R;
	T G;
	T B;
	T A;
};

using namespace Hence;

template<typename API, std::uint32_t kFrameBufferNum>
Result render
	(
		Window<API>& window,
		std::array<Command<API>,	kFrameBufferNum>& commands, 
		std::array<Semaphore<API>,	kFrameBufferNum>& renderCompletedSemaphores,
		std::array<Semaphore<API>,	kFrameBufferNum>& frameBufferReadySemaphores,
		const std::uint32_t frameIndex,
		std::function<Result(Command<API>&, const std::uint32_t)> commandRecordingProc
	)
{
	//static std::uint32_t currentFrameIndex = 0;

	assert
	(	
		(
			commands.size() == renderCompletedSemaphores.size()
			&&
			commands.size() == frameBufferReadySemaphores.size()
		)
		|| !"invalid commands or semaphores size!"
	);

	const std::uint32_t imageIndex = window.acquireNextImage(frameBufferReadySemaphores[frameIndex]);

	auto& command = commands[frameIndex];

	if (FAILED(res, commandRecordingProc(command, imageIndex)))
	{
		return res;
	}

	if (FAILED(res, command.execute(frameBufferReadySemaphores[frameIndex], renderCompletedSemaphores[frameIndex])))
	{
		return res;
	}

	if (FAILED(res, window.present(imageIndex, renderCompletedSemaphores[frameIndex])))
	{
		return res;
	}

	return Result();
}

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

	RGBA<std::uint8_t> pixel{ 100, 100, 100, 1 };
	std::vector<RGBA<std::uint8_t>> data(128 * 128, pixel);
	int debug = sizeof(pixel);

	image.write(ArrayProxy(data.size(), data.data()));

	SamplerInfo si{};

	Sampler sampler(device, si);

	Shader vs(device, "testShaders/vert.spv");
	Shader fs(device, "testShaders/frag.spv");

	BindLayout bl(device, vs, fs);
	BindGroup bg(device, bl);
	bg.bind(0, 0, image, sampler);

	RenderPass rp(device, window);

	GraphicsPipeline gp(device, GraphicsPipelineInfo
		{
			.colorBlendingState
			{
				.logicOp = std::nullopt,
				.attachments = std::vector<ColorBlendAttachment>(1,
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
		bl, vs, fs);


	ColorClearValue ccv = std::array<float, 4>{ 1.0, 0, 0, 1 };
	DepthClearValue dcv
	{
		.depth		= 1.0,
		.stencil	= 0u
	};

	std::array<Command<Vulkan>,		kFrameBufferCount>	commands;
	std::array<Semaphore<Vulkan>,	kFrameBufferCount>	renderCompletedSemaphores;
	std::array<Semaphore<Vulkan>,	kFrameBufferCount>	frameBufferReadySemaphores;
	
	for (int i = 0; i < kFrameBufferCount; ++i)
	{
		commands[i] = std::move(Command(device));
		renderCompletedSemaphores[i] = std::move(Semaphore(device));
		frameBufferReadySemaphores[i] = std::move(Semaphore(device));
	}

	std::uint32_t currentFrameIndex = 0;

	auto recordingProc = [&](Command<Vulkan>& command, const std::uint32_t imageIndex) -> Result
	{
		if (FAILED(res, command.begin(rp, imageIndex, ccv, dcv)))
		{
			return res;
		}

		command.setGraphicsPipeline(gp);
		command.setBindGroup(bg, 0);
		command.render(4, 1, 0, 0);
		command.end();

		return Result();
	};

	// debug
	for (int i = 0; i < 100; ++i)
	{

		std::cerr << "now : " << currentFrameIndex << "\n";

		render<Vulkan, kFrameBufferCount>
			(
				window,
				commands,
				renderCompletedSemaphores,
				frameBufferReadySemaphores,
				currentFrameIndex,
				recordingProc
			);


		currentFrameIndex = (currentFrameIndex + 1) % kFrameBufferCount;
	}

	return 0;
}
