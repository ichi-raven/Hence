/*****************************************************************//**
 * @file   VulkanDevice.cpp
 * @brief  VulkanDeviceƒNƒ‰ƒX‚ÌŽÀ‘•
 *
 * @author ichi-raven
 * @date   November 2022
 *********************************************************************/

#include "../../../include/API/Vulkan/VulkanDevice.hpp"

#include "../../../include/Utility/Constants.hpp"
#include "../../../include/Utility/Logger.hpp"

#include "../../../include/API/Vulkan/Utility/Macro.hpp"

#include <vector>

namespace Hence
{
	VulkanDevice::VulkanDevice() noexcept
	{

		if (!(auto res = createInstance()))
		{
			Logger::error("failed to create VkInstance!(native error : {})", res.nativeResult);
		}

#ifndef NDEBUG
		if (!(auto res = enableDebugReport()))
		{
			Logger::error("failed to create VkDebugReportCallbackEXT!(native error : {})", res.nativeResult);
		}
#endif

		if (!(auto res = selectPhysicalDevice()))
		{
			Logger::error("failed to select suitable VkPhysicalDevice!(native error : {})", res.nativeResult);
		}

		if (!(auto res = createDevice()))
		{
			Logger::error("failed to create VkDevice!(native error : {})", res.nativeResult);
		}

		if (!(auto res = createCommandPool()))
		{
			Logger::error("failed to create VkCommandPool!(native error : {})", res.nativeResult);
		}
	}

	VulkanDevice::~VulkanDevice() noexcept
	{

		if (FAILED(vkDeviceWaitIdle(mDevice)))
		{
			Logger::error("Failed to wait device idol!");
		}

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

	inline Result VulkanDevice::createInstance()
	{
		std::vector<const char*> extensions;
		VkApplicationInfo appInfo{};
		appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
		appInfo.pApplicationName = mAppName.c_str();
		appInfo.pEngineName = kEngineName;
		appInfo.apiVersion = VK_API_VERSION_1_2;
		appInfo.engineVersion = VK_MAKE_API_VERSION(version[0], version[1], version[2], version[3]);

		// get extention properties
		std::vector<VkExtensionProperties> props;

		{
			uint32_t count = 0;
			auto res = vkEnumerateInstanceExtensionProperties(nullptr, &count, nullptr));
			if (FAILED(res))
			{
				return Result(res);
			}

			props.resize(count);
			auto res = vkEnumerateInstanceExtensionProperties(nullptr, &count, props.data());
			if (FAILED(res))
			{
				return Result(res);
			}

			Logger::info("enabled extensions : ");

			extensions.reserve(props.size());
			for (const auto& v : props)
			{
				extensions.emplace_back(v.extensionName);
				Logger::info(v.extensionName);
			}
		}

		VkInstanceCreateInfo ci{};
		ci.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
		ci.enabledExtensionCount = uint32_t(extensions.size());
		ci.ppEnabledExtensionNames = extensions.data();
		ci.pApplicationInfo = &appInfo;

		// debug layer
		const char* layers[] = { "VK_LAYER_KHRONOS_validation" };

#ifndef NDEBUG
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

		auto res = vkCreateInstance(&ci, nullptr, &instance);
		if (FAILED(res))
		{
#ifndef NDEBUG

			Logger::warn("failed to enable debug layer! creating VkInstance without debug layer...");
			ci.enabledLayerCount = 0;
			ci.ppEnabledLayerNames = nullptr;

			res = checkVkResult(vkCreateInstance(&ci, nullptr, &instance));

#endif
			Logger::error("failed to create VkInstance!");
			return Result(res);
		}

		mInstance = instance;

		return Result();
	}

	inline Result VulkanDevice::selectPhysicalDevice() noexcept
	{
		std::uint32_t devCount = 0;

		if (FAILED(auto res = vkEnumeratePhysicalDevices(*mInstance, &devCount, nullptr))
		{
			return Result(res);
		}

		std::vector<VkPhysicalDevice> physDevs(devCount);

			if (FAILED(auto res = vkEnumeratePhysicalDevices(*mInstance, &devCount, physDevs.data())))
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

			for (int i = 0; const auto & queueFamily : queueFamilies)
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
			auto res = vkEnumerateDeviceExtensionProperties(mPhysDev, nullptr, &count, nullptr);
			if (FAILED(res))
			{
				Logger::error("failed to enumerate device extension properties!");
				return Result(res);
			}

			devExtProps.resize(count);
			auto res = vkEnumerateDeviceExtensionProperties(mPhysDev, nullptr, &count, devExtProps.data());
			if (FAILED(res))
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
			extensions.reserve()
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

			auto res = checkVkResult(vkCreateDevice(mPhysDev, &ci, nullptr, &mDevice));
			if (FAILED(res))
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

		auto res = checkVkResult(vkCreateCommandPool(mDevice, &ci, nullptr, &mCommandPool));
		
		if (FAILED(res))
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
		assert(mpfnVkDestroyDebugReportCallbackEXT || !"function pointer to VkDestroyDebugReportCallbackEXT is NULL!");

		mpfnvkDestroyDebugReportCallbackEXT(mInstance, mDebugReport, nullptr);

		Logger::info("disabled debug mode");

		return Result();
	}
}
