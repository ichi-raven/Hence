/*****************************************************************//**
 * @file   VulkanDevice.cpp
 * @brief  VulkanDeviceクラスの実装
 *
 * @author ichi-raven
 * @date   November 2022
 *********************************************************************/

#include "../../../include/API/Vulkan/VulkanDevice.hpp"

#include "../../../include/Utility/Constants.hpp"
#include "../../../include/Utility/Logger.hpp"
#include "../../../include/Utility/Macro.hpp"

#include "../../../include/API/Vulkan/Utility/Macro.hpp"

#include <GLFW/glfw3.h>

#include <vector>
#include <optional>
// DEBUG
#include <iostream>

namespace Hence
{
	VulkanDevice::VulkanDevice() noexcept
	{
		if (FAILED(res, createInstance()))
		{
			Logger::error("failed to create VkInstance!(native error : {})", res.nativeResult);
			return;
		}

		if (FAILED(res, initializeGLFW()))
		{
			Logger::error("failed to initialize GLFW!(native error : {})", res.nativeResult);
			return;
		}

#ifndef NDEBUG
		
		if (FAILED(res, enableDebugReport()))
		{
			Logger::error("failed to create VkDebugReportCallbackEXT!(native error : {})", res.nativeResult);
			return;
		}
#endif
		
		if (FAILED(res, selectPhysicalDevice()))
		{
			Logger::error("failed to select suitable VkPhysicalDevice!(native error : {})", res.nativeResult);
			return;
		}

		
		if (FAILED(res, createDevice()))
		{
			Logger::error("failed to create VkDevice!(native error : {})", res.nativeResult);
			return;
		}

		
		if (FAILED(res, createCommandPool()))
		{
			Logger::error("failed to create VkCommandPool!(native error : {})", res.nativeResult);
			return;
		}

		if (FAILED(res, createDescriptorPool()))
		{
			Logger::error("failed to create VkDescriptorPool!(native error : {})", res.nativeResult);
			return;
		}
	}

	VulkanDevice::~VulkanDevice() noexcept
	{

		if (VK_FAILED(res, vkDeviceWaitIdle(mDevice)))
		{
			Logger::error("failed to wait device idol! (native result : {})", static_cast<std::int32_t>(res));
		}

		vkDestroyDescriptorPool(mDevice, mDescriptorPool, nullptr);
		Logger::info("destroyed descriptor pool");

		vkDestroyCommandPool(mDevice, mCommandPool, nullptr);
		Logger::info("destroyed command pool");

#ifndef NDEBUG
		disableDebugReport();
		Logger::info("disabled debug report");
#endif

		vkDestroyDevice(mDevice, nullptr);
		Logger::info("destroyed device");

		vkDestroyInstance(mInstance, nullptr);
		Logger::info("destroyed instance");
	}

	VkInstance VulkanDevice::getInstance() noexcept
	{
		return mInstance;
	}

	VkPhysicalDevice VulkanDevice::getPhysicalDevice() noexcept
	{
		return mPhysDev;
	}

	VkDevice VulkanDevice::getDevice() noexcept
	{
		return mDevice;
	}

	VkQueue VulkanDevice::getDeviceQueue() noexcept
	{
		return mDeviceQueue;
	}

	std::uint32_t VulkanDevice::getGraphicsQueueIndex() const noexcept
	{
		return mGraphicsQueueIndex;
	}

	VkCommandPool VulkanDevice::getCommandPool() noexcept
	{
		return mCommandPool;
	}

	VkDescriptorPool VulkanDevice::getDescriptorPool() noexcept
	{
		return mDescriptorPool;
	}

	VkPhysicalDeviceMemoryProperties VulkanDevice::getPhysMemProps() const noexcept
	{
		return mPhysMemProps;
	}

	std::uint32_t VulkanDevice::getMemoryTypeIndex(std::uint32_t requestBits, VkMemoryPropertyFlags requestProps) const noexcept
	{
		std::uint32_t result = 0;
		for (std::uint32_t i = 0; i < mPhysMemProps.memoryTypeCount; ++i)
		{
			if (requestBits & 1)
			{
				const auto& types = mPhysMemProps.memoryTypes[i];
				if ((types.propertyFlags & requestProps) == requestProps)
				{
					result = i;
					break;
				}
			}

			requestBits >>= 1;
		}
		return result;
	}

	inline Result VulkanDevice::createInstance() noexcept
	{
		std::vector<const char*> extensions;
		VkApplicationInfo appInfo{};
		appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
		appInfo.pApplicationName = kEngineName;
		appInfo.pEngineName = kEngineName;
		appInfo.apiVersion = VK_API_VERSION_1_2;
		appInfo.engineVersion = VK_MAKE_API_VERSION(kVersion[0], kVersion[1], kVersion[2], kVersion[3]);

		// エクステンションプロパティ取得
		std::vector<VkExtensionProperties> props;

		{
			uint32_t count = 0;
			if (VK_FAILED(res, vkEnumerateInstanceExtensionProperties(nullptr, &count, nullptr)))
			{
				return Result(res);
			}

			props.resize(count);
			
			if (VK_FAILED(res, vkEnumerateInstanceExtensionProperties(nullptr, &count, props.data())))
			{
				return Result(res);
			}

			Logger::info("enabled extensions : ");

			extensions.reserve(props.size());
			for (const auto& v : props)
			{
				extensions.emplace_back(v.extensionName);
				Logger::info("{}", v.extensionName);
			}
		}

		VkInstanceCreateInfo ci{};
		ci.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
		ci.enabledExtensionCount = uint32_t(extensions.size());
		ci.ppEnabledExtensionNames = extensions.data();
		ci.pApplicationInfo = &appInfo;

#ifndef NDEBUG
		// デバッグレイヤ名
		const char* layers[] = { "VK_LAYER_KHRONOS_validation" };
		{
			ci.enabledLayerCount = 1;
			ci.ppEnabledLayerNames = layers;
		}
#else
		{
			ci.enabledLayerCount = 0;
			ci.ppEnabledLayerNames = nullptr;
		}
#endif

		VkInstance instance = VK_NULL_HANDLE;

		if (VK_FAILED(res, vkCreateInstance(&ci, nullptr, &instance)))
		{
#ifndef NDEBUG

			Logger::warn("failed to enable debug layer! creating VkInstance without debug layer...");
			ci.enabledLayerCount = 0;
			ci.ppEnabledLayerNames = nullptr;

			if (VK_FAILED(res, vkCreateInstance(&ci, nullptr, &instance)))
			{
				return Result(res);
			}
#else
			return Result(res);
#endif
		}

		mInstance = instance;

		return Result();
	}

	inline Result VulkanDevice::initializeGLFW() noexcept
	{

		if (glfwInit() != GLFW_TRUE)
		{
			Logger::error("failed to initialize GLFW!\n");
			return Result(0);
		}

		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

		return Result();
	}

	inline Result VulkanDevice::selectPhysicalDevice() noexcept
	{
		std::uint32_t devCount = 0;

		if (VK_FAILED(res, vkEnumeratePhysicalDevices(mInstance, &devCount, nullptr)))
		{
			return Result(res);
		}

		std::vector<VkPhysicalDevice> physDevs(devCount);

		if (VK_FAILED(res, vkEnumeratePhysicalDevices(mInstance, &devCount, physDevs.data())))
		{
			return Result(res);
		}

		Logger::info("physical device number : {}", physDevs.size());

		mPhysDev = VK_NULL_HANDLE;

		for (const auto& pd : physDevs)
		{
			std::optional<uint32_t> index;

			uint32_t queueFamilyCount = 0;
			vkGetPhysicalDeviceQueueFamilyProperties(pd, &queueFamilyCount, nullptr);

			std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
			vkGetPhysicalDeviceQueueFamilyProperties(pd, &queueFamilyCount, queueFamilies.data());

			for (std::uint32_t i = 0; i < queueFamilies.size(); ++i)
			{
				if (queueFamilies[i].queueFlags & VK_QUEUE_GRAPHICS_BIT)
				{
					index = i;
					mPhysDev = pd;
					break;
				}
			}
		}

		if (mPhysDev == VK_NULL_HANDLE)
		{
			Logger::error("failed to find a suitable GPU!");
			return Result(0);
		}

		vkGetPhysicalDeviceMemoryProperties(mPhysDev, &mPhysMemProps);

		{// graphics queue index検索

			std::uint32_t propCount = 0;
			vkGetPhysicalDeviceQueueFamilyProperties(mPhysDev, &propCount, nullptr);
			std::vector<VkQueueFamilyProperties> props(propCount);
			vkGetPhysicalDeviceQueueFamilyProperties(mPhysDev, &propCount, props.data());

			for (uint32_t i = 0; i < propCount; ++i)
			{
				if (props[i].queueFlags & VK_QUEUE_GRAPHICS_BIT)
				{
					mGraphicsQueueIndex = i;
					break;
				}
			}
		}

		return Result();
	}

	inline Result VulkanDevice::createDevice() noexcept
	{
		std::vector<VkExtensionProperties> devExtProps;

		{
			uint32_t count = 0;

			if (VK_FAILED(res, vkEnumerateDeviceExtensionProperties(mPhysDev, nullptr, &count, nullptr)))
			{
				Logger::error("failed to enumerate device extension properties!");
				return Result(res);
			}

			devExtProps.resize(count);
			if (VK_FAILED(res, vkEnumerateDeviceExtensionProperties(mPhysDev, nullptr, &count, devExtProps.data())))
			{
				return Result(res);
			}
		}

		{
			const float defaultQueuePriority(1.f);

			VkDeviceQueueCreateInfo devQueueCI{};
			devQueueCI.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
			devQueueCI.queueFamilyIndex = mGraphicsQueueIndex;
			devQueueCI.queueCount = 1;
			devQueueCI.pQueuePriorities = &defaultQueuePriority;

			std::vector<const char*> extensions;
			extensions.reserve(devExtProps.size());

			for (const auto& v : devExtProps)
			{
				if (strcmp(v.extensionName, "VK_KHR_buffer_device_address"))
					extensions.emplace_back(v.extensionName);
				//extensions.emplace_back(v.extensionName);
			}

			VkDeviceCreateInfo ci{};
			ci.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
			ci.pQueueCreateInfos = &devQueueCI;
			ci.queueCreateInfoCount = 1;
			ci.ppEnabledExtensionNames = extensions.data();
			ci.enabledExtensionCount = static_cast<std::uint32_t>(extensions.size());

			if (VK_FAILED(res, vkCreateDevice(mPhysDev, &ci, nullptr, &mDevice)))
			{
				Logger::error("failed to create device!");
				return Result(res);
			}
		}

		vkGetDeviceQueue(mDevice, mGraphicsQueueIndex, 0, &mDeviceQueue);

		return Result();
	}

	inline Result VulkanDevice::createCommandPool() noexcept
	{

		VkCommandPoolCreateInfo ci{};
		ci.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
		ci.queueFamilyIndex = mGraphicsQueueIndex;
		ci.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;

		if (VK_FAILED(res, vkCreateCommandPool(mDevice, &ci, nullptr, &mCommandPool)))
		{
			return Result(res);
		}

		return Result();
	}

	inline Result VulkanDevice::createDescriptorPool() noexcept
	{
		std::array<VkDescriptorPoolSize, 2> sizes{};

		sizes[0].descriptorCount = kPoolUBSize;
		sizes[0].type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;

		sizes.back().descriptorCount = kPoolCISize;
		sizes.back().type = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;

		VkDescriptorPoolCreateInfo dpci{};
		dpci.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
		dpci.flags = VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT;

		dpci.maxSets = (kPoolUBSize + kPoolCISize);

		dpci.poolSizeCount = static_cast<uint32_t>(sizes.size());
		dpci.pPoolSizes = sizes.data();

		if (VK_FAILED(res, vkCreateDescriptorPool(mDevice, &dpci, nullptr, &mDescriptorPool)))
		{
			return Result(res);
		}

		return Result();
	}

	VkBool32 VKAPI_CALL VulkanDevice::DebugReportCallback
	(
		VkDebugReportFlagsEXT flags, VkDebugReportObjectTypeEXT objactTypes,
		uint64_t object, size_t location, int32_t messageCode,
		const char* pLayerPrefix, const char* pMessage, void* pUserData
	)
	{
		VkBool32 ret = VK_FALSE;
		if (flags & VK_DEBUG_REPORT_INFORMATION_BIT_EXT || flags & VK_DEBUG_REPORT_DEBUG_BIT_EXT)
		{
			ret = VK_TRUE;
		}

		if (pLayerPrefix)
		{
			//Logger::error("[{}] {}", pLayerPrefix, pMessage);
			std::cerr << "[" << pLayerPrefix << "] : " << pMessage << "\n";
		}

		return ret;
	}

	inline Result VulkanDevice::enableDebugReport() noexcept
	{
		
		mpfnVkCreateDebugReportCallbackEXT		= reinterpret_cast<PFN_vkCreateDebugReportCallbackEXT>(vkGetInstanceProcAddr(mInstance, "vkCreateDebugReportCallbackEXT"));
		mpfnVkDebugReportMessageEXT				= reinterpret_cast<PFN_vkDebugReportMessageEXT>(vkGetInstanceProcAddr(mInstance, "vkDebugReportMessageEXT"));
		mpfnVkDestroyDebugReportCallbackEXT		= reinterpret_cast<PFN_vkDestroyDebugReportCallbackEXT>(vkGetInstanceProcAddr(mInstance, "vkDestroyDebugReportCallbackEXT"));

		VkDebugReportFlagsEXT flags = VK_DEBUG_REPORT_ERROR_BIT_EXT | VK_DEBUG_REPORT_WARNING_BIT_EXT;

		VkDebugReportCallbackCreateInfoEXT drcci{};
		drcci.sType = VK_STRUCTURE_TYPE_DEBUG_REPORT_CALLBACK_CREATE_INFO_EXT;
		drcci.flags = flags;
		drcci.pfnCallback = &DebugReportCallback;
		mpfnVkCreateDebugReportCallbackEXT(mInstance, &drcci, nullptr, &mDebugReport);

		Logger::info("enabled debug mode");

		return Result();
	}

	inline Result VulkanDevice::disableDebugReport() noexcept
	{
		if (!mpfnVkDestroyDebugReportCallbackEXT)
		{
			Logger::error("function pointer to VkDestroyDebugReportCallbackEXT is NULL!");
			return Result(0);
		}

		mpfnVkDestroyDebugReportCallbackEXT(mInstance, mDebugReport, nullptr);

		Logger::info("disabled debug mode");

		return Result();
	}

}
