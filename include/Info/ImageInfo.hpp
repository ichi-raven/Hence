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

        //ImageInfo() 
        //    : width(64)
        //    , height(64)
        //    , depth(1)
        //    , usage(ImageUsageBit::Sampled)
        //    , dimension(Dimension::two)
        //    , format(Format::R8G8B8A8Unorm)
        //    , sizeOfChannel(4)
        //    , hostVisible(true) 
        //{
        //    // 呼ばないほうが良い
        //}

        //ImageInfo(uint32_t width, uint32_t height, uint32_t depth = 1u, Format format = Format::R8G8B8A8Unorm, std::uint32_t sizeOfChannel = 4, ImageUsage usage = ImageUsageBit::Storage, bool hostVisible = true, Dimension dimension = Dimension::two)
        //    : width(width)
        //    , height(height)
        //    , depth(depth)
        //    , usage(usage)
        //    , dimension(dimension)
        //    , format(format)
        //    , sizeOfChannel(sizeOfChannel)
        //    , hostVisible(hostVisible)
        //{

        //}

        inline void setSRTex2D(uint32_t _width, uint32_t _height, bool _isHostVisible, Format _format = Format::R8G8B8A8Unorm, std::uint32_t _sizeOfChannel = 4)
        {
            width = _width;
            height = _height;
            depth = 1;
            dimension = Dimension::two;
            format = _format;
            hostVisible = _isHostVisible;
            format = format;
            sizeOfChannel = _sizeOfChannel;
            usage = ImageUsageBit::Sampled;
        }

        inline void setRTTex2D(uint32_t _width, uint32_t _height, Format _format = Format::R8G8B8A8Unorm, std::uint32_t _sizeOfChannel = 4, bool _isHostVisible = true)
        {
            width = _width;
            height = _height;
            depth = 1;
            dimension = Dimension::two;
            format = _format;
            hostVisible = _isHostVisible;
            format = format;
            sizeOfChannel = _sizeOfChannel;
            usage = ImageUsageBit::ColorAttachment;
        }

        inline void setRTTex2DColor(uint32_t _width, uint32_t _height, Format _format = Format::R8G8B8A8Unorm, std::uint32_t _sizeOfChannel = 4, bool _isHostVisible = true)
        {
            width = _width;
            height = _height;
            depth = 1;
            dimension = Dimension::three;
            format = _format;
            hostVisible = _isHostVisible;
            format = format;
            sizeOfChannel = _sizeOfChannel;
            usage = ImageUsageBit::ColorAttachment;
        }

        inline void setRTTex2DDepth(uint32_t _width, uint32_t _height, Format _format = Format::R8G8B8A8Unorm, std::uint32_t _sizeOfChannel = 4, bool _isHostVisible = true)
        {
            width = _width;
            height = _height;
            depth = 1;
            dimension = Dimension::two;
            format = _format;
            hostVisible = _isHostVisible;
            format = format;
            sizeOfChannel = _sizeOfChannel;
            usage = ImageUsageBit::DepthStencilAttachment;
        }

        std::uint32_t width;
        std::uint32_t height;
        std::uint32_t depth;
        std::uint32_t sizeOfChannel;
        Format format;
        Dimension dimension;
        ImageUsage usage;
        bool hostVisible;
    };
}

#endif
