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

#include <cstdint>

namespace Hence
{
    // �O���錾
    template<typename API>
    class Device;

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

        /** 
         * @brief �R���X�g���N�^
         *  
         * @param device ��Ƃ���f�o�C�X
         */
        Command(Device<API>& device);

        /** 
         * @brief �f�X�g���N�^
         *  
         */
        ~Command();

        NONCOPYABLE(Command)

        /** 
         * @brief �R�}���h�������݊J�n
         *  
         * @param renderpass �`����s��RenderPass
         */
        Result begin(RenderPass& renderpass);

        /** 
         * @brief �R���s���[�g���[�h�ŃR�}���h�������݊J�n
         *  
         */
        Result beginCompute();

        /** 
         * @brief �R�}���h�������ݏI��
         *  
         */
        Result end();

        /** 
         * @brief �g�p����`��p�C�v���C�����Z�b�g����
         *  
         * @param pipeline �g�p����`��p�C�v���C��
         */
        Result setGraphicsPipeline(const GraphicsPipeline<API>& pipeline);

        /**
         * @brief �g�p����R���s���[�g�p�C�v���C�����Z�b�g����
         *
         * @param pipeline �g�p����R���s���[�g�p�C�v���C��
         */
        Result setComputePipeline(const ComputePipeline<API>& pipeline);

        /** 
         * @brief �g�p���郌�C�g���[�X�p�C�v���C�����Z�b�g����
         *  
         * @param pipeline �g�p���郌�C�g���[�X�p�C�v���C��
         */
        Result setRaytracingPipeline(const RaytracingPipeline<API>& pipeline);

        /** 
         * @brief  �g�p����V�F�[�_���\�[�X�̃o�C���h�O���[�v���Z�b�g����
         *  
         * @param space ���蓖�Ă�space(HLSL)
         * @param bindGroup �g�p����o�C���h�O���[�v
         */
        Result setBindGroup(const BindGroup<API>& bindGroup, const std::uint8_t space = 0);

        /** 
         * @brief �`����s��
         *  
         */
        Result render();

        Result renderIndexed();

        Result execute();

        const Impl& getInternalImpl() const;

    private:
        using APIDevice = APITrait<API>::Device;

        APIDevice& mDevice;
        Impl mImpl;
    };
}

#endif
