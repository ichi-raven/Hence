/*****************************************************************//**
 * @file   Format.hpp
 * @brief  Format列挙型を定義するヘッダファイル
 * 
 * @author ichi-raven
 * @date   November 2022
 *********************************************************************/
#ifndef HENCE_USAGE_HPP_
#define HENCE_USAGE_HPP_

#include <cstdint>

/**
 * @brief  リソースのフォーマットを表す
 */
namespace Hence
{
    enum class Format : std::int32_t
    {
        Undefined = 0,
        R4G4UnormPack8,
        R4G4B4A4UnormPack16,
        B4G4R4A4UnormPack16,
        R5G6B5UnormPack16,
        B5G6R5UnormPack16,
        R5G5B5A1UnormPack16,
        B5G5R5A1UnormPack16,
        A1R5G5B5UnormPack16,
        R8Unorm,
        R8SNorm,
        R8UScaled,
        R8SScaled,
        R8UInt,
        R8SInt,
        R8SRGB,
        R8G8Unorm,
        R8G8SNorm,
        R8G8UScaled,
        R8G8SScaled,
        R8G8UInt,
        R8G8SInt,
        R8G8SRGB,
        R8G8B8Unorm,
        R8G8B8SNorm,
        R8G8B8UScaled,
        R8G8B8SScaled,
        R8G8B8UInt,
        R8G8B8SInt,
        R8G8B8SRGB,
        B8G8R8Unorm,
        B8G8R8SNorm,
        B8G8R8UScaled,
        B8G8R8SScaled,
        B8G8R8UInt,
        B8G8R8SInt,
        B8G8R8SRGB,
        R8G8B8A8Unorm,
        R8G8B8A8SNorm,
        R8G8B8A8UScaled,
        R8G8B8A8SScaled,
        R8G8B8A8UInt,
        R8G8B8A8SInt,
        R8G8B8A8SRGB,
        B8G8R8A8Unorm,
        B8G8R8A8SNorm,
        B8G8R8A8UScaled,
        B8G8R8A8SScaled,
        B8G8R8A8UInt,
        B8G8R8A8SInt,
        B8G8R8A8SRGB,
        A8B8G8R8UnormPack32,
        A8B8G8R8SNormPack32,
        A8B8G8R8UScaledPack32,
        A8B8G8R8SScaledPack32,
        A8B8G8R8UIntPack32,
        A8B8G8R8SIntPack32,
        A8B8G8R8SRGBPack32,
        A2R10G10B10UnormPack32,
        A2R10G10B10SNormPack32,
        A2R10G10B10UScaledPack32,
        A2R10G10B10SScaledPack32,
        A2R10G10B10UIntPack32,
        A2R10G10B10SIntPack32,
        A2B10G10R10UnormPack32,
        A2B10G10R10SNormPack32,
        A2B10G10R10UScaledPack32,
        A2B10G10R10SScaledPack32,
        A2B10G10R10UIntPack32,
        A2B10G10R10SIntPack32,
        R16Unorm,
        R16SNorm,
        R16UScaled,
        R16SScaled,
        R16UInt,
        R16SInt,
        R16SFloat,
        R16G16Unorm,
        R16G16SNorm,
        R16G16UScaled,
        R16G16SScaled,
        R16G16UInt,
        R16G16SInt,
        R16G16SFloat,
        R16G16B16Unorm,
        R16G16B16SNorm,
        R16G16B16UScaled,
        R16G16B16SScaled,
        R16G16B16UInt,
        R16G16B16SInt,
        R16G16B16SFloat,
        R16G16B16A16Unorm,
        R16G16B16A16SNorm,
        R16G16B16A16UScaled,
        R16G16B16A16SScaled,
        R16G16B16A16UInt,
        R16G16B16A16SInt,
        R16G16B16A16SFloat,
        R32UInt,
        R32SInt,
        R32SFloat,
        R32G32UInt,
        R32G32SInt,
        R32G32SFloat,
        R32G32B32UInt,
        R32G32B32SInt,
        R32G32B32SFloat,
        R32G32B32A32UInt,
        R32G32B32A32SInt,
        R32G32B32A32SFloat,
        R64UInt,
        R64SInt,
        R64SFloat,
        R64G64UInt,
        R64G64SInt,
        R64G64SFloat,
        R64G64B64UInt,
        R64G64B64SInt,
        R64G64B64SFloat,
        R64G64B64A64UInt,
        R64G64B64A64SInt,
        R64G64B64A64SFloat,
        B10G11R11UFloatPack32,
        E5B9G9R9UFloatPack32,
        D16Unorm,
        X8D24UnormPack32,
        D32SFloat,
        S8UInt,
        D16UnormS8UInt,
        D24UnormS8UInt,
        D32SFloatS8UInt,
        BC1RGBUnormBlock,
        BC1RGBSRGBBlock,
        BC1RGBAUnormBlock,
        BC1RGBASRGBBlock,
        BC2UnormBlock,
        BC2SRGBBlock,
        BC3UnormBlock,
        BC3SRGBBlock,
        BC4UnormBlock,
        BC4SNormBlock,
        BC5UnormBlock,
        BC5SNormBlock,
        BC6HUFloatBlock,
        BC6HSFloatBlock,
        BC7UnormBlock,
        BC7SRGBBlock,
        ETC2R8G8B8UnormBlock,
        ETC2R8G8B8SRGBBlock,
        ETC2R8G8B8A1UnormBlock,
        ETC2R8G8B8A1SRGBBlock,
        ETC2R8G8B8A8UnormBlock,
        ETC2R8G8B8A8SRGBBlock,
        EACR11UnormBlock,
        EACR11SNormBlock,
        EACR11G11UnormBlock,
        EACR11G11SNormBlock,
        ASTC4x4UnormBlock,
        ASTC4x4SRGBBlock,
        ASTC5x4UnormBlock,
        ASTC5x4SRGBBlock,
        ASTC5x5UnormBlock,
        ASTC5x5SRGBBlock,
        ASTC6x5UnormBlock,
        ASTC6x5SRGBBlock,
        ASTC6x6UnormBlock,
        ASTC6x6SRGBBlock,
        ASTC8x5UnormBlock,
        ASTC8x5SRGBBlock,
        ASTC8x6UnormBlock,
        ASTC8x6SRGBBlock,
        ASTC8x8UnormBlock,
        ASTC8x8SRGBBlock,
        ASTC10x5UnormBlock,
        ASTC10x5SRGBBlock,
        ASTC10x6UnormBlock,
        ASTC10x6SRGBBlock,
        ASTC10x8UnormBlock,
        ASTC10x8SRGBBlock,
        ASTC10x10UnormBlock,
        ASTC10x10SRGBBlock,
        ASTC12x10UnormBlock,
        ASTC12x10SRGBBlock,
        ASTC12x12UnormBlock,
        ASTC12x12SRGBBlock,

        // Provided by VK_VERSION_1_1
        G8B8G8R8_422Unorm,
        B8G8R8G8_422Unorm,
        G8B8R8_3Plane420Unorm,
        G8B8R8_2Plane420Unorm,
        G8B8R8_3Plane422Unorm,
        G8B8R8_2Plane422Unorm,
        G8B8R8_3Plane444Unorm,
        R10X6UnormPack16,
        R10X6G10X6Unorm2Pack16,
        R10X6G10X6B10X6A10X6Unorm4Pack16,
        G10X6B10X6G10X6R10X6_422Unorm4Pack16,
        B10X6G10X6R10X6G10X6_422Unorm4Pack16,
        G10X6_B10X6_R10X6_3Plane420Unorm3Pack16,
        G10X6_B10X6R10X6_2Plane420Unorm3Pack16,
        G10X6_B10X6_R10X6_3Plane422Unorm3Pack16,
        G10X6_B10X6R10X6_2Plane422Unorm3Pack16,
        G10X6_B10X6_R10X6_3Plane444Unorm3Pack16,
        R12X4UnormPack16,
        R12X4G12X4Unorm2Pack16,
        R12X4G12X4B12X4A12X4Unorm4Pack16,
        G12X4B12X4G12X4R12X4_422Unorm4Pack16,
        B12X4G12X4R12X4G12X4_422Unorm4Pack16,
        G12X4_B12X4_R12X43Plane420Unorm3Pack16,
        G12X4_B12X4R12X42Plane420Unorm3Pack16,
        G12X4_B12X4_R12X43Plane422Unorm3Pack16,
        G12X4_B12X4R12X42Plane422Unorm3Pack16,
        G12X4_B12X4_R12X43Plane444Unorm3Pack16,
        G16B16G16R16_422Unorm,
        B16G16R16G16_422Unorm,
        G16B16R16_3Plane420Unorm,
        G16B16R16_2Plane420Unorm,
        G16B16R16_3Plane422Unorm,
        G16B16R16_2Plane422Unorm,
        G16B16R16_3Plane444Unorm,
    };
}

#endif
