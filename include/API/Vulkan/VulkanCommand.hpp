/*****************************************************************//**
 * @file   VulkanCommand.hpp
 * @brief  VulkanCommand�N���X�̃w�b�_�t�@�C��
 * 
 * @author ichi-raven
 * @date   April 2023
 *********************************************************************/
#ifndef HENCE_API_VULKAN_VULKANCOMMAND_HPP_
#define HENCE_API_VULKAN_VULKANCOMMAND_HPP_

#include "../../Utility/Result.hpp"
#include "../../Utility/ArrayProxy.hpp"

#include "../../Info/ClearValue.hpp"

#include <vulkan/vulkan.hpp>

#include <variant>

namespace Hence
{
    class VulkanDevice;
    class VulkanRenderPass;
    class VulkanGraphicsPipeline;
    class VulkanComputePipeline;
    class VulkanRaytracingPipeline;
    class VulkanBuffer;
    class VulkanBindGroup;

	class VulkanCommand
	{
        /**
         * @brief  �R���X�g���N�^
         */
        VulkanCommand(VulkanDevice& device) noexcept;

        /**
         * @brief  �f�X�g���N�^
         */
        ~VulkanCommand() noexcept;

        /**
         * @brief �R�}���h�������݊J�n
         *
         * @param renderpass �`����s��RenderPass
         */
        Result begin(VulkanRenderPass& renderpass, const std::uint32_t frameBufferIndex, ArrayProxy<ColorClearValue> ccvs, const std::optional<DepthClearValue>& dcv) noexcept;

        /**
         * @brief �R���s���[�g���[�h�ŃR�}���h�������݊J�n
         *
         */
        Result beginCompute() noexcept;

        /**
         * @brief �R�}���h�������ݏI��
         *
         */
        Result end() noexcept;

        /**
         * @brief �g�p����`��p�C�v���C�����Z�b�g����
         *
         * @param pipeline �g�p����`��p�C�v���C��
         */
        Result setGraphicsPipeline(VulkanGraphicsPipeline& pipeline) noexcept;

        /**
         * @brief �g�p����R���s���[�g�p�C�v���C�����Z�b�g����
         *
         * @param pipeline �g�p����R���s���[�g�p�C�v���C��
         */
        Result setComputePipeline(VulkanComputePipeline& pipeline) noexcept;

        /**
         * @brief �g�p���郌�C�g���[�X�p�C�v���C�����Z�b�g����
         *
         * @param pipeline �g�p���郌�C�g���[�X�p�C�v���C��
         */
        Result setRaytracingPipeline(VulkanRaytracingPipeline& pipeline) noexcept;

        /**
         * @brief  �g�p����V�F�[�_���\�[�X�̃o�C���h�O���[�v���Z�b�g����
         *
         * @param space ���蓖�Ă�space(HLSL)
         * @param bindGroup �g�p����o�C���h�O���[�v
         */
        Result setBindGroup(VulkanGraphicsPipeline& pipeline, VulkanBindGroup& bindGroup, const std::uint8_t space = 0) noexcept;

        /**
         * @brief  ���_�o�b�t�@���Z�b�g����
         *
         * @return ����
         */
        Result setVertexBuffer(VulkanBuffer& vertexBuffer) noexcept;

        /**
         * @brief  �C���f�b�N�X�o�b�t�@���Z�b�g����
         */
        Result setIndexBuffer(VulkanBuffer& indexBuffer) noexcept;

        /**
         * @brief �`����s��
         *
         */
        Result render(const std::uint32_t vertexCount, const std::uint32_t instanceCount, const std::uint32_t firstVertex, const std::uint32_t firstInstance) noexcept;

        Result renderIndexed(const std::uint32_t indexCount, const std::uint32_t instanceCount, const std::uint32_t firstIndex, const std::uint32_t vertexOffset, const std::uint32_t firstInstance) noexcept;

        Result execute() noexcept;

    private:
        VulkanDevice& mDevice;
        VkCommandBuffer mCommandBuffer;
	};
}

#endif