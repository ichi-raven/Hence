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

	class VulkanRenderPass
	{
	public:

		template<typename... VulkanImageType>
		VulkanRenderPass(VulkanDevice& device, VulkanImageType&... colorTargets, VulkanImage& depthStencilTarget) noexcept
			: mDevice(device)
		{
			static_assert(sizeof...(VulkanImageType) > 0, "cannot create renderpass from empty colorTarget!");

			std::vector<VkImage> colorTargetImages = { colorTargets.getVkImage()...};
			std::vector<VkImageView> colorTargetImageViews = { colorTargets.getVkImageView()... };

			createRenderPass(colorTargetImages, depthStencilTarget.getVkImage(), getVkFormat(colorTargetImages...), depthStencilTarget.getVkFormat());
			createFrameBuffer(colorTargetImageViews, getVkExtent(colorTargets...));
		}

		VulkanRenderPass(VulkanDevice& device, VulkanWindow& window) noexcept;


		~VulkanRenderPass();

	private:

		inline Result createRenderPass(const std::vector<VkImage>& colorTargets, VkImage depthTarget, VkFormat colorFormat, VkFormat depthFormat) noexcept;

		inline Result createFrameBuffer(const std::vector<VkImageView>& ctViews, const VkExtent3D& extent) noexcept;

		template<typename HeadImage, typename... TailImages>
		inline const VkExtent3D& getVkExtent(HeadImage& head, TailImages... tails)
		{
			return head.getVkExtent();
		}

		template<typename HeadImage, typename... TailImages>
		inline VkFormat getVkFormat(HeadImage& head, TailImages... tails)
		{
			return head.getVkFormat();
		}

		VulkanDevice& mDevice;

		VkRenderPass mRenderPass;
		std::vector<VkFramebuffer> mFrameBuffers;
	};
}

#endif