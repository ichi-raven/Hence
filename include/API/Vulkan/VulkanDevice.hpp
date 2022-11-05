/*****************************************************************//**
 * @file   VulkanDevice.hpp
 * @brief  VulkanDeviceクラスのヘッダファイル
 * 
 * @author ichi-raven
 * @date   November 2022
 *********************************************************************/
#ifndef HENCE_API_VULKAN_VULKANDEVICE_HPP_
#define HENCE_API_VULKAN_VULKANDEVICE_HPP_

#include "../../Utility/Result.hpp"

#include <vulkan/vulkan.h>

#include <optional>
#include <cstdint>

namespace Hence
{
	/**
	 * @brief  DeviceインタフェースのVulkan実装クラス
	 */
	class VulkanDevice
	{
	public:

        /** 
         * @brief  デフォルトコンストラクタ
         *  
         */
        VulkanDevice() noexcept;

        /** 
         * @brief  デストラクタ
         *  
         */
        ~VulkanDevice() noexcept;

        /** 
         * @brief  VkInstanceを取得する
         *  
         * @return VkInstance
         */
        VkInstance getInstance() const noexcept;

        /** 
         * @brief  VkDeviceを取得する
         *  
         * @return VkDevice
         */
        VkDevice getDevice() const noexcept;

        /** 
         * @brief  このデバイスのVkQueueを取得する
         *  
         * @return VkQueue
         */
        VkQueue getDeviceQueue() const noexcept;

        /** 
         * @brief  VkCommandPoolを取得する
         *  
         * @return VkCommandPool
         */
        VkCommandPool getCommandPool() const noexcept;

    private:

        /** 
         * @brief  VkInstance作成
         *  
         * @return 結果(Resultクラス)
         */
        inline Result createInstance() noexcept;

        /**
         * @brief  VkPhysicaDevice列挙・選択
         *
         * @return 結果(Resultクラス)
         */
        inline Result selectPhysicalDevice() noexcept;

        /** 
         * @brief  論理デバイス構築
         *  
         * @return 結果(Resultクラス)
         */
        inline Result createDevice() noexcept;

        /** 
         * @brief  コマンドプール構築
         *  
         * @return 結果(Resultクラス)
         */
        inline Result createCommandPool() noexcept;

        //! Vulkanインスタンス
        static std::optional<VkInstance>    mInstance;
        
        //! 物理デバイス
        VkPhysicalDevice                    mPhysDev;

        //! 物理デバイスのメモリ情報
        VkPhysicalDeviceMemoryProperties    mPhysMemProps;

        //! 論理デバイス
        VkDevice                            mDevice;

        //! 描画用キューのインデックス
        std::uint32_t                       mGraphicsQueueIndex;

        //! コマンドを発行するキュー
        VkQueue                             mDeviceQueue;

        //! コマンドプール
        VkCommandPool                       mCommandPool;

        // デバッグレポート関連
        PFN_vkCreateDebugReportCallbackEXT  mvkCreateDebugReportCallbackEXT;
        PFN_vkDebugReportMessageEXT         mvkDebugReportMessageEXT;
        PFN_vkDestroyDebugReportCallbackEXT mvkDestroyDebugReportCallbackEXT;
        VkDebugReportCallbackEXT            mDebugReport;
	};
}

#endif
