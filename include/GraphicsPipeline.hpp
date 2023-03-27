#ifndef HENCE_GRAPHICSPIPELINE_HPP_
#define HENCE_GRAPHICSPIPELINE_HPP_

#include "API.hpp"
#include "Utility/Macro.hpp"

#include "Info/GraphicsPipelineInfo.hpp"

namespace Hence
{
    template<typename API>
    class Device;

    template<typename API>
    class RenderPass;

    template<typename API>
    class BindLayout;

    template<typename API>
    class Shader;

    template<typename T, typename API>
    concept ShaderType = std::same_as<Shader<API>, T>;

    template<typename API>
    class GraphicsPipeline
    {
    public:

        using Impl = APITrait<API>::GraphicsPipelineImpl;

        template<ShaderType<API>... ShaderTypes>
        GraphicsPipeline(Device<API>& device, const GraphicsPipelineInfo& gpi, RenderPass<API>& renderpass, BindLayout<API>& bindLayout, ShaderTypes... shaders) noexcept;
        
        ~GraphicsPipeline() noexcept;

        NONCOPYABLE(GraphicsPipeline)

        Impl& getInternalImpl() noexcept;

    private:
        using APIDevice = APITrait<API>::Device;

        APIDevice& mAPIDevice;
        Impl mImpl;
    };
}

#include "../src/GraphicsPipeline.inl"

#endif
