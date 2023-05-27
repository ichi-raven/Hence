#ifndef HENCE_COMPUTEPIPELINE_HPP_
#define HENCE_COMPUTEPIPELINE_HPP_

#include "API.hpp"
#include "Utility/Macro.hpp"

namespace Hence
{
    template<typename API>
    class Device;

    template<typename API>
    class ComputePipeline
    {
    public:

        using Impl = APITrait<API>::ComputePipelineImpl;
        
        ComputePipeline() noexcept;
        ComputePipeline(Device<API>& device, BindLayout<API>& bindLayout, Shader<API>& shader) noexcept;
        ~ComputePipeline() noexcept;

        NONCOPYABLE(ComputePipeline)

        Impl& getInternalImpl() noexcept;

    private:
        //using APIDevice = APITrait<API>::Device;

        //APIDevice& mAPIDevice;
        std::optional<Impl> mImpl;
    };
}

#include "../src/ComputePipeline.inl"

#endif

