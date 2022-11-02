#ifndef HENCE_BINDGROUP_HPP_
#define HENCE_BINDGROUP_HPP_

#include "API.hpp"
#include "Utility/Macro.hpp"

namespace Hence
{
    template<typename API>
    class Device;

    template<typename API>
    class Buffer;

    template<typename API>
    class Image;

    template<typename API>
    class BindGroup
    {
    public:

        using Impl = APITrait<API>::BindGroupImpl;

        BindGroup(Device<API>& device, const Shader& shader);
        ~BindGroup();

        NONCOPYABLE(BindGroup)


        bind(uint8_t slot, const Buffer<API>& buffer);
        bind(uint8_t slot, const Image<API>& image);

        const Impl& getInternalImpl() const;

    private:
        using APIDevice = APITrait<API>::Device;

        APIDevice& mAPIDevice;
        Impl mImpl;
    };
}

#endif
