#ifndef HENCE_RAYTRACINGPIPELINE_HPP_
#define HENCE_RAYTRACINGPIPELINE_HPP_

#include "API.hpp"
#include "Utility/Macro.hpp"

namespace Hence
{
    template<typename API>
    class Device;

    template<typename API>
    class RaytracingPipeline
    {
    public:

        using Impl = APITrait<API>::RaytracingPipelineImpl;

        RaytracingPipeline() noexcept;

        RaytracingPipeline(Device<API>& device) noexcept;

        ~RaytracingPipeline() noexcept;

        NONCOPYABLE(RaytracingPipeline)

        Impl& getInternalImpl() noexcept;

    private:
        //using APIDevice = APITrait<API>::Device;

        //APIDevice& mAPIDevice;
        Impl mImpl;
    };
}

#endif
