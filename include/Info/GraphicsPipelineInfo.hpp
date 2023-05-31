/*****************************************************************//**
 * @file   GraphicsPipelineInfo.hpp
 * @brief  GraphicsPipelineInfoクラスのヘッダファイル
 * 
 * @author ichi-raven
 * @date   March 2023
 *********************************************************************/
#ifndef HENCE_INFO_GRAPHICSPIPELINEINFO_HPP_
#define HENCE_INFO_GRAPHICSPIPELINEINFO_HPP_

#include <array>
#include <optional>

#include "ColorBlendState.hpp"
#include "Topology.hpp"
#include "RasterizerState.hpp"
#include "MultiSamplingState.hpp"
#include "DepthStencilState.hpp"


namespace Hence
{
    // TopLeftFront, BottomRightBack
    using Viewport = std::array<std::array<float, 3>, 2>;
    // TopLeft, BottomRight
    using Scissor = std::array<std::array<float, 2>, 2>;

	struct GraphicsPipelineInfo
	{
        static GraphicsPipelineInfo getDefaultVal() noexcept
        {
			return GraphicsPipelineInfo
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
			};
        }

        ColorBlendState colorBlendingState;
        DepthStencilState depthStencilState;
        MultiSampleState multiSampleState;
        RasterizerState rasterizerState;
        Topology topology;
        
        std::optional<Viewport> viewport;  //左上手前、右下奥3次元(Depthは正規化座標)
        std::optional<Scissor> scissor;    //左上、右下2次元
	};
}

#endif