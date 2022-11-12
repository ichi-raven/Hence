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
        ImageInfo() {}

        ImageInfo(uint32_t width, uint32_t height, uint32_t depth = 1u, Format format = Format::R8G8B8A8Unorm, ImageUsage usage = ImageUsageBit::, bool isHostVisible = true, Dimension dimension = Dimension::e2D, SamplerType samplerType = SamplerType::eDefault)
            : width(width)
            , height(height)
            , depth(depth)
            , usage(usage)
            , dimension(dimension)
            , format(format)
            , samplerType(samplerType)
            , isHostVisible(isHostVisible)
        {

        }

        inline void setSRTex2D(uint32_t _width, uint32_t _height, bool _isHostVisible, Format _format = Format::R8G8B8A8Unorm, SamplerType _samplerType = SamplerType::eDefault)
        {
            width = _width;
            height = _height;
            depth = 1;
            dimension = Dimension::e2D;
            format = _format;
            isHostVisible = _isHostVisible;
            format = format;
            samplerType = _samplerType;
            usage = TextureUsage::eShaderResource;
        }

        inline void setRTTex2D(uint32_t _width, uint32_t _height, Format _format = Format::R8G8B8A8Unorm, bool _isHostVisible = true, SamplerType _samplerType = SamplerType::eDefault)
        {
            width = _width;
            height = _height;
            depth = 1;
            dimension = Dimension::e2D;
            format = _format;
            isHostVisible = _isHostVisible;
            format = format;
            samplerType = _samplerType;
            usage = ImageUsageBit::ColorAttachment;
        }

        inline void setRTTex2DColor(uint32_t _width, uint32_t _height, Format _format = Format::R8G8B8A8Unorm, bool _isHostVisible = true, SamplerType _samplerType = SamplerType::eDefault)
        {
            width = _width;
            height = _height;
            depth = 1;
            dimension = Dimension::e2D;
            format = _format;
            isHostVisible = _isHostVisible;
            format = format;
            samplerType = _samplerType;
            usage = ImageUsageBit::ColorAttachment;
        }

        inline void setRTTex2DDepth(uint32_t _width, uint32_t _height, Format _format = Format::R8G8B8A8Unorm, bool _isHostVisible = true, SamplerType _samplerType = SamplerType::eDefault)
        {
            width = _width;
            height = _height;
            depth = 1;
            dimension = Dimension::e2D;
            format = _format;
            isHostVisible = _isHostVisible;
            format = format;
            samplerType = _samplerType;
            usage = ImageUsageBit::DepthStencilAttachment;
        }

        ImageUsage usage;
        Dimension dimension;
        Format format;
        SamplerType samplerType;
        bool isHostVisible;
        std::uint32_t width;
        std::uint32_t height;
        std::uint32_t depth;
    };
}

#endif
