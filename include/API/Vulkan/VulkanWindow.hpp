#ifndef HENCE_API_VULKAN_VULKANWINDOW_HPP_
#define HENCE_API_VULKAN_VULKANWINDOW_HPP_

#include "../../Info/WindowInfo.hpp"
#include "../../Utility/Result.hpp"

#include "VulkanImage.hpp"

#include <vulkan/vulkan.hpp>
#include <GLFW/glfw3.h>

#include <memory>
#include <optional>

namespace Hence
{
    class VulkanDevice;

	class VulkanWindow
	{
	public:

        VulkanWindow(VulkanDevice& vulkanDevice, const WindowInfo& windowInfo) noexcept;

		inline void updateInput() noexcept;

		inline bool focused() const noexcept;

	private:

        inline Result createGLFWWindow(const int width, const int height, std::string_view windowName, const bool fullscreen) noexcept;

        inline Result createSurface() noexcept;

        inline Result createSwapchain(const bool vsync) noexcept;

        inline Result createSwapchainImages() noexcept;

        inline Result createDepthBuffer() noexcept;

        inline Result selectSurfaceFormat(const VkFormat format) noexcept;

        inline Result setImageMemoryBarrier(VkCommandBuffer command, VkImage image,
            VkImageLayout oldLayout,
            VkImageLayout newLayout,
            VkImageAspectFlags aspectFlags) const noexcept;

        VulkanDevice& mDevice;

        GLFWwindow*                     mpWindow;
        VkSurfaceKHR                    mSurface;
        VkSwapchainKHR                  mSwapchain;
        VkSurfaceCapabilitiesKHR        mSurfaceCaps;
        VkSurfaceFormatKHR              mSurfaceFormat;
        VkPresentModeKHR                mPresentMode;
        VkExtent2D                      mSwapchainExtent;
        std::vector<VkImage>            mSwapchainImages;
        std::vector<VkImageView>        mSwapchainImageViews;
        std::optional<VulkanImage>      mDepthBuffer;

        //現在のフレーム(注意 : 処理中のフレームバッファのインデックスとは関係ない)
        uint32_t mCurrentFrame;
        //フレームの個数
        uint32_t mMaxFrameNum;
        //同時処理可能なフレーム数
        uint32_t mMaxFrameInFlight;
	};
}

#endif