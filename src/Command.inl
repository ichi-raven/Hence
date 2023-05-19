/*****************************************************************//**
 * @file   Command.inl
 * @brief  Commandクラスの実装展開ファイル
 * 
 * @author ichi-raven
 * @date   April 2023
 *********************************************************************/
#ifdef HENCE_COMMAND_HPP_

namespace Hence
{
	template<typename API>
	Command<API>::Command() noexcept
	{

	}


	template<typename API>
	Command<API>::Command(Device<API>& device) noexcept
		//: mAPIDevice(device.getInternalAPIDevice())
		: mImpl(std::make_optional<Impl>(&device.getInternalAPIDevice()))
	{
		
	}

	template<typename API>
	Command<API>::~Command() noexcept
	{

	}
	
	template<typename API>
	Command<API>::Command(Command<API>&& src) noexcept
		//: mAPIDevice(src.mAPIDevice)
		: mImpl(std::move(src.mImpl))
	{

	}

	template<typename API>
	Command<API>& Command<API>::operator=(Command<API>&& src) noexcept
	{
		//mAPIDevice = src.mAPIDevice;
		mImpl = std::move(src.mImpl);

		return *this;
	}

	template<typename API>
	Result Command<API>::begin(RenderPass<API>& renderpass, const uint32_t frameBufferIndex, ArrayProxy<ColorClearValue> ccvs, const DepthClearValue& dcv) noexcept
	{
		assert(mImpl || !"invalid command! (construct with device first!)");
		
		return mImpl->begin(renderpass.getInternalImpl(), frameBufferIndex, ccvs, dcv);
	}

	template<typename API>
	Result Command<API>::end() noexcept
	{
		assert(mImpl || !"invalid command! (construct with device first!)");

		return mImpl->end();
	}

	template<typename API>
	Result Command<API>::setGraphicsPipeline(GraphicsPipeline<API>& pipeline) noexcept
	{
		assert(mImpl || !"invalid command! (construct with device first!)");

		return mImpl->setGraphicsPipeline(pipeline.getInternalImpl());
	}

	template<typename API>
	Result Command<API>::setBindGroup(BindGroup<API>& bindGroup, const std::uint8_t space) noexcept
	{
		assert(mImpl || !"invalid command! (construct with device first!)");

		return mImpl->setBindGroup(bindGroup.getInternalImpl(), space);
	}

	template<typename API>
	Result Command<API>::setVertexBuffer(Buffer<API>& vertexBuffer) noexcept
	{
		assert(mImpl || !"invalid command! (construct with device first!)");

		return mImpl->setVertexBuffer(vertexBuffer.getInternalImpl());
	}

	template<typename API>
	Result Command<API>::setIndexBuffer(Buffer<API>& indexBuffer) noexcept
	{
		return mImpl.setIndexBuffer(indexBuffer.getInternalImpl());
	}

	template<typename API>
	Result Command<API>::render(const std::uint32_t vertexCount, const std::uint32_t instanceCount, const std::uint32_t firstVertex, const std::uint32_t firstInstance) noexcept
	{
		assert(mImpl || !"invalid command! (construct with device first!)");

		return mImpl->render(vertexCount, instanceCount, firstVertex, firstInstance);
	}

	template<typename API>
	Result Command<API>::renderIndexed(const std::uint32_t indexCount, const std::uint32_t instanceCount, const std::uint32_t firstIndex, const std::uint32_t vertexOffset, const std::uint32_t firstInstance) noexcept
	{
		assert(mImpl || !"invalid command! (construct with device first!)");

		return mImpl->renderIndexed(indexCount, instanceCount, firstIndex, vertexOffset, firstInstance);
	}

	template<typename API>
	Result Command<API>::barrier(Image<API>& image, ImageLayout from, ImageLayout to) noexcept
	{
		assert(mImpl || !"invalid command! (construct with device first!)");

		return mImpl->barrier(image, from, to);
	}

	template<typename API>
	Result Command<API>::execute(Semaphore<API>& waitSemaphore, Semaphore<API>& signalSemaphore) noexcept
	{
		assert(mImpl || !"invalid command! (construct with device first!)");

		return mImpl->execute(waitSemaphore.getInternalImpl(), signalSemaphore.getInternalImpl());
	}

	template<typename API>
	Command<API>::template Impl& Command<API>::getInternalImpl() noexcept
	{
		assert(mImpl || !"invalid command! (construct with device first!)");

		return *mImpl;
	}
}

#endif
