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
		VulkanRenderPass(VulkanDevice& device, VulkanImage& depthStencilTarget, VulkanImageTypes&... colorTargets) noexcept
			: mDevice(device)
			, mExtent(getVkExtent(colorTargets...))
		{
			static_assert(sizeof...(VulkanImageTypes) > 0, "cannot create renderpass from empty colorTarget!");

			//std::vector<VkImage> colorTargetImages = { colorTargets.getVkImage()...};
			std::vector<VkImageView> imageViews = { colorTargets.getVkImageView()... , depthStencilTarget.getVkImageView()};

			createRenderPass(sizeof...(colorTargets), getVkFormat(colorTargets...), depthStencilTarget.getVkFormat());
			createFrameBuffer(imageViews);
		}

		template<VulkanImageType... VulkanImageTypes>
		VulkanRenderPass(VulkanDevice& device, VulkanImageTypes&... colorTargets) noexcept
			: mDevice(device)
			, mExtent(getVkExtent(colorTargets...))
		{
			static_assert(sizeof...(VulkanImageTypes) > 0, "cannot create renderpass from empty colorTarget!");

			//std::vector<VkImage> colorTargetImages = { colorTargets.getVkImage()... };
			std::vector<VkImageView> imageViews = { colorTargets.getVkImageView()... };

			createRenderPass(sizeof...(colorTargets), getVkFormat(colorTargets...), std::nullopt);
			createFrameBuffer(imageViews);
		}

		VulkanRenderPass(VulkanDevice& device, VulkanWindow& window) noexcept;

		VkRenderPass getVkRenderPass() noexcept;

		const std::vector<VkFramebuffer>& getVkFrameBuffers() noexcept;

		const VkExtent3D& getVkExtent3D() const noexcept;

		~VulkanRenderPass();

	private:

		inline Result createRenderPass(const std::size_t colorTargetNum, VkFormat colorFormat, std::optional<VkFormat> depthFormat) noexcept;

		inline Result createFrameBuffer(const std::vector<VkImageView>& views) noexcept;

		template<VulkanImageType HeadImage, VulkanImageType... TailImages>
		inline const VkExtent3D& getVkExtent(HeadImage& head, TailImages... tails)
		{
			return head.getVkExtent();
		}

		template<VulkanImageType HeadImage, VulkanImageType... TailImages>
		inline VkFormat getVkFormat(HeadImage& head, TailImages... tails)
		{
			return head.getVkFormat();
		}

		VulkanDevice& mDevice;

		VkRenderPass mRenderPass;
		std::vector<VkFramebuffer> mFrameBuffers;
		VkExtent3D mExtent;
	};
}

#endif