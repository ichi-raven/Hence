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
#include "Sampler.hpp"

namespace Hence
{
    struct ImageInfo
    {
        ImageInfo() {}

        ImageInfo(uint32_t width, uint32_t height, uint32_t depth = 1u, Format format = Format::R8G8B8A8Unorm, ImageUsage usage = ImageUsageBit::Storage, bool hostVisible = true, Dimension dimension = Dimension::two)
            : width(width)
            , height(height)
            , depth(depth)
            , usage(usage)
            , dimension(dimension)
            , format(format)
            , hostVisible(hostVisible)
        {

        }

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

        inline void setRTTex2DDepth(uint32_t _width, uint32_t _height, Format _format = Format::R8G8B8A8Unorm, bool _isHostVisible = true)
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

        ImageUsage usage;
        Dimension dimension;
        Format format;
        bool hostVisible;
        std::uint32_t width;
        std::uint32_t height;
        std::uint32_t depth;
    };
}

#endif
