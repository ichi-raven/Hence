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

        ImageInfo(uint32_t width, uint32_t height, Sampler sampler, uint32_t depth = 1u, Format format = Format::R8G8B8A8Unorm, ImageUsage usage = ImageUsageBit::Storage, bool isHostVisible = true, Dimension dimension = Dimension::two)
            : width(width)
            , height(height)
            , depth(depth)
            , usage(usage)
            , dimension(dimension)
            , format(format)
            , sampler(sampler)
            , isHostVisible(isHostVisible)
        {

        }

        inline void setSRTex2D(uint32_t _width, uint32_t _height, Sampler _sampler, bool _isHostVisible, Format _format = Format::R8G8B8A8Unorm, Sampler _sampler)
        {
            width = _width;
            height = _height;
            depth = 1;
            dimension = Dimension::two;
            format = _format;
            isHostVisible = _isHostVisible;
            format = format;
            sampler = _sampler;
            usage = ImageUsageBit::Sampled;
        }

        inline void setRTTex2D(uint32_t _width, uint32_t _height, Sampler _sampler, Format _format = Format::R8G8B8A8Unorm, bool _isHostVisible = true, Sampler _sampler)
        {
            width = _width;
            height = _height;
            depth = 1;
            dimension = Dimension::two;
            format = _format;
            isHostVisible = _isHostVisible;
            format = format;
            sampler = _sampler;
            usage = ImageUsageBit::ColorAttachment;
        }

        inline void setRTTex2DColor(uint32_t _width, uint32_t _height, Sampler _sampler, Format _format = Format::R8G8B8A8Unorm, bool _isHostVisible = true, Sampler _sampler)
        {
            width = _width;
            height = _height;
            depth = 1;
            dimension = Dimension::three;
            format = _format;
            isHostVisible = _isHostVisible;
            format = format;
            sampler = _sampler;
            usage = ImageUsageBit::ColorAttachment;
        }

        inline void setRTTex2DDepth(uint32_t _width, uint32_t _height, Sampler _sampler, Format _format = Format::R8G8B8A8Unorm, bool _isHostVisible = true)
        {
            width = _width;
            height = _height;
            depth = 1;
            dimension = Dimension::two;
            format = _format;
            isHostVisible = _isHostVisible;
            format = format;
            sampler = _sampler;
            usage = ImageUsageBit::DepthStencilAttachment;
        }

        ImageUsage usage;
        Dimension dimension;
        Format format;
        Sampler sampler;
        bool isHostVisible;
        std::uint32_t width;
        std::uint32_t height;
        std::uint32_t depth;
    };
}

#endif
