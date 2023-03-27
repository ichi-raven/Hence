/*****************************************************************//**
 * @file   ColorBlendState.hpp
 * @brief  ColorBlendState構造体のヘッダファイル
 * 
 * @author ichi-raven
 * @date   March 2023
 *********************************************************************/
#ifndef HENCE_INFO_COLORBLENDSTATE_HPP_
#define HENCE_INFO_COLORBLENDSTATE_HPP_

#include <array>
#include <vector>
#include <optional>

#include "ColorComponent.hpp"

namespace Hence
{
    enum class LogicOp
    {
        Clear = 0,
        And = 1,
        AndReverse = 2,
        Copy = 3,
        AndInverted = 4,
        NoOp = 5,
        Xor = 6,
        Or = 7,
        Nor = 8,
        Equivalent = 9,
        Invert = 10,
        OrReverse = 11,
        CopyInverted = 12,
        OrInverted = 13,
        Nand = 14,
        Set = 15,
    };

    enum class BlendOp
    {
        Add = 0,
        Sub = 1,
        ReverseSub = 2,
        Min = 3,
        Max = 4,
    };

    enum class BlendFactor
    {
        Zero = 0,
        One = 1,
        SrcColor = 2,
        OneMinusSrcColor = 3,
        DstColor = 4,
        OneMinusDstColor = 5,
        SrcAlpha = 6,
        OneMinusSrcAlpha = 7,
        DstAlpha = 8,
        OneMinusDstAlpha = 9,
        ConstantColor = 10,
        OneMinusConstantColor = 11,
        ConstantAlpha = 12,
        OneMinusConstantAlpha = 13,
        SrcAlphaAbsolute = 14,
        Src1Color = 15,
        OneMinusSrc1Color = 16,
        Src1Alpha = 17,
        OneMinusSrc1Alpha = 18,
    };

    struct ColorBlendAttachment
    {
        bool blendEnable;
        BlendFactor srcColor;
        BlendFactor dstColor;
        BlendOp colorBlendOp;
        BlendFactor srcAlpha;
        BlendFactor dstAlpha;
        BlendOp alphaBlendOp;
        ColorComponent component;
    };

    struct ColorBlendState
    {
        std::optional<LogicOp> logicOp;
        std::vector<ColorBlendAttachment> attachments;
        std::array<float, 4> blendConstants;
    };
}

#endif
