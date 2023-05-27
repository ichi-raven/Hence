/*****************************************************************//**
 * @file   ComputePipeline.inl
 * @brief  ComputePipelineクラスの実装展開ファイル
 * 
 * @author ichi-raven
 * @date   May 2023
 *********************************************************************/
#ifdef HENCE_COMPUTEPIPELINE_HPP_

namespace Hence
{

    template<typename API>
    ComputePipeline<API>::ComputePipeline() noexcept
    {

    }

    template<typename API>
    ComputePipeline<API>::ComputePipeline(Device<API>& device, BindLayout<API>& bindLayout, Shader<API>& shader) noexcept
        : mImpl(std::make_optional<Impl>(&device.getInternalAPIDevice(), bindLayout.getInternalImpl(), shader.getInternalImpl()))
    {

    }
    
    template<typename API>
    ComputePipeline<API>::~ComputePipeline() noexcept
    {

    }


    template<typename API>
    ComputePipeline<API>::template Impl& ComputePipeline<API>::getInternalImpl() noexcept
    {
        assert(mImpl || !"invalid compute pipeline! (construct with device first!)");

        return *mImpl;
    }
}

#endif
