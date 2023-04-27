/*****************************************************************//**
 * @file   VulkanCommand.hpp
 * @brief  VulkanCommandクラスの実装
 *
 * @author ichi-raven
 * @date   April 2023
 *********************************************************************/

#include "../../../include/Utility/Logger.hpp"

#include "../../../include/API/Vulkan/VulkanCommand.hpp"
#include "../../../include/API/Vulkan/VulkanDevice.hpp"
#include "../../../include/API/Vulkan/VulkanRenderPass.hpp"
#include "../../../include/API/Vulkan/VulkanGraphicsPipeline.hpp"
#include "../../../include/API/Vulkan/VulkanBindGroup.hpp"
#include "../../../include/API/Vulkan/VulkanBuffer.hpp"

#include "../../../include/API/Vulkan/Utility/Macro.hpp"


namespace Hence
{
	VulkanCommand::VulkanCommand(VulkanDevice& device) noexcept
		: mDevice(device)
	{
		{
			VkCommandBufferAllocateInfo ai
			{
				.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO,
				.pNext = nullptr,
				.commandPool = mDevice.getCommandPool(),
				.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY,
				.commandBufferCount = 1,
			};

			if (VK_FAILED(res, vkAllocateCommandBuffers(mDevice.getDevice(), &ai, &mCommandBuffer)))
			{
				Logger::error("failed to allocate command buffer! (native result : {})", static_cast<std::int32_t>(res));
				return;
			}
		}

		{
			VkFenceCreateInfo ci
			{
				.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO,
				.pNext = nullptr,
				.flags = 0
			};

			if (VK_FAILED(res, vkCreateFence(mDevice.getDevice(), &ci, nullptr, &mFence)))
			{
				Logger::error("failed to create fences! (native result : {})", static_cast<std::int32_t>(res));
				return;
			}
		}


	}

	VulkanCommand::~VulkanCommand() noexcept
	{

		if (VK_FAILED(res, vkWaitForFences(mDevice.getDevice(), 1, &mFence, VK_TRUE, std::numeric_limits<std::uint64_t>::max())))
		{
			Logger::error("failed to wait fences! (native result : {})", static_cast<std::int32_t>(res));
			return;
		}

		vkDestroyFence(mDevice.getDevice(), mFence, nullptr);

		vkFreeCommandBuffers(mDevice.getDevice(), mDevice.getCommandPool(), 1, &mCommandBuffer);
	}

	Result VulkanCommand::begin(VulkanRenderPass& renderpass, const std::uint32_t frameBufferIndex, ArrayProxy<ColorClearValue> ccvs, const std::optional<DepthClearValue>& dcv) noexcept
	{
		// begin
		VkCommandBufferBeginInfo bi
		{
			.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO,
			.pNext = nullptr,
			.flags = VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT,
			.pInheritanceInfo = nullptr,
		};

		if (VK_FAILED(res, vkBeginCommandBuffer(mCommandBuffer, &bi)))
		{
			Logger::error("failed to begin command buffer! (native result ; {})", static_cast<std::uint32_t>(res));

			return Result(static_cast<std::int32_t>(res));
		}


		// renderpass
		VkRect2D area;
		{
			const auto& ext = renderpass.getVkExtent3D();

			area.offset =
			{
				.x = 0,
				.y = 0
			};

			area.extent =
			{
				.width = ext.width,
				.height = ext.height
			};
		}


		{
			const auto& frameBuffers = renderpass.getVkFrameBuffers();

			std::vector<VkClearValue> cvs(ccvs.size() + static_cast<std::size_t>(!!dcv));

			for (std::size_t i = 0; const auto & cv : ccvs)
			{
				switch (cv.index())
				{
				case 0: // float
					std::memcpy(cvs[i].color.float32, std::get<0>(cv).data(), sizeof(float) * 4);
					break;
				case 1: // int32_t
					std::memcpy(cvs[i].color.int32, std::get<1>(cv).data(), sizeof(std::int32_t) * 4);
					break;
				case 2: // uint32_t 
					std::memcpy(cvs[i].color.uint32, std::get<2>(cv).data(), sizeof(std::uint32_t) * 4);
					break;
				default:
					Logger::error("invalid color clear value variant type!");
					return Result(0);
					break;
				}
				++i;
			}

			if (dcv)
			{
				cvs.back().depthStencil =
				{
					.depth = dcv->depth,
					.stencil = dcv->stencil,
				};
			}

			VkRenderPassBeginInfo bi
			{
				.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO,
				.pNext = nullptr,
				.renderPass = renderpass.getVkRenderPass(),
				.framebuffer = frameBuffers.at(frameBufferIndex),
				.renderArea = area,
				.clearValueCount = cvs.size(),
				.pClearValues = cvs.data(),
			};


			vkCmdBeginRenderPass(mCommandBuffer, &bi, VK_SUBPASS_CONTENTS_INLINE);

		}

		return Result();
	}

	Result VulkanCommand::end()
	{

		vkEndCommandBuffer(mCommandBuffer);

		return Result();
	}

	Result VulkanCommand::setGraphicsPipeline(VulkanGraphicsPipeline& pipeline) noexcept
	{
		vkCmdBindPipeline(mCommandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline.getVkPipeline());
	}

	Result VulkanCommand::setBindGroup(VulkanGraphicsPipeline& pipeline, VulkanBindGroup& bindGroup, const std::uint8_t space = 0) noexcept
	{
		const auto& sets = bindGroup.getDescriptorSets();

		vkCmdBindDescriptorSets
		(
			mCommandBuffer,
			VK_PIPELINE_BIND_POINT_GRAPHICS,
			pipeline.getVkPipelineLayout(),
			0,
			sets.size(),
			sets.data(),
			0,
			nullptr
		);


		return Result();
	}


	Result VulkanCommand::setVertexBuffer(VulkanBuffer& vertexBuffer) noexcept
	{
		VkBuffer vb = vertexBuffer.getVkBuffer();

		vkCmdBindVertexBuffers(mCommandBuffer, 0, 1, &vb, nullptr);

		return Result();
	}

	Result VulkanCommand::setIndexBuffer(VulkanBuffer& indexBuffer) noexcept
	{

		vkCmdBindIndexBuffer(mCommandBuffer, indexBuffer.getVkBuffer(), 0, VK_INDEX_TYPE_UINT32);

		return Result();
	}

	Result VulkanCommand::render(const std::uint32_t vertexCount, const std::uint32_t instanceCount, const std::uint32_t firstVertex, const std::uint32_t firstInstance) noexcept
	{

		vkCmdDraw(mCommandBuffer, vertexCount, instanceCount, firstVertex, firstInstance);

		return Result();
	}

	Result VulkanCommand::renderIndexed(const std::uint32_t indexCount, const std::uint32_t instanceCount, const std::uint32_t firstIndex, const std::uint32_t vertexOffset, const std::uint32_t firstInstance) noexcept
	{

		vkCmdDrawIndexed(mCommandBuffer, indexCount, instanceCount, firstIndex, vertexOffset, firstInstance);

		return Result();
	}

	Result VulkanCommand::execute() noexcept
	{

		if (VK_FAILED(res, vkWaitForFences(mDevice.getDevice(), 1, &mFence, VK_TRUE, std::numeric_limits<std::uint64_t>::max())))
		{
			Logger::error("failed to wait previous fence!");
			return Result(static_cast<std::int32_t>(res));
		}

		if (VK_FAILED(res, vkAcquireNextImageKHR(mDevice, wo.mSwapchain.value(), std::numeric_limits<std::uint64_t>::max(), rpo.mPresentCompletedSems[wo.mCurrentFrame], VK_NULL_HANDLE, &mNowFrameBufferIndex)))
		{

		}

		VkPipelineStageFlags waitDstStageMasks[] = { VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };
		
		VkSubmitInfo submitInfo
		{
			.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO,
			.pNext = nullptr,
			.waitSemaphoreCount = 1,
			.pWaitSemaphores = {},
			.pWaitDstStageMask = waitDstStageMasks,
			.commandBufferCount = 1,
			.pCommandBuffers = &mCommandBuffer,
			.signalSemaphoreCount = 1,
			.pSignalSemaphores = {}
		};

		if (VK_FAILED(res, vkQueueSubmit(mDevice.getDeviceQueue(), 1, &submitInfo, mFence)))
		{
			Logger::error("failed to submit command!");
			return Result(static_cast<std::int32_t>(res));
		}
	}
}
