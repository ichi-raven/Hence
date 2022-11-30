/*****************************************************************//**
 * @file   WindowInfo.hpp
 * @brief  WindowInfo構造体のヘッダファイル
 * 
 * @author ichi-raven
 * @date   November 2022
 *********************************************************************/
#ifndef HENCE_INFO_WINDOWINFO_HPP_
#define HENCE_INFO_WINDOWINFO_HPP_

#include <cstdint>
#include <string_view>

namespace Hence
{
    struct WindowInfo
    {
        WindowInfo() noexcept;

        WindowInfo(const std::uint32_t width, const std::uint32_t height, const std::uint32_t frameCount, const std::string_view windowName, bool fullScreen = false, bool vsync = true) noexcept;

        WindowInfo(const std::uint32_t width, const std::uint32_t height, const std::uint32_t frameCount, const char* windowName, bool fullScreen = false, bool vsync = true) noexcept;

        std::uint32_t width;
        std::uint32_t height;
        std::uint32_t frameCount;
        std::string_view windowName;
        bool vsync;
        bool fullScreen;
    };
}

#endif
