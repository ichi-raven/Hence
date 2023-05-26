/*****************************************************************//**
 * @file   Command.hpp
 * @brief  Command�N���X�̃w�b�_�t�@�C��
 * 
 * @author ichi-raven
 * @date   November 2022
 *********************************************************************/
#ifndef HENCE_COMMAND_HPP_
#define HENCE_COMMAND_HPP_

#include "API.hpp"
#include "Utility/Macro.hpp"
#include "Utility/ArrayProxy.hpp"

#include "Info/ClearValue.hpp"
#include "Info/ImageLayout.hpp"

#include <cstdint>

namespace Hence
{
    // �O���錾
    template<typename API>
    class Device;

    // �O���錾
    template<typename API>
    class Semaphore;

    // �O���錾
    template<typename API>
    class GraphicsPipeline;

    // �O���錾
    template<typename API>
    class ComputePipeline;

    // �O���錾
    template<typename API>
    class RaytracingPipeline;

    // �O���錾
    template<typename API>
    class BindGroup;

    template<typename API>
    class RenderPass;

    /**
     * @brief  GPU�ɑ��M����R�}���h��\���N���X
     * @tparam API �o�b�N�G���h�Ɏg�p����API�^(API.hpp���Œ�`����Ă���)
     */
    template<typename API>
    class Command
    {
    public:
        // ���������^(��ʂɃ��[�U���g�p����K�v�͂Ȃ�)
        using Impl = APITrait<API>::CommandImpl;

        Command() noexcept;

        /** 
         * @brief �R���X�g���N�^
         *  
         * @param device ��Ƃ���f�o�C�X
         */
        Command(Device<API>& device) noexcept;

        /** 
         * @brief �f�X�g���N�^
         *  
         */
        ~Command() noexcept;

        NONCOPYABLE(Command);

        Command(Command<API>&& src) noexcept;
        Command<API>& operator=(Command<API>&& src) noexcept;


        /** 
         * @brief �R�}���h�������݊J�n
         *  
         * @param renderpass �`����s��RenderPass
         */
        Result begin(RenderPass<API>& renderpass, const uint32_t frameBufferIndex, ArrayProxy<ColorClearValue> ccvs, const DepthClearValue& dcv) noexcept;

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
        Result setGraphicsPipeline(GraphicsPipeline<API>& pipeline) noexcept;

        /**
         * @brief �g�p����R���s���[�g�p�C�v���C�����Z�b�g����
         *
         * @param pipeline �g�p����R���s���[�g�p�C�v���C��
         */
        Result setComputePipeline(ComputePipeline<API>& pipeline) noexcept;

        /** 
         * @brief �g�p���郌�C�g���[�X�p�C�v���C�����Z�b�g����
         *  
         * @param pipeline �g�p���郌�C�g���[�X�p�C�v���C��
         */
        Result setRaytracingPipeline(RaytracingPipeline<API>& pipeline) noexcept;

        /** 
         * @brief  �g�p����V�F�[�_���\�[�X�̃o�C���h�O���[�v���Z�b�g����
         *  
         * @param space ���蓖�Ă�space(HLSL)
         * @param bindGroup �g�p����o�C���h�O���[�v
         */
        Result setBindGroup(BindGroup<API>& bindGroup) noexcept;

        /** 
         * @brief  ���_�o�b�t�@���Z�b�g����
         *  
         * @return ����
         */
        Result setVertexBuffer(Buffer<API>& vertexBuffer) noexcept;

        /**
         * @brief  �C���f�b�N�X�o�b�t�@���Z�b�g����
         */
        Result setIndexBuffer(Buffer<API>& indexBuffer) noexcept;

        /** 
         * @brief �`����s��
         *  
         */
        Result render(const std::uint32_t vertexCount, const std::uint32_t instanceCount, const std::uint32_t firstVertex, const std::uint32_t firstInstance) noexcept;

        Result renderIndexed(const std::uint32_t indexCount, const std::uint32_t instanceCount, const std::uint32_t firstIndex, const std::uint32_t vertexOffset, const std::uint32_t firstInstance) noexcept;

        Result barrier(Image<API>& image, ImageLayout from, ImageLayout to) noexcept;

        Result execute(Semaphore<API>& waitSemaphore, Semaphore<API>& signalSemaphore) noexcept;

        Impl& getInternalImpl() noexcept;

    private:
        //using APIDevice = APITrait<API>::Device;

        //APIDevice& mAPIDevice;
        std::optional<Impl> mImpl;
    };
}

#include "../src/Command.inl"

#endif
