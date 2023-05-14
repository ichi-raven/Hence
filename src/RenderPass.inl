/*****************************************************************//**
 * @file   RenderPass.inl
 * @brief  RenderPassクラスの実装展開ファイル
 * 
 * @author ichi-raven
 * @date   March 2023
 *********************************************************************/
#ifdef HENCE_RENDERPASS_HPP_

#include "../include/Window.hpp"

namespace Hence
{
	template<typename API>
	RenderPass<API>::RenderPass() noexcept
	{

	}

	template<typename API>
	RenderPass<API>::RenderPass(Device<API>& device, Window<API>& window) noexcept
		//: mAPIDevice(device.getInternalAPIDevice())
		: mImpl(std::make_optional<Impl>(&device.getInternalAPIDevice(), window.getInternalImpl()))
	{

	}

	template<typename API>
	RenderPass<API>::~RenderPass() noexcept
	{

	}

	template<typename API>
	RenderPass<API>::Impl& RenderPass<API>::getInternalImpl() noexcept
	{
		assert(mImpl || !"invalid renderpass! (construct with device first!)");

		return *mImpl;
	}

}

#endif


