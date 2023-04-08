/*****************************************************************//**
 * @file   RasterizerState.hpp
 * @brief  RasterizerState構造体のヘッダファイル
 * 
 * @author ichi-raven
 * @date   March 2023
 *********************************************************************/
#ifndef HENCE_INFO_RASTERIZERSTATE_HPP_
#define HENCE_INFO_RASTERIZERSTATE_HPP_

#include <optional>

namespace Hence
{
    struct DepthBias
    {
        float constantFactor;
        float clamp;
        float slopeFactor;
    };

    enum class PolygonMode
    {
        Fill = 0,
        Line = 1,
        Point = 2,
    };

    enum class CullMode
    {
        None = 0,
        Front = 1,
        Back = 2,
        FrontAndBack = 3,
        Both = FrontAndBack,
    };

    enum class FrontFace
    {
        CounterClockwise = 0,
        Clockwise = 1,
        CCW = CounterClockwise,
        CW = Clockwise,
    };

    struct RasterizerState
    {
        bool depthClampEnable;
        bool rasterizerDiscardEnable;
        PolygonMode polygonMode;
        CullMode cullMode;
        FrontFace frontFace;
        float lineWidth;
        std::optional<DepthBias> depthBias;
    };
}

#endif
