/*****************************************************************//**
 * @file   GraphicsPipelineInfo.hpp
 * @brief  GraphicsPipelineInfo�N���X�̃w�b�_�t�@�C��
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
        
        std::optional<Viewport> viewport;  //�����O�A�E����3����(Depth�͐��K�����W)
        std::optional<Scissor> scissor;    //����A�E��2����
	};
}

#endif