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
    using Viewport = std::array<std::array<float, 3>, 2>;
    using Scissor = std::array<std::array<float, 2>, 2>;

	struct GraphicsPipelineInfo
	{
        ColorBlendState colorBlendingState;
        Topology topology;
        RasterizerState rasterizerState;
        MultiSampleState multiSampleState;
        DepthStencilState depthStencilState;
        
        std::optional<Viewport> viewport;  //左上手前、右下奥3次元(Depthは正規化座標)
        std::optional<Scissor> scissor;    //左上、右下2次元
	};
}

#endif