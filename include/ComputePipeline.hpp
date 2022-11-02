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

        using Impl = APITrait<API>::BindGroupImpl;

        ComputePipeline(Device<API>& device);
        ~ComputePipeline();

        NONCOPYABLE(ComputePipeline)

        const Impl& getInternalImpl() const;

    private:
        using APIDevice = APITrait<API>::Device;

        APIDevice& mAPIDevice;
        Impl mImpl;
    };
}

#endif
