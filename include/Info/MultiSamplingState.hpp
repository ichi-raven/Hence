/*****************************************************************//**
 * @file   MultiSamplingState.hpp
 * @brief  MultiSamplingState構造体のヘッダファイル
 * 
 * @author ichi-raven
 * @date   March 2023
 *********************************************************************/
#ifndef HENCE_INFO_MULTISAMPLINGSTATE_HPP_
#define HENCE_INFO_MULTISAMPLINGSTATE_HPP_

#include <concepts>

namespace Hence
{
    enum class SampleCountFlag
    {
        b1  = 0x00000001,
        b2  = 0x00000002,
        b4  = 0x00000004,
        b8  = 0x00000008,
        b16 = 0x00000010,
        b32 = 0x00000020,
        b64 = 0x00000040,
    };
    
    template<typename T>
    concept SampleCountFlagType = std::same_as<T, SampleCountFlag>;

    struct SampleCount
    {
        //template<SampleCountFlagType... SampleCountFlags>
        //SampleCount(SampleCountFlags... flags)
        //    : flag(static_cast<std::int32_t>(flags) + ... + 0)
        //{
        //    static_assert(sizeof...(SampleCountFlags) > 0, "constructor called by empty flag!");
        //}

        SampleCount(SampleCountFlag flag)
            : flag(static_cast<std::int32_t>(flag))
        {}

        std::int32_t flag;
    };

    struct MultiSampleState
    {
        SampleCount rasterizationSamples;
        bool sampleShadingEnable;
        float minSampleShading;
        std::vector<uint32_t> sampleMasks;
        bool alphaToCoverageEnable;
        bool alphaToOneEnable;
    };
}

#endif
