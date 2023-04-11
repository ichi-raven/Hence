/*****************************************************************//**
 * @file   ClearValue.hpp
 * @brief  ClearValue類構造体のヘッダファイル
 * 
 * @author ichi-raven
 * @date   April 2023
 *********************************************************************/
#ifndef HENCE_INFO_CLEARVALUE_HPP_
#define HENCE_INFO_CLEARVALUE_HPP_

#include <cstdint>
#include <variant>

namespace Hence
{
    struct ColorClearValue
    {
        std::variant<std::array<float, 4>, std::array<std::int32_t, 4>, std::array<std::uint32_t, 4>> value;
    };

    struct DepthClearValue
    {
        float depth;
        std::uint32_t stencil;
    };
}

#endif 
