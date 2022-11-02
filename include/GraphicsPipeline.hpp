#ifndef HENCE_GRAPHICSPIPELINE_HPP_
#define HENCE_GRAPHICSPIPELINE_HPP_

#include "API.hpp"
#include "Utility/Macro.hpp"

namespace Hence
{
    template<typename API>
    class Device;

    template<typename API>
    class GraphicsPipeline
    {
    public:

        using Impl = APITrait<API>::GraphicsPipelineImpl;

        GraphicsPipeline(Device<API>& device);
        ~GraphicsPipeline();

        NONCOPYABLE(GraphicsPipeline)

        const Impl& getInternalImpl() const;

    private:
        using APIDevice = APITrait<API>::Device;

        APIDevice& mAPIDevice;
        Impl mImpl;
    };
}

#endif
