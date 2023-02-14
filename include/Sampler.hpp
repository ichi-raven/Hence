/*****************************************************************//**
 * @file   Sampler.hpp
 * @brief  Samplerクラスのヘッダファイル
 * 
 * @author ichi-raven
 * @date   December 2022
 *********************************************************************/
#ifndef HENCE_SAMPLER_HPP_
#define HENCE_SAMPLER_HPP_

#include "API.hpp"
#include "Utility/Macro.hpp"

#include "Info/SamplerInfo.hpp"

namespace Hence
{
    // 前方宣言
    template<typename API>
    class Device;

    template<typename API>
    class Sampler
    {
    public:
        // 内部実装型(一般にユーザが使用する必要はない)
        using Impl = APITrait<API>::SamplerImpl;

        Sampler(Device<API> device, const SamplerInfo& samplerInfo) noexcept;

        ~Sampler() noexcept;

        NONCOPYABLE(Sampler)

        const Impl& getInternalImpl() const noexcept;

    private:
        using APIDevice = APITrait<API>::Device;

        APIDevice& mAPIDevice;
        Impl mImpl;
    };
}

#include "../src/Sampler.inl"

#endif
