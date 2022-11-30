/*****************************************************************//**
 * @file   VulkanDevice.hpp
 * @brief  VulkanDevice�N���X�̃w�b�_�t�@�C��
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
	 * @brief  Device�C���^�t�F�[�X��Vulkan�����N���X
	 */
	class VulkanDevice
	{
	public:

        /** 
         * @brief  �f�t�H���g�R���X�g���N�^
         *  
         */
        VulkanDevice() noexcept;

        /** 
         * @brief  �f�X�g���N�^
         *  
         */
        ~VulkanDevice() noexcept;

        /** 
         * @brief  VkInstance���擾����
         *  
         * @return VkInstance
         */
        VkInstance getInstance() const noexcept;

        /** 
         * @brief  VkPhysicalDevice���擾����
         *  
         * @return VkPhysicalDevice
         */
        VkPhysicalDevice getPhysicalDevice() const noexcept;

        /** 
         * @brief  VkDevice���擾����
         *  
         * @return VkDevice
         */
        VkDevice getDevice() const noexcept;

        /** 
         * @brief  ���̃f�o�C�X��VkQueue���擾����
         *  
         * @return VkQueue
         */
        VkQueue getDeviceQueue() const noexcept;

        /** 
         * @brief graphics queue��index���擾����
         *  
         * @return index
         */
        std::uint32_t getGraphicsQueueIndex() const noexcept;
      
        /** 
         * @brief  VkCommandPool���擾����
         *  
         * @return VkCommandPool
         */
        VkCommandPool getCommandPool() const noexcept;

        /** 
         * @brief  VkPhysicalDeviceMemoryProperties���擾����
         *  
         * @return VkPhysicalDeviceMemoryProperties
         */
        VkPhysicalDeviceMemoryProperties getPhysMemProps() const noexcept;

        std::uint32_t getMemoryTypeIndex(std::uint32_t requestBits, VkMemoryPropertyFlags requestProps) const noexcept;

    private:

        /**
         * @brief VkDebugLayer�̏o�͕\���p�R�[���o�b�N�֐� 
         * @detail �e������Vulkan�̎d�l���� 
         */
        static VkBool32 VKAPI_CALL DebugReportCallback
        (
            VkDebugReportFlagsEXT flags, VkDebugReportObjectTypeEXT objactTypes,
            uint64_t object, size_t location, int32_t messageCode,
            const char* pLayerPrefix, const char* pMessage, void* pUserData
        );

        /** 
         * @brief  VkInstance�쐬
         *  
         * @return ����(Result�N���X)
         */
        inline Result createInstance() noexcept;

        /**
         * @brief  VkPhysicaDevice�񋓁E�I��
         *
         * @return ����(Result�N���X)
         */
        inline Result selectPhysicalDevice() noexcept;

        /** 
         * @brief  �_���f�o�C�X�\�z
         *  
         * @return ����(Result�N���X)
         */
        inline Result createDevice() noexcept;

        /** 
         * @brief  �R�}���h�v�[���\�z
         *  
         * @return ����(Result�N���X)
         */
        inline Result createCommandPool() noexcept;

        /**
         * @brief  �f�o�b�O���|�[�g�o�͂�L��������
         */
        inline Result enableDebugReport() noexcept;

        /**
         * @brief  �f�o�b�O���|�[�g�o�͂𖳌�������
         */
        inline Result disableDebugReport() noexcept;

        //! Vulkan�C���X�^���X
        VkInstance                          mInstance;
        
        //! �����f�o�C�X
        VkPhysicalDevice                    mPhysDev;

        //! �����f�o�C�X�̃��������
        VkPhysicalDeviceMemoryProperties    mPhysMemProps;

        //! �_���f�o�C�X
        VkDevice                            mDevice;

        //! �`��p�L���[�̃C���f�b�N�X
        std::uint32_t                       mGraphicsQueueIndex;

        //! �R�}���h�𔭍s����L���[
        VkQueue                             mDeviceQueue;

        //! �R�}���h�v�[��
        VkCommandPool                       mCommandPool;

        // �f�o�b�O���|�[�g�֘A
        PFN_vkCreateDebugReportCallbackEXT  mpfnVkCreateDebugReportCallbackEXT;
        PFN_vkDebugReportMessageEXT         mpfnVkDebugReportMessageEXT;
        PFN_vkDestroyDebugReportCallbackEXT mpfnVkDestroyDebugReportCallbackEXT;
        VkDebugReportCallbackEXT            mDebugReport;
	};
}

#endif
