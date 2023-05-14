/*****************************************************************//**
 * @file   GraphicsPipeline.inl
 * @brief  GraphicsPipelineクラスの実装展開ファイル
 * 
 * @author ichi-raven
 * @date   March 2023
 *********************************************************************/
#ifdef HENCE_GRAPHICSPIPELINE_HPP_

#include "../include/Device.hpp"
#include "../include/RenderPass.hpp"
#include "../include/BindLayout.hpp"
#include "../include/Shader.hpp"

namespace Hence
{
    template <typename API>
    GraphicsPipeline<API>::GraphicsPipeline() noexcept
    {

    }

    template <typename API>
    template<ShaderType<API>... ShaderTypes>
    GraphicsPipeline<API>::GraphicsPipeline(Device<API>& device, const GraphicsPipelineInfo& gpi, RenderPass<API>& renderpass, BindLayout<API>& bindLayout, ShaderTypes&... shaders) noexcept
        //: mAPIDevice(device.getInternalAPIDevice())
        : mImpl(std::make_optional<Impl>(&device.getInternalAPIDevice(), gpi, renderpass.getInternalImpl(), bindLayout.getInternalImpl(), shaders.getInternalImpl()...)) // TODO
    {

    }

    template<typename API>
    GraphicsPipeline<API>::~GraphicsPipeline() noexcept
    {

    }

    template<typename API>
    GraphicsPipeline<API>::Impl& GraphicsPipeline<API>::getInternalImpl() noexcept
    {
        assert(mImpl || !"invalid graphics pipeline! (construct with device first!)");

        return *mImpl;
    }
}

#endif
