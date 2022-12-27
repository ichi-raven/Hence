/*****************************************************************//**
 * @file   API.hpp
 * @brief  API���Ƃ�trait�y�ю���������`����
 * 
 * @author ichi-raven
 * @date   November 2022
 *********************************************************************/
#ifndef HENCE_API_HPP_
#define HENCE_API_HPP_

#include "API/VulkanImpl.hpp"
#include "API/DirectX12Impl.hpp"

namespace Hence
{
    /**
     * @brief  Vulkan API��\���^�CAPI�Ƃ��Ă��̌^��n����Vulkan API���o�b�N�G���h�Ƃ��ē��삷��
     */
    struct Vulkan 
    {};

    /**
     * @brief  DirectX12��\���^�CAPI�Ƃ��Ă��̌^��n����DirectX12���o�b�N�G���h�Ƃ��ē��삷��
     */
    struct DirectX12 
    {};

    /**
     * @brief  API��trait�C���̓��ꉻ��p����API���Ƃ̎��������\������
     */
    template<typename API>
    struct APITrait;

    template<>
    struct APITrait<Vulkan>
    {
        constexpr static auto APIName = "Vulkan";

        using Device                    = VulkanDevice;
        using WindowImpl                = VulkanWindow;
        using VRAMAllocatorImpl         = VulkanVRAMAllocator;
        using BufferImpl                = VulkanBuffer;
        using ImageImpl                 = VulkanImage;
        using SamplerImpl               = VulkanSampler;
        using ShaderImpl                = VulkanShader;
        using BindLayoutImpl            = VulkanBindLayout;
        using BindGroupImpl             = VulkanBindGroup;
        using CommandImpl               = VulkanCommand;
        using RenderPassImpl            = VulkanRenderPass;
        using GraphicsPipelineImpl      = VulkanGraphicsPipeline;
        using ComputePipelineImpl       = VulkanComputePipeline;
        using RaytracingPipelineImpl    = VulkanRaytracingPipeline;
    };

    template<>
    struct APITrait<DirectX12>
    {
        constexpr static auto APIName = "DirectX12";

        using Device                    = DirectX12Device;
        using WindowImpl                = DirectX12Window;
        using VRAMAllocatorImpl         = DirectX12VRAMAllocator;
        using BufferImpl                = DirectX12Buffer;
        using ImageImpl                 = DirectX12Image;
        using SamplerImpl               = DirectX12Sampler;
        using ShaderImpl                = DirectX12Shader;
        using BindLayoutImpl            = DirectX12BindLayout;
        using BindGroupImpl             = DirectX12BindGroup;
        using CommandImpl               = DirectX12Command;
        using RenderPassImpl            = DirectX12RenderPass;
        using GraphicsPipelineImpl      = DirectX12GraphicsPipeline;
        using ComputePipelineImpl       = DirectX12ComputePipeline;
        using RaytracingPipelineImpl    = DirectX12RaytracingPipeline;
    };
}

#endif
