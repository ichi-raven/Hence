#ifndef HENCE_COMMAND_HPP_
#define HENCE_COMMAND_HPP_

#include "API.hpp"
#include "Utility/Macro.hpp"

namespace Hence
{
    template<typename API>
    class Device;

    template<typename API>
    class GraphicsPipeline;

    template<typename API>
    class ComputePipeline;

    template<typename API>
    class RaytracingPipeline;

    template<typename API>
    class Command
    {
    public:

        using Impl = APITrait<API>::CommandImpl;

        Command(Device<API>& device);
        ~Command();

        NONCOPYABLE(Command)

        void begin(RenderPass& renderpass);

        void beginCompute();

        void end();

        void setGraphicsPipeline(const GraphicsPipeline<API>& pipeline);

        void setComputePipeline(const ComputePipeline<API>& pipeline);

        void setRaytracingPipeline(const RaytracingPipeline<API>& pipeline);

        void render();

        void renderIndexed();

        void execute();

        const Impl& getInternalImpl() const;

    private:
        using APIDevice = APITrait<API>::Device;

        APIDevice& mDevice;
        Impl mImpl;
    };
}

#endif
