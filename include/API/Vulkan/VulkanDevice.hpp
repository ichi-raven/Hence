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

#include <vulkan/vulkan.h>

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
         * @brief  VkCommandPool���擾����
         *  
         * @return VkCommandPool
         */
        VkCommandPool getCommandPool() const noexcept;

    private:

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

        //! Vulkan�C���X�^���X
        static std::optional<VkInstance>    mInstance;
        
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
        PFN_vkCreateDebugReportCallbackEXT  mvkCreateDebugReportCallbackEXT;
        PFN_vkDebugReportMessageEXT         mvkDebugReportMessageEXT;
        PFN_vkDestroyDebugReportCallbackEXT mvkDestroyDebugReportCallbackEXT;
        VkDebugReportCallbackEXT            mDebugReport;
	};
}

#endif
