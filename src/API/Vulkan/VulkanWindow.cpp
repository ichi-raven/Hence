/*****************************************************************//**
 * @file   VulkanWindow.cpp
 * @brief  VulkanWindowƒNƒ‰ƒX‚ÌŽÀ‘•
 * 
 * @author ichi-raven
 * @date   November 2022
 *********************************************************************/
#include "../../../include/API/Vulkan/VulkanWindow.hpp"
#include "../../../include/API/Vulkan/VulkanDevice.hpp"
#include "../../../include/API/Vulkan/VulkanSemaphore.hpp"
#include "../../../include/API/Vulkan/Utility/Macro.hpp"
#include "../../../include/API/Vulkan/Utility/HelperFunctions.hpp"

#include "../../../include/Utility/Logger.hpp"
#include "../../../include/Utility/Macro.hpp"

namespace Hence
{
	VulkanWindow::VulkanWindow(VulkanDevice* pVulkanDevice, const WindowInfo& windowInfo) noexcept
		: mpDevice(pVulkanDevice)
	{
		assert(pVulkanDevice != nullptr || !"vulkan device is nullptr!");

		mMaxFrameNum = windowInfo.frameCount;
		mMaxFrameInFlight = std::max(1, static_cast<int>(windowInfo.frameCount) - 1);
		mCurrentFrame = 0;
		
		if (FAILED(res, createGLFWWindow(static_cast<int>(windowInfo.width), static_cast<int>(windowInfo.height), windowInfo.windowName, windowInfo.fullScreen)))
		{
			Logger::error("failed to create GLFW Window! (native error : {})", res.nativeResult);
			return;
		}

		if (FAILED(res, createSurface()))
		{
			Logger::error("failed to create VkSurface! (native error : {})", res.nativeResult);
			return;
		}

		if (FAILED(res, createSwapchain(windowInfo.vsync)))
		{
			Logger::error("failed to create VkSwapchain! (native error : {})", res.nativeResult);
			return;
		}

		if (FAILED(res, createSwapchainImages()))
		{
			Logger::error("failed to create VkImages for swapchain! (native error : {})", res.nativeResult);
			return;
		}

		if (FAILED(res, createDepthBuffer()))
		{
			Logger::error("failed to create VkImage for depth buffer! (native error : {})", res.nativeResult);
			return;
		}
	}

	VulkanWindow::~VulkanWindow() noexcept
	{
		const auto& vkDevice = mpDevice->getDevice();
		
		vkDestroyImageView(vkDevice, mDepthBuffer->getVkImageView(), nullptr);
		vkFreeMemory(vkDevice, mDepthBuffer->getVkDeviceMemory(), nullptr);
		vkDestroyImage(vkDevice, mDepthBuffer->getVkImage(), nullptr);

		for (auto& view : mSwapchainImageViews)
		{
			vkDestroyImageView(vkDevice, view, nullptr);
		}

		vkDestroySwapchainKHR(vkDevice, mSwapchain, nullptr);
		Logger::info("destroyed swapchain");
		
		vkDestroySurfaceKHR(mpDevice->getInstance(), mSurface, nullptr);
		Logger::info("destroyed surface");

		glfwDestroyWindow(mpWindow);
		Logger::info("destroyed GLFW window");
		
	}

	inline void VulkanWindow::updateInput() noexcept
	{
		glfwPollEvents();
	}

	inline bool VulkanWindow::focused() const noexcept
	{
		return static_cast<bool>(glfwGetWindowAttrib(mpWindow, GLFW_FOCUSED));
	}

	std::uint32_t VulkanWindow::acquireNextImage(VulkanSemaphore& signalSemaphore) noexcept
	{
		std::uint32_t rtnIndex = 0;

		if (VK_FAILED(res, vkAcquireNextImageKHR(mpDevice->getDevice(), mSwapchain, std::numeric_limits<std::uint64_t>::max(), signalSemaphore.getVkSemaphore(), VK_NULL_HANDLE, &rtnIndex)))
		{
			Logger::error("failed to acquire next image from swapchain! (native error : {})", static_cast<std::int32_t>(res));
			return 0;
		}

		return rtnIndex;
	}

	Result VulkanWindow::present(const std::uint32_t frameBufferIndex, VulkanSemaphore& waitSemaphore) noexcept
	{
		auto vkSem = waitSemaphore.getVkSemaphore();

		// present
		VkPresentInfoKHR presentInfo
		{
			.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR,
			.pNext = nullptr,
			.waitSemaphoreCount		= 1,
			.pWaitSemaphores		= &vkSem,
			.swapchainCount			= 1,
			.pSwapchains			= &mSwapchain,
			.pImageIndices			= &frameBufferIndex,
		};

		if (VK_FAILED(res, vkQueuePresentKHR(mpDevice->getDeviceQueue(), &presentInfo)))
		{
			Logger::error("failed to present queue! (native error : {})", static_cast<std::int32_t>(res));
			return Result(res);
		}

		return Result();
	}

	inline Result VulkanWindow::createGLFWWindow(const int width, const int height, std::string_view windowName, const bool fullscreen) noexcept
	{
		if (fullscreen)
		{
			mpWindow = glfwCreateWindow(width, height, windowName.data(), glfwGetPrimaryMonitor(), nullptr);
		}
		else
		{
			mpWindow = glfwCreateWindow(width, height, windowName.data(), nullptr, nullptr);
		}

		if (!mpWindow)
		{
			Logger::error("failed to create GLFW Window!");
			return Result(0);
		}

		return Result();
	}

	inline Result VulkanWindow::createSurface() noexcept
	{
		const auto vkInstance			= mpDevice->getInstance();
		const auto vkPhysicalDevice		= mpDevice->getPhysicalDevice();
		const auto graphicsQueueIndex	= mpDevice->getGraphicsQueueIndex();

		if (VK_FAILED(res, glfwCreateWindowSurface(vkInstance, mpWindow, nullptr, &mSurface)))
		{
			return Result(static_cast<std::int32_t>(res));
		}

		if (FAILED(res, selectSurfaceFormat(VK_FORMAT_B8G8R8A8_UNORM)))
		{
			Logger::error("failed to select surface format!");
			return res;
		}

		if (VK_FAILED(res, vkGetPhysicalDeviceSurfaceCapabilitiesKHR(vkPhysicalDevice, mSurface, &mSurfaceCaps)))
		{
			Logger::error("failed to get physical device surface capability!");
			return Result(static_cast<std::int32_t>(res));
		}

		VkBool32 isSupport = VK_FALSE;
		if (VK_FAILED(res, vkGetPhysicalDeviceSurfaceSupportKHR(vkPhysicalDevice, graphicsQueueIndex, mSurface, &isSupport)))
		{
			Logger::error("failed to get physical device surface support!");
			return Result(static_cast<std::int32_t>(res));
		}

		if (!isSupport)
		{
			Logger::error("the surface is not supported by this physical device!");
			return Result(0);
		}

		return Result();
	}

	inline Result VulkanWindow::createSwapchain(const bool vsync) noexcept
	{
		const auto vkDevice				= mpDevice->getDevice();
		const auto graphicsQueueIndex	= mpDevice->getGraphicsQueueIndex();

		if (mMaxFrameNum < mSurfaceCaps.minImageCount)
		{
			Logger::error("required frame count is lower than capable minimum surface frame count!");
			Logger::info("minimum frame count : {}", mSurfaceCaps.minImageCount);
			
			return Result(0);
		}

		if (mSurfaceCaps.maxImageCount && mMaxFrameNum > mSurfaceCaps.maxImageCount)
		{
			Logger::error("required frame count is upper than capable maximum surface frame count!");
			Logger::info("maximum frame count : {}", mSurfaceCaps.maxImageCount);
			return Result(0);
		}

		auto& extent = mSurfaceCaps.currentExtent;
		if (extent.width <= 0u || extent.height <= 0u)
		{
			// ignore invalid param and use window size
			int width, height;
			glfwGetWindowSize(mpWindow, &width, &height);
			extent.width = static_cast<uint32_t>(width);
			extent.height = static_cast<uint32_t>(height);
		}

		mPresentMode = VK_PRESENT_MODE_FIFO_KHR;

		uint32_t queueFamilyIndices[] = { graphicsQueueIndex };
		VkSwapchainCreateInfoKHR ci
		{
			.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR,
			.surface = mSurface,
			.minImageCount = mMaxFrameNum,// mSurfaceCaps.minImageCount;
			.imageFormat = mSurfaceFormat.format,
			.imageColorSpace = mSurfaceFormat.colorSpace,
			.imageExtent = extent,
			.imageArrayLayers = 1,
			.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT,
			.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE,
			.queueFamilyIndexCount = 0,
			.preTransform = mSurfaceCaps.currentTransform,
			.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR,
			.presentMode = vsync ? VK_PRESENT_MODE_FIFO_KHR : VK_PRESENT_MODE_IMMEDIATE_KHR,
			.clipped = VK_TRUE,
			.oldSwapchain = VK_NULL_HANDLE
		};

		if (VK_FAILED(res, vkCreateSwapchainKHR(vkDevice, &ci, nullptr, &mSwapchain)))
		{
			Logger::error("failed to create swapchain!");
			return Result(static_cast<std::int32_t>(res));
		}

		mSwapchainExtent = extent;

		return Result();
	}

	inline Result VulkanWindow::createSwapchainImages() noexcept
	{
		const auto vkDevice = mpDevice->getDevice();

		uint32_t imageCount = 0;
		if (VK_FAILED(res, vkGetSwapchainImagesKHR(vkDevice, mSwapchain, &imageCount, nullptr)))
		{
			Logger::error("failed to get swapchain images number!");
			return Result(static_cast<std::int32_t>(res));
		}

		mSwapchainImages.resize(imageCount);
		
		if (VK_FAILED(res, vkGetSwapchainImagesKHR(vkDevice, mSwapchain, &imageCount, mSwapchainImages.data())))
		{
			Logger::error("failed to get swapchain images!");
			return Result(static_cast<std::int32_t>(res));
		}


		{
			
			VkCommandBuffer command = VK_NULL_HANDLE;
			{
				VkCommandBufferAllocateInfo ai
				{
					.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO,
					.commandPool = mpDevice->getCommandPool(),
					.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY,
					.commandBufferCount = 1,
				};
				vkAllocateCommandBuffers(vkDevice, &ai, &command);
			}

			VkCommandBufferBeginInfo commandBI{};
			commandBI.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
			vkBeginCommandBuffer(command, &commandBI);

			for (auto image : mSwapchainImages)
			{
				setImageMemoryBarrier(command, image, VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_PRESENT_SRC_KHR);
			}

			vkEndCommandBuffer(command);

			VkSubmitInfo submitInfo
			{
				.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO,
				.pNext = nullptr,
				.commandBufferCount = 1,
				.pCommandBuffers = &command
			};

			vkQueueSubmit(mpDevice->getDeviceQueue(), 1, &submitInfo, VK_NULL_HANDLE);

			// end copying
			vkDeviceWaitIdle(vkDevice);
			vkFreeCommandBuffers(vkDevice, mpDevice->getCommandPool(), 1, &command);
		}

		mSwapchainImageViews.resize(imageCount);

		for (size_t i = 0; i < imageCount; ++i)
		{
			VkImageViewCreateInfo ci{};
			ci.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
			ci.viewType = VK_IMAGE_VIEW_TYPE_2D;
			ci.format = mSurfaceFormat.format;
			ci.components = 
			{
				VK_COMPONENT_SWIZZLE_IDENTITY,
				VK_COMPONENT_SWIZZLE_IDENTITY,
				VK_COMPONENT_SWIZZLE_IDENTITY,
				VK_COMPONENT_SWIZZLE_IDENTITY,
			};
			ci.subresourceRange = { VK_IMAGE_ASPECT_COLOR_BIT, 0, 1, 0, 1 };
			ci.image = mSwapchainImages[i];

			if (VK_FAILED(res, vkCreateImageView(vkDevice, &ci, nullptr, &mSwapchainImageViews[i])))
			{
				Logger::error("failed to create swapchain image views!");
				return Result(static_cast<std::int32_t>(res));
			}
		}

		return Result();
	}

	inline Result VulkanWindow::createDepthBuffer() noexcept
	{
		const auto vkDevice			= mpDevice->getDevice();
		const auto vkDeviceQueue	= mpDevice->getDeviceQueue();
		const auto vkCommandPool	= mpDevice->getCommandPool();

		VkImage image = VK_NULL_HANDLE;
		{
			VkImageCreateInfo ci
			{
				.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO,
				.pNext = nullptr,
				.imageType = VK_IMAGE_TYPE_2D,
				.format = VK_FORMAT_D32_SFLOAT,
				.extent
					{
						.width = mSwapchainExtent.width,
						.height = mSwapchainExtent.height,
						.depth = 1
					},
				.mipLevels = 1,
				.arrayLayers = 1,
				.samples = VK_SAMPLE_COUNT_1_BIT,
				.usage = VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT,
				.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED
			};


			if (VK_FAILED(res, vkCreateImage(vkDevice, &ci, nullptr, &image)))
			{
				Logger::error("failed to create depth buffer's image");
				return Result(static_cast<std::int32_t>(res));
			}
			
		}

		VkDeviceMemory memory = VK_NULL_HANDLE;
		{
			VkMemoryRequirements reqs;
			vkGetImageMemoryRequirements(vkDevice, image, &reqs);
			VkMemoryAllocateInfo ai{};
			ai.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
			ai.allocationSize = reqs.size;
			ai.memoryTypeIndex = mpDevice->getMemoryTypeIndex(
				reqs.memoryTypeBits, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);

			if (VK_FAILED(res, vkAllocateMemory(vkDevice, &ai, nullptr, &memory)))
			{
				Logger::error("failed to allocate depth buffer's device memory");
				return Result(static_cast<std::int32_t>(res));
			}
			
			if (VK_FAILED(res, vkBindImageMemory(vkDevice, image, memory, 0)))
			{
				Logger::error("failed to bind depth buffer's device memory");
				return Result(static_cast<std::int32_t>(res));
			}
		}

		VkImageView imageView = VK_NULL_HANDLE;
		{
			VkImageViewCreateInfo ci{};
			ci.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
			ci.image = image;
			ci.viewType = VK_IMAGE_VIEW_TYPE_2D;
			ci.format = VK_FORMAT_D32_SFLOAT;
			ci.components = {
				VK_COMPONENT_SWIZZLE_R,
				VK_COMPONENT_SWIZZLE_G,
				VK_COMPONENT_SWIZZLE_B,
				VK_COMPONENT_SWIZZLE_A,
			};
			//ci.subresourceRange = {VK_IMAGE_ASPECT_DEPTH_BIT | VK_IMAGE_ASPECT_STENCIL_BIT, 0, 1, 0, 1};
			ci.subresourceRange = { VK_IMAGE_ASPECT_DEPTH_BIT, 0, 1, 0, 1 };

			if (VK_FAILED(res, vkCreateImageView(vkDevice, &ci, nullptr, &imageView)))
			{
				Logger::error("failed to create depth buffer's vkImageView!");
				return Result(static_cast<std::int32_t>(res));
			}
		}

		auto currentLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;

		// set image layout
		{
			VkCommandBuffer command;
			{
				VkCommandBufferAllocateInfo ai{};
				ai.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
				ai.commandBufferCount = 1;
				ai.commandPool = vkCommandPool;
				ai.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
				vkAllocateCommandBuffers(vkDevice, &ai, &command);
			}

			VkCommandBufferBeginInfo commandBI{};
			commandBI.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
			vkBeginCommandBuffer(command, &commandBI);

			//setImageMemoryBarrier(command, io.mImage.value(), VK_IMAGE_LAYOUT_UNDEFINED,
			//                      io.currentLayout, VK_IMAGE_ASPECT_DEPTH_BIT | VK_IMAGE_ASPECT_STENCIL_BIT);
			setImageMemoryBarrier(command, image, VK_IMAGE_LAYOUT_UNDEFINED,
				VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL, VK_IMAGE_ASPECT_DEPTH_BIT);
			vkEndCommandBuffer(command);

			VkSubmitInfo submitInfo{};
			submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
			submitInfo.commandBufferCount = 1;
			submitInfo.pCommandBuffers = &command;
			vkQueueSubmit(vkDeviceQueue, 1, &submitInfo, VK_NULL_HANDLE);

			// end copying
			vkDeviceWaitIdle(vkDevice);
			vkFreeCommandBuffers(vkDevice, vkCommandPool, 1, &command);
		}

		VkExtent3D extent{ mSwapchainExtent.width, mSwapchainExtent.height, 1 };

		mDepthBuffer.emplace(mpDevice, image, memory, imageView, VK_FORMAT_D32_SFLOAT, extent, 1u);

		return Result();
	}

	inline Result VulkanWindow::selectSurfaceFormat(const VkFormat format) noexcept
	{
		Result result;

		auto physicalDevice = mpDevice->getPhysicalDevice();

		std::uint32_t surfaceFormatCount = 0;  // get count of formats
		if (VK_FAILED(res, vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice, mSurface, &surfaceFormatCount, nullptr)))
		{
			Logger::error("failed to get physical device surface format number!");
			return Result(static_cast<std::int32_t>(res));
		}

		std::vector<VkSurfaceFormatKHR> formats(surfaceFormatCount);  // get actual format

		if (VK_FAILED(res, vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice, mSurface, &surfaceFormatCount, formats.data())))
		{
			Logger::error("failed to get physical device surface format!");
			return Result(static_cast<std::int32_t>(res));
		}

		// search matched format
		for (const auto& f : formats)
		{
			if (f.format == format)
			{
				mSurfaceFormat = f;
				return Result();
			}
		}

		Logger::error("all physical device surface format did not match with requested format!");
		return Result(0);
	}

	const std::vector<VkImage>& VulkanWindow::getVkSwapchainImages() noexcept
	{
		return mSwapchainImages;
	}

	const std::vector<VkImageView>& VulkanWindow::getVkSwapchainImageViews() noexcept
	{
		return mSwapchainImageViews;
	}

	const VkExtent2D& VulkanWindow::getVkSwapchainExtent() noexcept
	{
		return mSwapchainExtent;
	}

	VkFormat VulkanWindow::getVkFormat() noexcept
	{
		return mSurfaceFormat.format;
	}

	VulkanImage& VulkanWindow::getDepthBuffer() noexcept
	{
		return *mDepthBuffer;
	}

}
