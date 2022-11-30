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

#include <vector>
#include <optional>

namespace Hence
{
	VulkanDevice::VulkanDevice() noexcept
	{
		if (FAILED(res, createInstance()))
		{
			Logger::error("failed to create VkInstance!(native error : {})", res.nativeResult);
		}

#ifndef NDEBUG
		
		if (FAILED(res, enableDebugReport()))
		{
			Logger::error("failed to create VkDebugReportCallbackEXT!(native error : {})", res.nativeResult);
		}
#endif
		
		if (FAILED(res, selectPhysicalDevice()))
		{
			Logger::error("failed to select suitable VkPhysicalDevice!(native error : {})", res.nativeResult);
		}

		
		if (FAILED(res, createDevice()))
		{
			Logger::error("failed to create VkDevice!(native error : {})", res.nativeResult);
		}

		
		if (FAILED(res, createCommandPool()))
		{
			Logger::error("failed to create VkCommandPool!(native error : {})", res.nativeResult);
		}
	}

	VulkanDevice::~VulkanDevice() noexcept
	{

		if (FAILED(res, vkDeviceWaitIdle(mDevice)))
		{
			Logger::error("failed to wait device idol! (native result : {})", static_cast<std::int32_t>(res));
		}

		vkDestroyCommandPool(mDevice, mCommandPool, nullptr);
		Logger::info("destroyed command poo");

#ifndef NDEBUG
		disableDebugReport();
		Logger::info("disabled debug report");
#endif

		vkDestroyDevice(mDevice, nullptr);
		Logger::info("destroyed device");

		vkDestroyInstance(mInstance.value(), nullptr);
		Logger::info("destroyed instance");
	}

	VkInstance VulkanDevice::getInstance() const noexcept
	{
		assert(mInstance || !"VkInstance is invalid(empty)!");

		return *mInstance;
	}

	VkDevice VulkanDevice::getDevice() const noexcept
	{
		return mDevice;
	}

	VkQueue VulkanDevice::getDeviceQueue() const noexcept
	{
		return mDeviceQueue;
	}

	VkCommandPool VulkanDevice::getCommandPool() const noexcept
	{
		return mCommandPool;
	}

	VkPhysicalDeviceMemoryProperties VulkanDevice::getPhysMemProps() const noexcept
	{
		return mPhysMemProps;
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

		VkInstance instance;

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

	inline Result VulkanDevice::selectPhysicalDevice() noexcept
	{
		std::uint32_t devCount = 0;

		if (VK_FAILED(res, vkEnumeratePhysicalDevices(*mInstance, &devCount, nullptr)))
		{
			return Result(res);
		}

		std::vector<VkPhysicalDevice> physDevs(devCount);

		if (VK_FAILED(res, vkEnumeratePhysicalDevices(*mInstance, &devCount, physDevs.data())))
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

			for (std::uint32_t i = 0; const auto & queueFamily : queueFamilies)
			{
				if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT)
				{
					index = i;
					mPhysDev = pd;
					break;
				}

				++i;
			}
		}

		if (mPhysDev == VK_NULL_HANDLE)
		{
			Logger::error("failed to find a suitable GPU!");
			return Result(0);
		}

		vkGetPhysicalDeviceMemoryProperties(mPhysDev, &mPhysMemProps);

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
			const float defaultQueuePriority(1.0f);
			VkDeviceQueueCreateInfo devQueueCI{};
			devQueueCI.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
			devQueueCI.queueFamilyIndex = mGraphicsQueueIndex;
			devQueueCI.queueCount = 1;
			devQueueCI.pQueuePriorities = &defaultQueuePriority;

			std::vector<const char*> extensions;
			extensions.reserve(devExtProps.size());

			for (const auto& v : devExtProps)
			{
				extensions.emplace_back(v.extensionName);
			}

			VkDeviceCreateInfo ci{};
			ci.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
			ci.pQueueCreateInfos = &devQueueCI;
			ci.queueCreateInfoCount = 1;
			ci.ppEnabledExtensionNames = extensions.data();
			ci.enabledExtensionCount = uint32_t(extensions.size());

			if (VK_FAILED(res, vkCreateDevice(mPhysDev, &ci, nullptr, &mDevice)))
			{
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
			Logger::error("[{}] {}", pLayerPrefix, pMessage);
		}

		return ret;
	}

	inline Result VulkanDevice::enableDebugReport() noexcept
	{
		
		mpfnVkCreateDebugReportCallbackEXT		= reinterpret_cast<PFN_vkCreateDebugReportCallbackEXT>(vkGetInstanceProcAddr(*mInstance, "vkCreateDebugReportCallbackEXT"));
		mpfnVkDebugReportMessageEXT				= reinterpret_cast<PFN_vkDebugReportMessageEXT>(vkGetInstanceProcAddr(*mInstance, "vkDebugReportMessageEXT"));
		mpfnVkDestroyDebugReportCallbackEXT		= reinterpret_cast<PFN_vkDestroyDebugReportCallbackEXT>(vkGetInstanceProcAddr(*mInstance, "vkDestroyDebugReportCallbackEXT"));

		VkDebugReportFlagsEXT flags = VK_DEBUG_REPORT_ERROR_BIT_EXT | VK_DEBUG_REPORT_WARNING_BIT_EXT;

		VkDebugReportCallbackCreateInfoEXT drcci{};
		drcci.sType = VK_STRUCTURE_TYPE_DEBUG_REPORT_CALLBACK_CREATE_INFO_EXT;
		drcci.flags = flags;
		drcci.pfnCallback = &DebugReportCallback;
		mpfnVkCreateDebugReportCallbackEXT(*mInstance, &drcci, nullptr, &mDebugReport);

		Logger::info("enabled debug mode");

		return Result();
	}

	inline Result VulkanDevice::disableDebugReport() noexcept
	{
		assert(mpfnVkDestroyDebugReportCallbackEXT || !"function pointer to VkDestroyDebugReportCallbackEXT is NULL!");

		mpfnVkDestroyDebugReportCallbackEXT(*mInstance, mDebugReport, nullptr);

		Logger::info("disabled debug mode");

		return Result();
	}

}
