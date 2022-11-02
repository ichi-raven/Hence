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
    class RenderPass
    {
    public:
        using Impl = APITrait<API>::RenderPassImpl;

        RenderPass(Device<API>& device);

        ~RenderPass();

        NONCOPYABLE(RenderPass)

        void create(Image& colorTarget, Image& depthTarget);

        void create(std::vector<Image>& colorTargets, Image& depthTarget);

        const Impl& getInternalImpl() const;

    private:
        using APIDevice = APITrait<API>::Device;

        APIDevice& mAPIDevice;
        Impl mImpl;
    };
}

#endif
