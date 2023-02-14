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

#include <vulkan/vulkan.hpp>

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
        VkInstance getInstance() noexcept;

        /** 
         * @brief  VkPhysicalDeviceを取得する
         *  
         * @return VkPhysicalDevice
         */
        VkPhysicalDevice getPhysicalDevice() noexcept;

        /** 
         * @brief  VkDeviceを取得する
         *  
         * @return VkDevice
         */
        VkDevice getDevice() noexcept;

        /** 
         * @brief  このデバイスのVkQueueを取得する
         *  
         * @return VkQueue
         */
        VkQueue getDeviceQueue() noexcept;

        /** 
         * @brief graphics queueのindexを取得する
         *  
         * @return index
         */
        std::uint32_t getGraphicsQueueIndex() const noexcept;
      
        /** 
         * @brief  VkCommandPoolを取得する
         *  
         * @return VkCommandPool
         */
        VkCommandPool getCommandPool() noexcept;

        /** 
         * @brief  VkPhysicalDeviceMemoryPropertiesを取得する
         *  
         * @return VkPhysicalDeviceMemoryProperties
         */
        VkPhysicalDeviceMemoryProperties getPhysMemProps() const noexcept;

        /** 
         * @brief  リソースに要求されるメモリ情報を表すビットフラグを構成する
         *  
         * @param requestBits
         * @param requestProps 
         * @return ビットフラグ(memoryTypeIndexに直接渡せる)
         */
        std::uint32_t getMemoryTypeIndex(std::uint32_t requestBits, VkMemoryPropertyFlags requestProps) const noexcept;

        VkDescriptorPool getDescriptorPool() noexcept;

        constexpr static std::uint32_t kPoolUBSize = 256;
        constexpr static std::uint32_t kPoolCISize = 256;

    private:

        /**
         * @brief VkDebugLayerの出力表示用コールバック関数 
         * @detail 各引数はVulkanの仕様準拠 
         */
        static VkBool32 VKAPI_CALL DebugReportCallback
        (
            VkDebugReportFlagsEXT flags, VkDebugReportObjectTypeEXT objactTypes,
            uint64_t object, size_t location, int32_t messageCode,
            const char* pLayerPrefix, const char* pMessage, void* pUserData
        );

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

        /**
         * @brief  ディスクリプタプール構築
         * 
         * @return 結果(Resultクラス)
         */
        inline Result createDescriptorPool() noexcept;
             
        /**
         * @brief  デバッグレポート出力を有効化する
         */
        inline Result enableDebugReport() noexcept;

        /**
         * @brief  デバッグレポート出力を無効化する
         */
        inline Result disableDebugReport() noexcept;

        //! Vulkanインスタンス
        VkInstance                          mInstance;
        
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

        //! descriptorpoolとそれが持っているサイズ
        VkDescriptorPool                    mDescriptorPool;

        // デバッグレポート関連
        PFN_vkCreateDebugReportCallbackEXT  mpfnVkCreateDebugReportCallbackEXT;
        PFN_vkDebugReportMessageEXT         mpfnVkDebugReportMessageEXT;
        PFN_vkDestroyDebugReportCallbackEXT mpfnVkDestroyDebugReportCallbackEXT;
        VkDebugReportCallbackEXT            mDebugReport;
	};
}

#endif
