#ifndef HENCE_API_HPP_
#define HENCE_API_HPP_

#include "API/VulkanImpl.hpp"
#include "API/DirectX12Impl.hpp"

namespace Hence
{

    struct Vulkan {};

    struct DirectX12 {};

    template<typename API>
    struct APITrait;

    template<>
    struct APITrait<Vulkan>
    {
        constexpr static auto APIName = "Vulkan";

        using Device                    = VulkanDevice;
        using VRAMAllocatorImpl         = VulkanVRAMAllocator;
        using BufferImpl                = VulkanBuffer;
        using ImageImpl                 = VulkanImage;
        using ShaderImpl                = VulkanShader;
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
        using VRAMAllocatorImpl         = DirectX12VRAMAllocator;
        using BufferImpl                = DirectX12Buffer;
        using ImageImpl                 = DirectX12Image;
        using ShaderImpl                = DirectX12Shader;
        using BindGroupImpl             = DirectX12BindGroup;
        using CommandImpl               = DirectX12Command;
        using RenderPassImpl            = DirectX12RenderPass;
        using GraphicsPipelineImpl      = DirectX12GraphicsPipeline;
        using ComputePipelineImpl       = DirectX12ComputePipeline;
        using RaytracingPipelineImpl    = DirectX12RaytracingPipeline;
    };
}

#endif
