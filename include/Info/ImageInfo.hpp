/*****************************************************************//**
 * @file   ImageInfo.hpp
 * @brief  ImageInfo構造体のヘッダファイル
 * 
 * @author ichi-raven
 * @date   November 2022
 *********************************************************************/
#ifndef HENCE_INFO_IMAGEINFO_HPP_
#define HENCE_INFO_IMAGEINFO_HPP_

#include "ImageUsage.hpp"
#include "Format.hpp"
#include "Dimension.hpp"


namespace Hence
{
    struct ImageInfo
    {
        // 集成体初期化を想定

        inline void setSRTex2D(uint32_t _width, uint32_t _height, bool _isHostVisible, Format _format = Format::R8G8B8A8Unorm)
        {
            width = _width;
            height = _height;
            depth = 1;
            dimension = Dimension::two;
            format = _format;
            hostVisible = _isHostVisible;
            format = format;
            usage = ImageUsageBit::Sampled;
        }

        inline void setRTTex2D(uint32_t _width, uint32_t _height, Format _format = Format::R8G8B8A8Unorm, bool _isHostVisible = true)
        {
            width = _width;
            height = _height;
            depth = 1;
            dimension = Dimension::two;
            format = _format;
            hostVisible = _isHostVisible;
            format = format;
            usage = ImageUsageBit::ColorAttachment;
        }

        inline void setRTTex2DColor(uint32_t _width, uint32_t _height, Format _format = Format::R8G8B8A8Unorm, bool _isHostVisible = true)
        {
            width = _width;
            height = _height;
            depth = 1;
            dimension = Dimension::three;
            format = _format;
            hostVisible = _isHostVisible;
            format = format;
            usage = ImageUsageBit::ColorAttachment;
        }

        inline void setRTTex2DDepth(uint32_t _width, uint32_t _height, Format _format = Format::D32SFloat , bool _isHostVisible = true)
        {
            width = _width;
            height = _height;
            depth = 1;
            dimension = Dimension::two;
            format = _format;
            hostVisible = _isHostVisible;
            format = format;
            usage = ImageUsageBit::DepthStencilAttachment;
        }

        std::uint32_t width;
        std::uint32_t height;
        std::uint32_t depth;
        Format format;
        Dimension dimension;
        ImageUsage usage;
        bool hostVisible;
    };
}

#endif
