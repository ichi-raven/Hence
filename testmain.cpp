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
#include <chrono>
#include <numeric>

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

struct ShaderToy
{
		float iResolution[4];
		float iMouse[4];
		float iTime;
};

using namespace Hence;
using API = Vulkan;

int main()
{
	constexpr std::uint32_t kWidth = 640;
	constexpr std::uint32_t kHeight = 480;
	constexpr std::uint32_t kFrameBufferCount = 3;
	constexpr std::string_view kWindowName = "testWindow";
	constexpr bool kVSyncEnable = false;
	constexpr bool kFullScreen = false;

	constexpr std::uint32_t kComputeSize = 1000000;

	Device<API> device;

	Window window(device, WindowInfo
		{
			.width = kWidth,
			.height = kHeight,
			.frameCount = kFrameBufferCount,
			.windowName = kWindowName,
			.vsync = kVSyncEnable,
			.fullScreen = kFullScreen
		});

	VRAMAllocator vramAllocator(device);

	Buffer buffer(vramAllocator, BufferInfo
		{
			.memorySize = sizeof(ShaderToy),
			.usage{BufferUsageBit::Uniform},
			.hostVisible = true,
		});

	{// write
		ShaderToy data
		{
			.iResolution = { kWidth, kHeight, 1.f, 0},
			.iMouse = {0.f, 0.f, 0.f, 0.f},
			.iTime = 0.f
		};

		buffer.writeData(ArrayProxy(1, &data));
	}

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

	{// write
		RGBA<std::uint8_t> pixel{ 50, 50, 50, 1 };
		std::vector<RGBA<std::uint8_t>> data(128 * 128, pixel);

		image.write(ArrayProxy(static_cast<std::uint32_t>(data.size()), data.data()));
	}

	Sampler sampler(device, SamplerInfo{});

	Shader vs(device, "testShaders/shader.vert");
	Shader fs(device, "testShaders/testFrag.frag");
	//Shader fs(device, "testShaders/shader.frag");
	Shader cs(device, "testShaders/testComp.comp");

	BindLayout bl(device, vs, fs);
	BindGroup bg(device, bl);
	bg.bind(0, 0, image, sampler);
	bg.bind(0, 1, buffer);

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
			.topology{Topology::TriangleStrip},
			.viewport = std::nullopt,
			.scissor = std::nullopt
		},
		rp,
		bl, vs, fs);

	Buffer storageBuffer(vramAllocator, BufferInfo
		{
			.memorySize = sizeof(std::uint32_t) * kComputeSize,
			.usage{BufferUsageBit::Storage},
			.hostVisible = true,
		});

	BindLayout cbl(device, cs);
	BindGroup cbg(device, cbl);
	cbg.bind(0, 0, storageBuffer);
	ComputePipeline cp(device, cbl, cs);

	ColorClearValue ccv = std::array<float, 4>{ 0.9f, 0.0f, 0.0f, 1.f};
	DepthClearValue dcv
	{
		.depth		= 1.0,
		.stencil	= 0u
	};

	std::array<Command<API>,	kFrameBufferCount>	commands;
	std::array<Semaphore<API>,	kFrameBufferCount>	renderCompletedSemaphores;
	std::array<Semaphore<API>,	kFrameBufferCount>	frameBufferReadySemaphores;
	
	for (std::size_t i = 0; i < kFrameBufferCount; ++i)
	{
		commands[i]						= std::move(Command(device));
		renderCompletedSemaphores[i]	= std::move(Semaphore(device));
		frameBufferReadySemaphores[i]	= std::move(Semaphore(device));
	}

	auto recordingProc = [&](Command<API>& command, const std::uint32_t imageIndex) -> Result
	{
		command.begin();

		command.beginRenderPass(rp, imageIndex, ccv, dcv);
		command.setGraphicsPipeline(gp);
		command.setBindGroup(bg);
		command.render(4, 1, 0, 0);
		command.endRenderPass();
		
		command.setComputePipeline(cp);
		command.setBindGroup(cbg);
		command.dispatch(kComputeSize, 1, 1);

		command.end();

		return Result();
	};

	std::uint32_t currentFrameIndex = 0;
	std::uint32_t elapsedFrame = 0;
	constexpr std::size_t avgSize = 60;
	std::array<double, avgSize> times = {};
	double time = 0, deltaTime = 0;
	std::chrono::high_resolution_clock::time_point now, prev = std::chrono::high_resolution_clock::now();

	std::cout << "now running\n";
	while(!window.getKey(Key::Escape))
	{
		window.updateInput();
		
		const auto [mx, my] = window.getMousePos();
		
		{
			now = std::chrono::high_resolution_clock::now();
			time += deltaTime = std::chrono::duration_cast<std::chrono::microseconds>(now - prev).count() / 1000000.;
			times[elapsedFrame % avgSize] = deltaTime;
		}

		{// write
			ShaderToy data
			{
				.iResolution = { kWidth, kHeight, 1.f, 0},
				.iMouse = {static_cast<float>(mx), static_cast<float>(my) , 0.f, 0.f},
				.iTime = static_cast<float>(time)
			};

			buffer.writeData(ArrayProxy(1, &data));
		}

		render<API, kFrameBufferCount>
			(
				window,
				commands,
				renderCompletedSemaphores,
				frameBufferReadySemaphores,
				currentFrameIndex,
				recordingProc
			);

		{// read
			storageBuffer.readData<std::uint32_t>([](std::uint32_t* ptr, std::size_t size)
				{
					std::cout << "compute val : " << ptr[955793] << "\n";
				});
		}

		{
			currentFrameIndex = (currentFrameIndex + 1) % kFrameBufferCount;
			++elapsedFrame;
			prev = now;
		}
	}

	
	std::cerr << "fps : " << 1. / (std::accumulate(times.begin(), times.end(), 0.) / static_cast<double>(avgSize)) << "\n";

	std::cout << "end\n";

	return 0;
}
