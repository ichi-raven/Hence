/*****************************************************************//**
 * @file   VulkanRenderPass.hpp
 * @brief  VulkanRenderPassクラスのヘッダファイル
 * 
 * @author ichi-raven
 * @date   March 2023
 *********************************************************************/
#ifndef HENCE_API_VULKAN_VULKANRENDERPASS_HPP_
#define HENCE_API_VULKAN_VULKANRENDERPASS_HPP_


#include "../../Utility/Result.hpp"

#include <vulkan/vulkan.hpp>

#include <vector>

#include "VulkanImage.hpp"

namespace Hence
{
	class VulkanDevice;

	class VulkanWindow;

	template<typename T>
	concept VulkanImageType = std::same_as<T, VulkanImage>;

	class VulkanRenderPass
	{
	public:

		template<VulkanImageType... VulkanImageTypes>
		VulkanRenderPass(VulkanDevice* pVulkanDevice, VulkanImage& depthStencilTarget, VulkanImageTypes&... colorTargets) noexcept
			: mpDevice(pVulkanDevice)
			, mExtent(getVkExtent(colorTargets...))
		{
			static_assert(sizeof...(VulkanImageTypes) > 0, "cannot create renderpass from empty colorTarget!");

			//std::vector<VkImage> colorTargetImages = { colorTargets.getVkImage()...};
			std::vector<VkImageView> imageViews = { colorTargets.getVkImageView()... , depthStencilTarget.getVkImageView()};

			createRenderPass(sizeof...(colorTargets), getVkFormat(colorTargets...), depthStencilTarget.getVkFormat(), VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL);
			createFrameBufferSumUp(imageViews);
		}

		template<VulkanImageType... VulkanImageTypes>
		VulkanRenderPass(VulkanDevice* pVulkanDevice, VulkanImageTypes&... colorTargets) noexcept
			: mpDevice(pVulkanDevice)
			, mExtent(getVkExtent(colorTargets...))
		{
			static_assert(sizeof...(VulkanImageTypes) > 0, "cannot create renderpass from empty colorTarget!");

			//std::vector<VkImage> colorTargetImages = { colorTargets.getVkImage()... };
			std::vector<VkImageView> imageViews = { colorTargets.getVkImageView()... };

			createRenderPass(sizeof...(colorTargets), getVkFormat(colorTargets...), std::nullopt, VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL);
			createFrameBufferSumUp(imageViews);
		}

		VulkanRenderPass(VulkanDevice* pVulaknDevice, VulkanWindow& window) noexcept;

		VkRenderPass getVkRenderPass() noexcept;

		const std::vector<VkFramebuffer>& getVkFrameBuffers() noexcept;

		const VkExtent3D& getVkExtent3D() const noexcept;

		~VulkanRenderPass();

	private:

		Result createRenderPass(const std::size_t colorTargetNum, VkFormat colorFormat, std::optional<VkFormat> depthFormat, VkImageLayout finalLayout) noexcept;

		Result createFrameBufferEach(const std::vector<VkImageView>& colorViews, VkImageView depthView = VK_NULL_HANDLE) noexcept;

		Result createFrameBufferSumUp(const std::vector<VkImageView>& views) noexcept;

		template<VulkanImageType HeadImage, VulkanImageType... TailImages>
		const VkExtent3D& getVkExtent(HeadImage& head, TailImages... tails)
		{
			return head.getVkExtent();
		}

		template<VulkanImageType HeadImage, VulkanImageType... TailImages>
		VkFormat getVkFormat(HeadImage& head, TailImages... tails)
		{
			return head.getVkFormat();
		}

		VulkanDevice* mpDevice;

		VkRenderPass mRenderPass;
		std::vector<VkFramebuffer> mFrameBuffers;
		VkExtent3D mExtent;
	};
}

#endif