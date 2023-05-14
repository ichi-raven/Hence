/*****************************************************************//**
 * @file   RenderPass.hpp
 * @brief  RenderPassクラスのヘッダファイル
 * 
 * @author ichi-raven
 * @date   March 2023
 *********************************************************************/

#ifndef HENCE_RENDERPASS_HPP_
#define HENCE_RENDERPASS_HPP_

#include "API.hpp"
#include "Utility/Macro.hpp"


namespace Hence
{
    template<typename API>
    class Device;

    template<typename API>
    class Image;

    template<typename API>
    class Window;

    template<typename T, typename API>
    concept ImageType = std::same_as<T, Image<API>>;

    template<typename API>
    class RenderPass
    {
    public:
        using Impl = APITrait<API>::RenderPassImpl;

        RenderPass() noexcept;

        RenderPass(Device<API>& device, Window<API>& window) noexcept;

        template<ImageType<API>... ImageTypes>
        RenderPass(Device<API>& device, Image<API> depthTarget, ImageTypes... colorTargets) noexcept;

        ~RenderPass() noexcept;

        NONCOPYABLE(RenderPass)

        Impl& getInternalImpl() noexcept;

    private:
        //using APIDevice = APITrait<API>::Device;

        //APIDevice& mAPIDevice;
        std::optional<Impl> mImpl;
    };
}

#include "../src/RenderPass.inl"

#endif
